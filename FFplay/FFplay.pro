QT       += core gui quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FFplay
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    MainWindow.cpp \
    ImageThread.cpp \
    VideoFrameProvider.cpp \
    VideoItem.cpp

HEADERS  += \
    MainWindow.h \
    ImageThread.h \
    VideoFrameProvider.h \
    VideoItem.h

CONFIG += mobility
MOBILITY = 

android{
    CONFIG*=c++11
    CFLAGS=-D__STDC_CONSTANT_MACROS
    DEFINES +=__STDC_CONSTANT_MACROS
    INCLUDEPATH += E:/OpenCODE/FFMPEG/ffmpeg-3.2-arm/include
    LIBS += -LE:/OpenCODE/FFMPEG/ffmpeg-3.2-arm/lib
    LIBS +=  -lavfilter-6 -lavcodec-57 -lavformat-57 -lavutil-55 -lswscale-4 -lswresample-2
}

win32{
    INCLUDEPATH += E:/OpenCODE/FFMPEG/ffmpeg-3.2-msys+msvc15/include
    LIBS += -LE:/OpenCODE/FFMPEG/ffmpeg-3.2-msys+msvc15/lib
    LIBS +=  -lavfilter -lavcodec -lavformat -lavutil -lswscale -lswresample
    CFLAGS = -D__STDC_CONSTANT_MACROS
    DEFINES += __STDC_CONSTANT_MACROS
}

INCLUDEPATH += $$(MAVLINK)/

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        E:/OpenCODE/FFMPEG/ffmpeg-3.2-arm/lib/libavcodec-57.so \
        E:/OpenCODE/FFMPEG/ffmpeg-3.2-arm/lib/libavfilter-6.so \
        E:/OpenCODE/FFMPEG/ffmpeg-3.2-arm/lib/libavformat-57.so \
        E:/OpenCODE/FFMPEG/ffmpeg-3.2-arm/lib/libavutil-55.so \
        E:/OpenCODE/FFMPEG/ffmpeg-3.2-arm/lib/libswscale-4.so \
        E:/OpenCODE/FFMPEG/ffmpeg-3.2-arm/lib/libswresample-2.so
}

DISTFILES += \
    Main.qml

RESOURCES += \
    ffplayResource.qrc
