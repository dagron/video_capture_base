#-------------------------------------------------
#
# Project created by QtCreator 2016-09-22T14:55:17
#
#-------------------------------------------------
QT       += core gui widgets

CONFIG   += c++14

TARGET = VideoSample
TEMPLATE = app


SOURCES += main.cpp \
    videoplayer.cpp \
    shower.cpp

HEADERS += \
    videoplayer.h \
    shower.h

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /home/user/WORKSPACE/caffe/include/

LIBS += -L /home/user/WORKSPACE/caffe/build/lib/libcaffe.so
LIBS += -L /usr/lib/x86_64-linux-gnu/libglog.so
LIBS += -L /usr/local/lib/*.so

DEFINES += DEBUG

DEFINES += DEBUG
CONFIG(debug, debug|release){
    DEFINES += DEBUG
}


