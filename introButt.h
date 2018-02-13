#ifndef INTROBUTT
#define INTROBUTT

#include <QPushButton>

#include <QGraphicsDropShadowEffect>
#include <QColor>

#include <QThread>

#include "sleeper.h"


class IntroButt;

class Task : public QObject {

    Q_OBJECT

    public:
    QGraphicsDropShadowEffect * g;
    IntroButt * b;

    public slots:
    void runButtonPressed();
    void runButtonReleased();
    
    signals:
    void workFinished();
};





class IntroButt : public QPushButton {

    Q_OBJECT

    public: 
    IntroButt();
    ~IntroButt();
    int lastPosi;
    int inLock;

    public slots:
    void buttonPressed();
    void buttonReleased();

    private:
    QGraphicsDropShadowEffect * effectButt;
};


#endif
