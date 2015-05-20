#-------------------------------------------------
#
# Project created by QtCreator 2015-05-20T20:59:59
#
#-------------------------------------------------

QT       += core gui

QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PasswordBook
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/logindialog.cpp

HEADERS  += src/mainwindow.h \
    src/logindialog.h

FORMS    += src/mainwindow.ui \
    src/logindialog.ui
