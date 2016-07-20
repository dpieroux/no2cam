TEMPLATE = app

QT += testlib
QT -= gui

CONFIG += c++11
CONFIG += testcase
CONFIG += console
CONFIG -= app_bundle

TARGET = core_tst

INCLUDEPATH += ../..
OBJECTS_DIR = ../../obj
DESTDIR=../../bin

SOURCES += \
    AotfCrystalTest.cpp \
    CoreTest.cpp \
    core_tst.cpp

HEADERS += \
    AotfCrystalTest.h \
    CoreTest.h

INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../bin/ -lcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../bin/ -lcore
else:unix: LIBS += -L$$OUT_PWD/../bin/ -lcore