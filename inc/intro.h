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

#include "../inc/shadowButt.h"

class Intro : public QFrame {

    Q_OBJECT
    
    public:
    Intro();
    ~Intro();
    void init();

    public slots:
    void emitField();
    void emitRule();
    void emitOpt();
    void emitHelp();

    signals:
    void fieldStack();
    void ruleStack();
    void optStack();
    void helpStack();

    private:
    QGridLayout * layout;
    QWidget * introBox;
    
        QVBoxLayout * box;
        QGraphicsDropShadowEffect * effect;

        ShadowButt * newgame;
        ShadowButt * decks;
        ShadowButt * rules;
        ShadowButt * options;
        ShadowButt * help;
        ShadowButt * quit;

};


#endif
