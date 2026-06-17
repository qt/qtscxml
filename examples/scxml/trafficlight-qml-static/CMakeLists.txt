# Copyright (C) 2023 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(trafficlight-qml-static LANGUAGES CXX)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/scxml/trafficlight-qml-static")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Scxml)
qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(trafficlight-qml-static
    trafficlight-qml-static.cpp
)

set_target_properties(trafficlight-qml-static PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(trafficlight-qml-static PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Scxml
)

# Statecharts:
qt6_add_statecharts(trafficlight-qml-static
    statemachine.scxml
)

qt_add_qml_module(trafficlight-qml-static
    URI TrafficLightApplication
    VERSION 1.0
    QML_FILES
        MainView.qml
        Button.qml
        Lights.ui.qml
    SOURCES
        trafficlight-qml.h
    RESOURCES
        play.png
        yellow.png
        red.png
        green.png
        background.png
        pause.png
)

install(TARGETS trafficlight-qml-static
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
