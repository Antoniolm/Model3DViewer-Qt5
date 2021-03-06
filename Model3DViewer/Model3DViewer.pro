#-------------------------------------------------
#
# Project created by QtCreator 2017-07-10T17:52:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Model3DViewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    openglwidget.cpp \
    camera.cpp \
    mesh.cpp \
    fileobj.cpp

HEADERS  += mainwindow.h \
    openglwidget.h \
    camera.h \
    mesh.h \
    fileobj.h

FORMS    += mainwindow.ui

LIBS += -lOpengl32
CONFIG += c++11

RESOURCES += \
    resources.qrc
