#-------------------------------------------------
#
# Project created by QtCreator 2016-11-21T12:40:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Phonebook
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    adddialog.cpp \
    phonebook.cpp

HEADERS  += mainwindow.h \
    adddialog.h \
    phonebook.h

FORMS    += mainwindow.ui \
    add_dialog.ui
