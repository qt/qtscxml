# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(tst_statemachine LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()


#####################################################################
## tst_statemachine Test:
#####################################################################

if(WASM)
    return()
endif()

qt_internal_add_test(tst_statemachine
    SOURCES
        tst_statemachine.cpp
    LIBRARIES
        Qt::Gui
        Qt::Qml
        Qt::Scxml
        Qt::CorePrivate
        Qt::ScxmlPrivate
        Qt::TestPrivate
)

# Resources:
set(tst_statemachine_resource_files
    "topmachine.scxml"
    "submachineA.scxml"
    "submachineB.scxml"
    "emptylog.scxml"
    "eventoccurred.scxml"
    "historystate.scxml"
    "ids1.scxml"
    "invoke.scxml"
    "multipleinvokableservices.scxml"
    "stateDotDoneEvent.scxml"
    "statenames.scxml"
    "statenamesnested.scxml"
    "foreach.scxml"
    "finalizeOnDoneInvokeEvent.scxml"
    "nestedinvoker.scxml"
    "nestederror.scxml"
)

qt_internal_add_resource(tst_statemachine "tst_statemachine"
    PREFIX
        "/tst_statemachine"
    FILES
        ${tst_statemachine_resource_files}
)

qt6_add_statecharts(tst_statemachine
    topmachine.scxml
)

#### Keys ignored in scope 1:.:.:statemachine.pro:<TRUE>:
# TEMPLATE = "app"
