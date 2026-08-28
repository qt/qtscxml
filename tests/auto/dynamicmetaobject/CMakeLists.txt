# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(tst_dynamicmetaobject LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()


#####################################################################
## tst_dynamicmetaobject Test:
#####################################################################

qt_internal_add_test(tst_dynamicmetaobject
    SOURCES
        tst_dynamicmetaobject.cpp
    LIBRARIES
        Qt::Gui
        Qt::Qml
        Qt::Scxml
)

# Resources:
set(tst_dynamicmetaobject_resource_files
    "mediaplayer.scxml"
    "test1.scxml"
)

qt_internal_add_resource(tst_dynamicmetaobject "tst_dynamicmetaobject"
    PREFIX
        "/tst_dynamicmetaobject"
    FILES
        ${tst_dynamicmetaobject_resource_files}
)


#### Keys ignored in scope 1:.:.:dynamicmetaobject.pro:<TRUE>:
# TEMPLATE = "app"
