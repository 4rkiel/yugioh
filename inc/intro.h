#ifndef INTRO
#define INTRO

#include <QApplication>
#include <QFrame>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QGraphicsDropShadowEffect>

#include <QPushButton>
#include <QString>

#include <QTabWidget>
#include <QShortcut>

#include "../inc/shadowButt.h"

class Intro : public QFrame {

    Q_OBJECT
    
    public:
    Intro();
    ~Intro();
    void init();

    public slots:
    void emitMaster();
    void emitDeck();
    void emitRule();
    void emitOpt();
    void emitHelp();

    signals:
    void masterStack();
    void buildStack();
    void ruleStack();
    void optStack();
    void helpStack();

    private:
    QGridLayout * layout;

    QWidget * infoBox;
    QShortcut *shortcut;
        
        QGraphicsDropShadowEffect * iffect;
        QHBoxLayout * infoLayout;
        QLabel * info;

    
    QWidget * introBox;
    
        QVBoxLayout * box;
        QGraphicsDropShadowEffect * effect;

        ShadowButt * choice;
        ShadowButt * decks;
        ShadowButt * rules;
        ShadowButt * options;
        ShadowButt * help;
        ShadowButt * quit;

};


#endif
