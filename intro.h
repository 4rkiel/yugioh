#ifndef INTRO
#define INTRO

#include <QApplication>
#include <QFrame>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QGraphicsDropShadowEffect>

#include <QPushButton>
#include <QIcon>
#include <QString>

#include "shadowButt.h"



class Intro : public QFrame {

    Q_OBJECT
    
    public:
    Intro();
    ~Intro();
    void init();

    public slots:
    void emitNewStack();

    signals:
    void newStack();

    private:
    QGridLayout * layout;
    QWidget * introBox;
    QVBoxLayout * box;

    QGraphicsDropShadowEffect * effect;

    ShadowButt * newgame;
    ShadowButt * options;
    ShadowButt * rules;
    ShadowButt * quit;
 
};


#endif
