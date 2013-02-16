#-------------------------------------------------
#
# Project created by QtCreator 2013-02-13T22:38:35
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += sql
QT       += script
QT       -= gui

TARGET = OMPSS
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    server.cpp \
    task.cpp \
    vrmath.cpp

HEADERS += \
    server.h \
    task.h \
    vrmath.h
