#####################################################################
## EcmaScript SCXML DataModel Plugin:
#####################################################################

qt_internal_add_plugin(QDataModelPluginEcmaScript
    OUTPUT_NAME qscxmldatamodelecmascript
    TYPE scxmldatamodel
    SOURCES
        qdatamodel_ecmascript_plugin.cpp qdatamodel_ecmascript_plugin.h
        qscxmlecmascriptdatamodel.h qscxmlecmascriptdatamodel.cpp
        qscxmlecmascriptplatformproperties.cpp qscxmlecmascriptplatformproperties_p.h
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Scxml
        Qt::Qml
    PRIVATE_MODULE_INTERFACE
        Qt::CorePrivate
        Qt::QmlPrivate
        Qt::ScxmlPrivate
    INCLUDE_DIRECTORIES
        $<TARGET_PROPERTY:Qt::QmlPrivate,INTERFACE_INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:Qt::Scxml,INTERFACE_INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:Qt::ScxmlPrivate,INTERFACE_INCLUDE_DIRECTORIES>
)

# OTHER_FILES = "ecmascriptdatamodel_plugin.json"
