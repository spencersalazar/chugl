
QT += core gui opengl

CONFIG += warn_off

win32 {
    CONFIG += static
}

TARGET = chugl
TEMPLATE = lib
CONFIG += plugin
TARGET_EXT = chug

CONFIG += build_all

MAKEFILE = makefile.qt
MOC_DIR = build
RCC_DIR = build
UI_DIR = build
OBJECTS_DIR = build

CFLAGS += -D__QT__

macx-* {
CFLAGS += -D__MACOSX_CORE__ -I../chuck/src
QMAKE_CXXFLAGS += $$CFLAGS
QMAKE_CFLAGS += $$CFLAGS
QMAKE_LIBS += 
QMAKE_LFLAGS += -Wl,-undefined,dynamic_lookup
QMAKE_LFLAGS_SONAME = chugl.chug
}

linux-* {
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE += -O3
QMAKE_LFLAGS_RELEASE -= -O1

CFLAGS += -D__LINUX__ -D__PLATFORM_LINUX__ -I../chuck/src 
QMAKE_CXXFLAGS += $$CFLAGS
QMAKE_CFLAGS += $$CFLAGS
QMAKE_LFLAGS +=
LIBS += -lstdc++ -lm -ldl
}

win32 {
DEFINES -= UNICODE
CFLAGS += -D__PLATFORM_WIN32__ -D__WINDOWS_DS__ -I../chuck/src -DWIN32 -D_WINDOWS
QMAKE_CXXFLAGS += $$CFLAGS
QMAKE_CFLAGS += $$CFLAGS
QMAKE_LFLAGS += 
}

SOURCES += \
    chugl.cpp \
    chugl_api.cpp \
    chugl_qt.cpp \
    ui/chuck_ui.cpp \
    ui/chuck_ui_qt.cpp \
    ui/util_icon.cpp

HEADERS += \
    chugl.h \
    chugl_api.h \
    chugl_util.h \
    chugl_opengl.h \
    ui/chuck_ui.h \
    ui/chuck_ui_qt.h \
    ui/util_icon.h

GENGL_SRC= genchugin.py

gengl.input = GENGL_SRC
gengl.output = chugl_opengl.cpp
gengl.commands = PYTHONPATH=\"\$PYTHONPATH:OpenGL\" python genchugin.py
gengl.depends = OpenGL/gl.xml ck.py genchugin.py
gengl.variable_out = SOURCES
gengl.name = gengl
QMAKE_EXTRA_COMPILERS += gengl


