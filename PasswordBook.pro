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

DESTDIR = ./


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/logindialog.cpp \
    src/addaccinfodialog.cpp \
    src/configopt.cpp \
    src/editaccinfodialog.cpp \
    src/changepwddialog.cpp \
    src/introdialog.cpp

HEADERS  += src/mainwindow.h \
    src/logindialog.h \
    src/defines.h \
    src/addaccinfodialog.h \
    src/configopt.h \
    src/editaccinfodialog.h \
    src/changepwddialog.h \
    src/introdialog.h

FORMS    += src/mainwindow.ui \
    src/logindialog.ui \
    src/addaccinfodialog.ui \
    src/editaccinfodialog.ui \
    src/changepwddialog.ui \
    src/introdialog.ui

RC_FILE += ./ico.rc

OTHER_FILES += \
    ico.rc
