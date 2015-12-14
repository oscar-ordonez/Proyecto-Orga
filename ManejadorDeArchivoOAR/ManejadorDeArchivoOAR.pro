#-------------------------------------------------
#
# Project created by QtCreator 2015-11-26T17:47:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ManejadorDeArchivoOAR
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    borrarcampos.cpp \
    campo.cpp \
    index.cpp \
    listarcampos.cpp \
    arbolb.cpp \
    nodo.cpp \
    listarregistros.cpp
    listarcampos.cpp

HEADERS  += mainwindow.h \
    borrarcampos.h \
    campo.h \
    index.h \
    listarcampos.h \
    arbolb.h \
    nodo.h \
    listarregistros.h
    listarcampos.h

FORMS    += mainwindow.ui \
    borrarcampos.ui \
    listarcampos.ui \
    listarregistros.ui

RESOURCES += \
    Recursos.qrc
