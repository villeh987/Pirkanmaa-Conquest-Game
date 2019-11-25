QT += testlib
QT -= gui
QT += core gui widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += ../../Game/gameeventhandler.hh \
           ../../Game/player.hh \
           ../../Course/CourseLib/core/*.h \
           ../../Course/CourseLib/tiles/tilebase.h \
           ../../Course/CourseLib/interfaces/igameeventhandler.h \
           ../../Game/Game_errors/resourceerror.hh


SOURCES +=  tst_gameeventhandler.cpp \
            ../../Game/gameeventhandler.cpp \
            ../../Game/player.cpp \
            ../../Course/CourseLib/core/*.cpp \
            ../../Course/CourseLib/tiles/tilebase.cpp \

INCLUDEPATH += \
            ../../Game \
            ../../Course/CourseLib
