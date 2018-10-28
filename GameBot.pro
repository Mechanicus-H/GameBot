#-------------------------------------------------
#
# Project created by QtCreator 2018-10-16T23:45:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameBot
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp\
        gamebot.cpp \
    action.cpp

HEADERS  += gamebot.h \
    action.h

RC_FILE += \
    resources.rc
