#-------------------------------------------------
#
# Project created by QtCreator 2020-10-27T11:41:49
#
#-------------------------------------------------

QT       -= gui

TARGET = $$qtLibraryTarget(l2_dxf2odb)
TEMPLATE = lib

DEFINES += L2_DXF2ODB_LIBRARY

include(../dxflib/dxflib.pri)

SOURCES += \
    l2_dxf2odb.cpp \
    l2_creationadapter.cpp

HEADERS +=\
    l2_dxf2odb.h \
    l2_dxf2odb_global.h \
    l2_creationadapter.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIB_LIST =
DIST_DIR=../../dist/
include (../common.pri)
