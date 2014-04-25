#-------------------------------------------------
#
# Project created by QtCreator 2014-04-25T15:11:19
#
#-------------------------------------------------

QT       += core gui

TARGET = BoardGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Models/Player.cpp \
    Models/GameBoard.cpp \
    Models/Space.cpp \
    country.cpp

HEADERS  += mainwindow.h \
    Models/Player.h \
    Models/GameBoard.h \
    Models/Space.h \
    country.h

FORMS    += mainwindow.ui
