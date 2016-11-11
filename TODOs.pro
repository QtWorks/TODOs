#-------------------------------------------------
#
# Project created by QtCreator 2016-10-27T23:33:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TODOs
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    TODOs.cpp \
    MenuToolBar.cpp \
    GroupWidget.cpp \
    ElementWidget.cpp \
    GroupHeaderWidget.cpp \
    HeaderWidget.cpp \
    ParametersDialog.cpp \
    StatusBar.cpp

HEADERS  += MainWindow.h \
    TODOs.h \
    MenuToolBar.h \
    GroupWidget.h \
    ElementWidget.h \
    GroupHeaderWidget.h \
    HeaderWidget.h \
    ParametersDialog.h \
    StatusBar.h

RESOURCES += \
    resources.qrc
