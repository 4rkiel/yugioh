######################################################################
# Automatically generated by qmake (3.1) Tue Mar 20 01:59:36 2018
######################################################################

QMAKE_CXXFLAGS += -std=c++0x

CONFIG += console
QT += widgets
QT += network

TEMPLATE = app
TARGET = yugioh
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

HEADERS += inc/buildtab.h \
           inc/choice.h \
           inc/soloChoice.h \
           inc/multiplayerChoice.h \
           inc/joinChoice.h \
           inc/hostChoice.h \
           inc/netChoice.h \
           inc/field.h \
           inc/generique.h \
           inc/genProgress.h \
           inc/helptab.h \
           inc/intro.h \
           inc/main.h \
           inc/optab.h \
           inc/ruletab.h \
           inc/zButt.h \
           inc/shadowButt.h \
           inc/shadowLab.h \
           inc/duplica.h \
           inc/sleeper.h \
           inc/slotCard.h \
	   inc/editeur_de_carte.h

SOURCES += src/buildtab.cpp \
           src/choice.cpp \
           src/soloChoice.cpp \
           src/multiplayerChoice.cpp \
           src/joinChoice.cpp \
           src/hostChoice.cpp \
           src/netChoice.cpp \
           src/field.cpp \
           src/generique.cpp \
           src/genProgress.cpp \
           src/helptab.cpp \
           src/intro.cpp \
           src/main.cpp \
           src/optab.cpp \
           src/ruletab.cpp \
           src/zButt.cpp \
           src/shadowButt.cpp \
           src/shadowLab.cpp \
           src/duplica.cpp \
           src/slotCard.cpp \
	   src/editeur_de_carte.cpp
