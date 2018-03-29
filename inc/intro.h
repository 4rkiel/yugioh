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

#include "../inc/flatButt.h"
#include "../inc/flatExpButt.h"

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
    QShortcut * shortcut;
        
        QGraphicsDropShadowEffect * iffect;
        QHBoxLayout * infoLayout;
        QLabel * info;
        FlatButt * quit;

    
    QWidget * introBox;
    
        QVBoxLayout * box;
        QGraphicsDropShadowEffect * effect;

        FlatExpButt * choice;
        FlatExpButt * decks;
        FlatExpButt * rules;
        FlatExpButt * options;
        FlatExpButt * help;

		QFrame * sep1;
		QFrame * sep2;
		QFrame * sep3;
		QFrame * sep4;
};


#endif
