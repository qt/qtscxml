TEMPLATE = app

QT += qml scxml

SOURCES += trafficlight-qml-dynamic.cpp

QML_IMPORT_NAME = TrafficLightApplication
QML_IMPORT_MAJOR_VERSION = 1

qml_resources.files = \
    qmldir \
    MainView.qml \
    Button.qml \
    Lights.ui.qml \
    statemachine.scxml \
    play.png \
    yellow.png \
    red.png \
    green.png \
    background.png \
    pause.png \

qml_resources.prefix = /qt/qml/TrafficLightApplication

RESOURCES += qml_resources

target.path = $$[QT_INSTALL_EXAMPLES]/scxml/trafficlight-qml-dynamic
INSTALLS += target
