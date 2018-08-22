#-------------------------------------------------
#
# Project created by QtCreator 2018-08-21T02:43:43
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = HighLightDetected
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

INCLUDEPATH += /opt/tarfile/opencv-2.4.4/include
LIBS        += /opt/tarfile/opencv-2.4.4/build/lib/*.so
