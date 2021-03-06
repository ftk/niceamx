TEMPLATE = lib
CONFIG += plugin
CONFIG -= qt

DEFINES += WIN32 OVERTIMER_DISABLE

SOURCES += $$files(../system/*.cpp)
SOURCES += $$files(../system/pawn/*.cpp)
SOURCES += $$files(../system/SDK/*.cpp)

SOURCES += $$files(../util/*.cpp)
SOURCES += $$files(../api/*.cpp)
SOURCES += $$files(../modules/*.cpp)

HEADERS += $$files(../system/*.h)
HEADERS += $$files(../system/pawn/*.h)
HEADERS += $$files(../system/SDK/*.h)
HEADERS += $$files(../system/SDK/amx/*.h)

HEADERS += $$files(../util/*.h)
HEADERS += $$files(../util/config/*.h)
HEADERS += $$files(../api/*.h)
HEADERS += $$files(../modules/*.h)

HEADERS += $$files(../system/*.hpp)
HEADERS += $$files(../system/pawn/*.hpp)
HEADERS += $$files(../system/SDK/*.hpp)

HEADERS += $$files(../util/*.hpp)
HEADERS += $$files(../api/*.hpp)
HEADERS += $$files(../modules/*.hpp)


INCLUDEPATH += ../
INCLUDEPATH += ../system

INCLUDEPATH += ../../boost-trunk/

QMAKE_CXXFLAGS += -std=c++11 -Wno-unused-local-typedefs
QMAKE_LFLAGS_PLUGIN += -Wl,--enable-stdcall-fixup -Wl,--kill-at

DEF_FILE = win/plugin.def





