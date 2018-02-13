#ifndef INTRO
#define INTRO

#include <QApplication>
#include <QFrame>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QPushButton>
#include <QIcon>
#include <QString>

#include "introButt.h"



class Intro : public QFrame {

    Q_OBJECT
    
    public:
    Intro();
    ~Intro();

    public slots:
    void emitNewStack();

    signals:
    void newStack();

    private:
    IntroButt * newgame;
    IntroButt * options;
    IntroButt * rules;
    IntroButt * quit;
 
};


#endif
