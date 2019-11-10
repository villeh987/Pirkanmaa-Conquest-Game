QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += ../../Game/gameeventhandler.hh

SOURCES +=  tst_gameeventhandler.cpp \
            ../../Game/gameeventhandler.cpp
