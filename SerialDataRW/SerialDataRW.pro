CONFIG += serialport
QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialDataRW
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        MainWindow.cpp \
    SerialCommunicator.cpp \
    DataConverter.cpp

HEADERS  += MainWindow.h \
    SerialCommunicator.h \
    DataConverter.h

FORMS    += MainWindow.ui
