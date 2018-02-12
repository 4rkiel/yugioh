#ifndef INTRO
#define INTRO

#include <QApplication>
#include <QFrame>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QPushButton>
#include <QIcon>
#include <QString>

#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QThread>

#include "sleeper.h"


class Intro;

class Task : public QObject {
Q_OBJECT
public:
    QGraphicsDropShadowEffect * g;
    QPushButton * b;
    Intro * dad;
public slots:
    void runButtonPressed();
    void runButtonReleased();
signals:
    void workFinished();
};




class Intro : public QFrame {

    Q_OBJECT
    
    public:
    Intro();
    ~Intro();
    QPushButton * button;
    QPushButton * quit;
    int buttLock;
    int quitLock;
    int lastButt;
    int lastQuit;

    public slots:
    void emitNewStack();
    void buttonPressed();
    void buttonReleased();

    signals:
    void newStack();

    private:
    QGraphicsDropShadowEffect * effectButt;
    QGraphicsDropShadowEffect * effectQuit;
    QThread * threadButt;
    Task * task;
};


#endif
