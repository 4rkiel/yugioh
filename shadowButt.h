#ifndef SHADOWBUTT
#define SHADOWBUTT

#include <QPushButton>

#include <QGraphicsDropShadowEffect>
#include <QColor>

#include <QThread>

#include "sleeper.h"


class ShadowButt;

class ShadowTask : public QObject {

    Q_OBJECT

    public slots:
    void buttLoop(); 

    signals:
    void newState();
};




class ShadowButt : public QPushButton {

    Q_OBJECT

    public: 
    ShadowButt();
    ~ShadowButt();

    public slots:
    void buttonPressed();
    void buttonReleased();
    void runNewState();

    private:
    QGraphicsDropShadowEffect * effectButt;
    QThread * pressThread;
    ShadowTask * pressTask;
    int lastPosi;
    int state;

    signals:
    void askWait();
    void newState();
};


#endif
