CONFIG += c++11

#QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -std=c++11

#CONFIG += console

QT += widgets
QT += network
QT += core
QT -= gui

TARGET = serveur
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    monserveur.cpp

HEADERS += \
    monserveur.h

