TEMPLATE = app
TARGET = TheGame

QT += core gui widgets

CONFIG += c++14

SOURCES += \
    Game_tiles/rock.cpp \
    Game_tiles/water.cpp \
    Game_dialogs/endgamedialog.cpp \
    Game_dialogs/fightdialog.cpp \
    Game_dialogs/buildingdialog.cpp \
    Game_dialogs/confirmdialog.cpp \
    gameeventhandler.cpp \
    gamescene.cpp \
    main.cpp \
    mapitem.cpp \
    mapwindow.cc \
    Game_buildings/mine.cpp \
    Game_workers/miner.cpp \
    objectmanager.cpp \
    player.cpp \
    Game_dialogs/startdialog.cpp \
    Game_buildings/tunitower.cpp \
    Game_workers/teekkari.cpp \
    styles.cpp \
    Game_dialogs/workerdialog.cpp \
    Game_tiles/lava.cpp

HEADERS += \
    Game_tiles/rock.hh \
    Game_tiles/water.hh \
    Game_dialogs/buildingdialog.hh \
    Game_dialogs/confirmdialog.hh \
    constants.hh \
    Game_dialogs/endgamedialog.hh \
    Game_dialogs/fightdialog.hh \
    gameeventhandler.hh \
    gamescene.hh \
    mapitem.hh \
    mapwindow.hh \
    Game_buildings/mine.hh \
    Game_workers/miner.hh \
    objectmanager.hh \
    player.hh \
    Game_errors/resourceerror.hh \
    Game_resourcemaps/resources.hh \
    Game_dialogs/startdialog.hh \
    Game_buildings/tunitower.hh \
    Game_workers/teekkari.hh \
    styles.hh \
    Game_dialogs/workerdialog.hh \
    Game_tiles/lava.hh

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
    buildingdialog.ui \
    confirmdialog.ui \
    endgamedialog.ui \
    fightdialog.ui \
    mapwindow.ui \
    startdialog.ui \
    workerdialog.ui
