#-------------------------------------------------
#
# Project created by QtCreator 2014-04-25T15:11:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BoardGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Models/Space.cpp \
    initgame.cpp \
    Models/Player.cpp

HEADERS  += mainwindow.h \
    Models/Space.h \
    initgame.h \
    Models/Player.h

FORMS    += mainwindow.ui \
    initgame.ui

RESOURCES += \
    resource.qrc
RC_FILE = mono.rc
