#-------------------------------------------------
#
# Project created by QtCreator 2015-02-19T12:49:09
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageViewer
TEMPLATE = app


SOURCES += main.cpp \
    image.cpp \
    zoom.cpp \
    filter.cpp

HEADERS  += \
    image.h \
    zoom.h \
    filter.h

FORMS    += \
    image.ui
