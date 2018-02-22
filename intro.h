#ifndef INTRO
#define INTRO

#include <QApplication>
#include <QFrame>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QGraphicsDropShadowEffect>

#include <QPushButton>
#include <QString>

#include <QTabWidget>


#include "shadowButt.h"


class Intro : public QFrame {

    Q_OBJECT
    
    public:
    Intro();
    ~Intro();
    void init();

    public slots:
    void emitNewStack();
    void showOptions();
    void showRules();
    void showIntro();

    signals:
    void newStack();

    private:
    QGridLayout * layout;
    QWidget * introBox;
    
        QVBoxLayout * box;
        QGraphicsDropShadowEffect * effect;

        ShadowButt * newgame;
        ShadowButt * decks;
        ShadowButt * rules;
        ShadowButt * options;
        ShadowButt * quit;

    QPushButton * shadow;

    QWidget * optionBox;
    QVBoxLayout * optionLayout;
        QTabWidget * tabBox;
        QWidget * optionTab;
        QVBoxLayout * optionTabLayout;
        QLabel * optLabel;
        QWidget * aboutTab;
        QVBoxLayout * aboutTabLayout;
        QLabel * abtLabel;
};


#endif
