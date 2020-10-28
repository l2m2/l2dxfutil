#-------------------------------------------------
#
# Project created by QtCreator 2020-10-27T11:41:49
#
#-------------------------------------------------

QT       -= gui

TARGET = $$qtLibraryTarget(l2_dxf2gerber)
TEMPLATE = lib

DEFINES += L2_DXF2GERBER_LIBRARY

include(../dxflib/dxflib.pri)

SOURCES += \
    l2_dxfadapter.cpp \
    l2_dxf2gerber.cpp

HEADERS +=\
    l2_dxfadapter.h \
    l2_dxf2gerber_global.h \
    l2_dxf2gerber.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIB_LIST =
DIST_DIR=../../dist/
include (../common.pri)
