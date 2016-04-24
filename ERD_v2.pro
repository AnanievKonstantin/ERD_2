#-------------------------------------------------
#
# Project created by QtCreator 2016-04-20T14:09:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ERD_v2
TEMPLATE = app


SOURCES += main.cpp \
    EREssenceData.cpp \
    ERRelationsData.cpp \
    Support.cpp \
    DataController.cpp

HEADERS  += \
    EREnums.h \
    EREssenceData.h \
    ERRelationsData.h \
    Support.h \
    DataController.h
