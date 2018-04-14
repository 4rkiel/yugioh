#ifndef MASTER
#define MASTER

#include <QStackedWidget>
#include <QGridLayout>

#include "../inc/ai_main.h"
#include "../inc/ai_battle.h"
#include "../inc/reseau.h"
#include "../inc/noyau.h"
#include "../inc/field.h"
#include "../inc/selector.h"

#include <QString>
#include <iostream>
#include <QShortcut>

#include <QThread>
#include "../inc/sleeper.h"


class MasterTask : public QObject {

Q_OBJECT;

public:

	bool threadLock;


public slots:

    void masterLoop();


signals:
    
    void newTick();

};


class Master : public QFrame {

Q_OBJECT

public:
    
    Master();
    ~Master();
	


public slots:

    void emitIntro();
	void sendErr(int);
    void loadField(int);
	
    void timeTicker();
	void stopTick();


signals:

    void introStack();


private:

	int mode;
    QStackedWidget * stacked;
    QShortcut *shortcut;
    QGridLayout * layout;
    Field * field;
    Selector * selector;
    Reseau * network;
    Noyau * noyau;
    Ai_main * ai_main;
    Ai_battle * ai_battle;

    QThread * mThread;
    MasterTask * mTask;
};

#endif
