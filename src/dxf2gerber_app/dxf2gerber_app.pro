QT += core
QT -= gui

TARGET = dxf2gerber_app
#CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

LIB_LIST = l2_dxf2gerber
DIST_DIR=../../dist/
include (../common.pri)
