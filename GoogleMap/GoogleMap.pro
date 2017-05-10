QT +=  core gui quick webengine webenginewidgets webchannel

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GoogleMap
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        MainWindow.cpp \
    DataManager.cpp

HEADERS  += MainWindow.h \
    DataManager.h

FORMS    +=

RESOURCES += \
    MapRes.qrc
