TEMPLATE = app
TARGET = TheGame

QT += core gui widgets

CONFIG += c++14

SOURCES += \
    Game_tiles/water.cpp \
    gameeventhandler.cpp \
    gamescene.cpp \
    main.cpp \
    mapitem.cpp \
    mapwindow.cc \
    Game_buildings/mine.cpp \
    objectmanager.cpp \
    player.cpp \
    startdialog.cpp \
    Game_buildings/supplychain.cpp \
    Game_buildings/tunitower.cpp \
    workerdialog.cpp

HEADERS += \
    Game_tiles/water.hh \
    gameeventhandler.hh \
    gamescene.hh \
    mapitem.hh \
    mapwindow.hh \
    Game_buildings/mine.hh \
    objectmanager.hh \
    player.hh \
    Game_errors/resourceerror.hh \
    Game_resourcemaps/resources.hh \
    startdialog.hh \
    Game_buildings/supplychain.hh \
    Game_buildings/tunitower.hh \
    workerdialog.hh

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

FORMS += \
    mapwindow.ui \
    startdialog.ui \
    workerdialog.ui
