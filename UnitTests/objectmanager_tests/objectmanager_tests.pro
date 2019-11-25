QT += testlib
QT -= gui
QT += core gui widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += ../../Game/gameeventhandler.hh \
           ../../Game/objectmanager.hh \
           ../../Game/player.hh \
           ../../Course/CourseLib/core/*.h \
           ../../Course/CourseLib/tiles/tilebase.h \
           ../../Game/Game_tiles/*.hh \
           ../../Course/CourseLib/interfaces/igameeventhandler.h \
           ../../Course/CourseLib/interfaces/iobjectmanager.h \
           ../../Game/Game_errors/resourceerror.hh \
           ../../Course/CourseLib/buildings/buildingbase.h
           #../../Game/Game_buildings/*.hh


SOURCES +=  tst_objectmanager.cpp \
            ../../Game/gameeventhandler.cpp \
            ../../Game/objectmanager.cpp \
            ../../Game/player.cpp \
            ../../Course/CourseLib/core/*.cpp \
            ../../Course/CourseLib/tiles/tilebase.cpp \
            ../../Game/Game_tiles/*.cpp \
            ../../Course/CourseLib/buildings/buildingbase.cpp
           #../../Game/Game_buildings/*.cpp

INCLUDEPATH += \
            ../../Game \
            ../../Course/CourseLib
