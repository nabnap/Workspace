#-------------------------------------------------
#
# Project created by QtCreator 2016-12-06T15:40:28
#
#-------------------------------------------------

QT       += core gui webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = broooser
TEMPLATE = app

SOURCES += main.cpp\
        browserwindow.cpp \
    browser.cpp \
    tabwidget.cpp \
    urlline.cpp \
    webview.cpp \
    jsonmanager.cpp

HEADERS  += browserwindow.h \
    browser.h \
    tabwidget.h \
    urlline.h \
    webview.h \
    jsonmanager.h
RESOURCES += data/broooser.qrc
win32:RC_ICONS += simplebrowser.ico
