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
    DataController.cpp \
    Arrow.cpp \
    EREssence.cpp \
    EREssenceBase.cpp \
    EREssenceCharacteristic.cpp \
    EREssenceDesignation.cpp \
    EREssenceProperty.cpp \
    EREssenceRelation.cpp \
    ERGraphicsView.cpp \
    EssenceGraphicsController.cpp \
    EssenseCreateWindow.cpp \
    widget.cpp \
    RelationOperationWindow.cpp \
    TreeModel.cpp \
    TreeItem.cpp \
    TreeModelForOneEssence.cpp

HEADERS  += \
    EREnums.h \
    EREssenceData.h \
    ERRelationsData.h \
    Support.h \
    DataController.h \
    Arrow.h \
    EREssence.h \
    EREssenceBase.h \
    EREssenceCharacteristic.h \
    EREssenceDesignation.h \
    EREssenceProperty.h \
    EREssenceRelation.h \
    ERGraphicsView.h \
    EssenceGraphicsController.h \
    EssenseCreateWindow.h \
    widget.h \
    RelationOperationWindow.h \
    TreeModel.h \
    TreeItem.h \
    TreeModelForOneEssence.h

DISTFILES += \
    ToDo
