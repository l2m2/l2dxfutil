#-------------------------------------------------
#
# Project created by QtCreator 2020-11-17T15:01:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dxf2gerber_dlg
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

FORMS    += dialog.ui

LIB_LIST = l2_dxf2gerber
DIST_DIR=../../dist/
include (../common.pri)
