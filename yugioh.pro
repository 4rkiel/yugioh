######################################################################
# Automatically generated by qmake (3.1) Fri Mar 23 21:33:24 2018
######################################################################

QMAKE_CXXFLAGS += -std=c++0x

CONFIG += console
CONFIG += c++11

QT += widgets
QT += network
QT += core

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

# Input
HEADERS += inc/buildtab.h \
           inc/master.h \
           inc/selector.h \
           inc/choice.h \
           inc/soloChoice.h \
           inc/joinChoice.h \
           inc/hostChoice.h \
           inc/netChoice.h \
           inc/duplica.h \
           inc/stats.h \
           inc/history.h \
           inc/chat.h \
           inc/editeur_de_carte.h \
           inc/extAdr.h \
           inc/field.h \
           inc/generique.h \
           inc/genProgress.h \
           inc/helptab.h \
           inc/intro.h \
           inc/main.h \
           inc/optab.h \
           inc/ruletab.h \
           inc/flatButt.h \
           inc/shadowButt.h \
           inc/shadowLab.h \
           inc/sleeper.h \
           inc/slotCard.h \
           inc/zButt.h \ 
    inc/deckedit.h \
    inc/noyau.h \
    inc/parser.h \
    inc/carte.h \
    inc/reseau.h
SOURCES += src/buildtab.cpp \
           src/master.cpp \
           src/selector.cpp \
           src/choice.cpp \
           src/soloChoice.cpp \
           src/joinChoice.cpp \
           src/hostChoice.cpp \
           src/netChoice.cpp \
           src/duplica.cpp \
           src/stats.cpp \
           src/history.cpp \
           src/chat.cpp \
           src/editeur_de_carte.cpp \
           src/extAdr.cpp \
           src/field.cpp \
           src/generique.cpp \
           src/genProgress.cpp \
           src/helptab.cpp \
           src/intro.cpp \
           src/main.cpp \
           src/optab.cpp \
           src/ruletab.cpp \
           src/flatButt.cpp \
           src/shadowButt.cpp \
           src/shadowLab.cpp \
           src/slotCard.cpp \
           src/zButt.cpp \
    src/deckedit.cpp \
    src/noyau.cpp \
    src/parser.cpp \
    src/carte.cpp \
    src/reseau.cpp

           
TRANSLATIONS += i18n/en_US/yugi_en_US.ts i18n/fr_FR/yugi_fr_FR.ts
