#!/bin/bash
# Copyright (C) 2026 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

$HOME/bauhaus-suite/setup.sh --non-interactive
export PATH=/home/qt/bauhaus-suite/bin:$PATH
export BAUHAUS_CONFIG=$(cd $(dirname $(readlink -f $0)) && pwd)
export AXIVION_VERSION_NAME=$(git rev-parse HEAD)
export EXCLUDE_FILES="build/*:src/3rdparty/*"
export CAFECC_BASEPATH="/home/qt/work/qt/$TESTED_MODULE_COIN"
gccsetup --cc gcc --cxx g++ --config "$BAUHAUS_CONFIG"
cd "$CAFECC_BASEPATH"
BAUHAUS_IR_COMPRESSION=none COMPILE_ONLY=1 cmake -G Ninja -DAXIVION_ANALYSIS_TOOLCHAIN_FILE=/home/qt/bauhaus-suite/profiles/cmake/axivion-launcher-toolchain.cmake -DCMAKE_PREFIX_PATH=/home/qt/work/install/lib/cmake -DCMAKE_PROJECT_INCLUDE_BEFORE=/home/qt/bauhaus-suite/profiles/cmake/axivion-before-project-hook.cmake -B build -S . --fresh
cmake --build build -j4

ROOT_DIR=src
MAGIC="Qt-Security score:critical"

INCLUDE_FILES=""

while IFS= read -r file; do
    if [ -z "$INCLUDE_FILES" ]; then
        INCLUDE_FILES="$file"
    else
        INCLUDE_FILES="$INCLUDE_FILES:$file"
    fi
done <<EOF
$(grep -rl "$MAGIC" "$ROOT_DIR")
EOF

if [ -z "$INCLUDE_FILES" ]; then
    echo "No Security Critical files found; running analysis with an explicit fallback sentinel."
    INCLUDE_FILES="__NO_FILES_FOUND__"
fi

export INCLUDE_FILES

# Groups follow the Qt 6 modules in this repo: scxml (Scxml module, its
# ECMAScript data model plugin and the QtScxml QML module) and statemachine
# (StateMachine module and the QtQml.StateMachine QML module). ScxmlGlobalPrivate
# is a static internal module, so it has no .ir of its own.
for MODULE in qtscxml qtstatemachine; do
    export MODULE
    export IRNAME=build/$MODULE.ir
    if [ "$MODULE" == "qtscxml" ]
    then
        TARGET_NAME="build/lib/libQt6Scxml.so.*.ir"
        TARGET_NAME="$TARGET_NAME:build/plugins/scxmldatamodel/lib*.so*.ir"
        TARGET_NAME="$TARGET_NAME:build/qml/QtScxml/lib*.so*.ir"
        export TARGET_NAME
        export PACKAGE="Add-ons"
    elif [ "$MODULE" == "qtstatemachine" ]
    then
        TARGET_NAME="build/lib/libQt6StateMachine.so.*.ir"
        TARGET_NAME="$TARGET_NAME:build/qml/QtQml/StateMachine/lib*.so*.ir"
        export TARGET_NAME
        export PACKAGE="Add-ons"
    fi
    axivion_ci "$@"
done
