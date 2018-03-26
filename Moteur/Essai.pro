#-------------------------------------------------
#
# Project created by QtCreator 2018-03-16T12:52:09
#
#-------------------------------------------------
CONFIG += c++11
QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Essai
TEMPLATE = app


SOURCES += main.cpp\
        essai.cpp \
    noyau.cpp \
    carte.cpp \
    reseau.cpp \
    parser.cpp 

HEADERS  += essai.h \
    noyau.h \
    carte.h \
    reseau.h \
    parser.h 
