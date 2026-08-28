# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(tst_statemachineinfo LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()


#####################################################################
## tst_statemachineinfo Test:
#####################################################################

qt_internal_add_test(tst_statemachineinfo
    SOURCES
        tst_statemachineinfo.cpp
    LIBRARIES
        Qt::Gui
        Qt::Qml
        Qt::ScxmlPrivate
)

# Resources:
set(tst_statemachineinfo_resource_files
    "statemachine.scxml"
)

qt_internal_add_resource(tst_statemachineinfo "tst_statemachineinfo"
    PREFIX
        "/tst_statemachineinfo"
    FILES
        ${tst_statemachineinfo_resource_files}
)


#### Keys ignored in scope 1:.:.:statemachineinfo.pro:<TRUE>:
# TEMPLATE = "app"
