# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(tst_scxmlcoutput_namespace LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()

if(WASM)
    return()
endif()

qt_internal_add_test(tst_scxmlcoutput_namespace
    SOURCES
        tst_scxmlcoutput.cpp
    LIBRARIES
        Qt::Scxml
)

# This testcase tests providing the namespace
qt6_add_statecharts(tst_scxmlcoutput_namespace
    ../shared/ids1.scxml
    NAMESPACE MyNamespace
)
