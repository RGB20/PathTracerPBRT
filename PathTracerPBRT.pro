#-------------------------------------------------
#
# Project created by QtCreator 2019-07-26T19:30:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PathTracerPBRT
TEMPLATE = app
CONFIG += c++11 -pthread
INCLUDEPATH += 3rdpty

SOURCES += main.cpp\
        mainwindow.cpp \
    scene.cpp \
    shape.cpp \
    ray.cpp \
    camera.cpp \
    sphere.cpp \
    plane.cpp \
    polygon.cpp \
    material.cpp \
    diffuse.cpp

HEADERS  += mainwindow.h \
    scene.h \
    shape.h \
    ray.h \
    camera.h \
    sphere.h \
    plane.h \
    polygon.h \
    material.h \
    diffuse.h

FORMS    += mainwindow.ui
