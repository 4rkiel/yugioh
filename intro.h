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
#include "optab.h"

class Intro : public QFrame {

    Q_OBJECT
    
    public:
    Intro();
    ~Intro();
    void init();

    public slots:
    void emitApp();
    void emitOpt();

    signals:
    void appStack();
    void optStack();

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

    OptionTab * optionBox;
};


#endif
