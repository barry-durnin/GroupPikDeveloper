#-------------------------------------------------
#
# Project created by QtCreator 2016-05-16T21:13:48
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GroupPikDeveloper
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    camerawidget.cpp

HEADERS  += mainwindow.h \
    camerawidget.h

FORMS    += mainwindow.ui \
    cameradialog.ui \
    camerawidget.ui

CONFIG += mobility
MOBILITY = 

