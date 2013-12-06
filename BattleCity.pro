#-------------------------------------------------
#
# Project created by QtCreator 2013-12-03T12:08:24
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BattleCity
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    world.cpp \
    tank.cpp \
    wall.cpp \
    bullet.cpp

HEADERS  += mainwindow.h \
    world.h \
    tank.h \
    wall.h \
    bullet.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x
