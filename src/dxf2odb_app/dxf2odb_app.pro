QT += core
QT -= gui

TARGET = dxf2odb_app
#CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

LIB_LIST = l2_dxf2odb
DIST_DIR=../../dist/
include (../common.pri)
