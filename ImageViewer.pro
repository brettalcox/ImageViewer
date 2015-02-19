#-------------------------------------------------
#
# Project created by QtCreator 2015-02-19T12:49:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageViewer
TEMPLATE = app


SOURCES += main.cpp \
    image.cpp \
    zoom.cpp

HEADERS  += \
    image.h \
    zoom.h

FORMS    += \
    image.ui
