#-------------------------------------------------
#
# Project created by QtCreator 2015-02-19T12:49:09
#
#-------------------------------------------------

QT       += core gui network
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageViewer
TEMPLATE = app


SOURCES += main.cpp \
    image.cpp \
    zoom.cpp \
    filter.cpp \
    loadurl.cpp

HEADERS  += \
    image.h \
    zoom.h \
    filter.h \
    loadurl.h \
    LinkedList.h \
    Node.h

FORMS    += \
    image.ui \
    loadurl.ui
