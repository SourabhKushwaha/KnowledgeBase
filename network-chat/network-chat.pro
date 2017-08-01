QT += core qml quick gui network

TEMPLATE = app

HEADERS       = client.h \
                connection.h \
                peermanager.h \
                server.h \
                QmlBridge.h \
                AppManager.h
SOURCES       = client.cpp \
                connection.cpp \
                main.cpp \
                peermanager.cpp \
                server.cpp \
                QmlBridge.cpp \
                AppManager.cpp
FORMS         =

RESOURCES += \
    AppResource.qrc
