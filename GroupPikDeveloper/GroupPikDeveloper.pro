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
    camerawidget.cpp \
    logindialog.cpp \
    tcpclient.cpp

HEADERS  += mainwindow.h \
    camerawidget.h \
    logindialog.h \
    tcpclient.h

FORMS    += mainwindow.ui \
    camerawidget.ui \
    logindialog.ui

CONFIG += mobility
MOBILITY = 

