# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(tst_qstatemachine LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()


#####################################################################
## tst_qstatemachine Test:
#####################################################################

qt_internal_add_test(tst_qstatemachine
    SOURCES
        tst_qstatemachine.cpp
    LIBRARIES
        Qt::StateMachine
        Qt::StateMachinePrivate
        Qt::TestPrivate
)

## Scopes:
#####################################################################

qt_internal_extend_target(tst_qstatemachine CONDITION TARGET Qt::Widgets
    LIBRARIES
        Qt::Widgets
)
