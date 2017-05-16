QT += core gui network qml quick

TEMPLATE = app
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS       = chatdialog.h \
                client.h \
                connection.h \
                peermanager.h \
                server.h \
    QmlBridge.h \
    AppManager.h
SOURCES       = chatdialog.cpp \
                client.cpp \
                connection.cpp \
                main.cpp \
                peermanager.cpp \
                server.cpp \
    QmlBridge.cpp \
    AppManager.cpp
FORMS         = chatdialog.ui
QT           += network widgets


RESOURCES += \
    AppResource.qrc


