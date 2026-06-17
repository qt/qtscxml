QT += widgets scxml

SOURCES = trafficlight.cpp
HEADERS = trafficlight.h

SOURCES += trafficlight-widgets-dynamic.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/scxml/trafficlight-widgets-dynamic
INSTALLS += target

RESOURCES += \
    trafficlight-widgets-dynamic.qrc
