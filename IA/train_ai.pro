######################################################################
# Automatically generated by qmake (3.1) Fri Mar 23 21:33:24 2018
######################################################################

QMAKE_CXXFLAGS += -std=c++0x

#CONFIG += console
CONFIG += c++11

QT += widgets
QT += network
QT += core

TEMPLATE = app
TARGET = train_ai
OBJECTS_DIR = obj
MOC_DIR = obj
INCLUDEPATH += .

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += ../inc/ai.h \
           AiTrainer.h

SOURCES += ../src/ai.cpp \
           AiTRainer.cpp \
           main.cpp


CONFIG -= console
QT.testlib.CONFIG -= console