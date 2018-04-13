#ifndef DARKBUTT
#define DARKBUTT

#include <QPushButton>

#include <QHBoxLayout>
#include <QString>
#include <QLabel>

#include <QGraphicsDropShadowEffect>
#include <QColor>

#include <QEvent>
#include <QMouseEvent>

#include <QThread>
#include "../inc/sleeper.h"

#include "../inc/superButt.h"


class DarkButt;

class DarkTask : public QObject {

    Q_OBJECT

    public slots:
    void buttLoop(); 

    signals:
    void newState();
};




class DarkButt : public SuperButt {

    Q_OBJECT

public: 
    DarkButt(QString icoStr, QString txtStr);
    ~DarkButt();
	
    void setText(QString str);
    void setIcon(QString icoStr);
    

public slots:

    void buttonPressed();
    void buttonReleased();
    void runNewState();

private:

    QHBoxLayout * layout;
    QLabel * ico;
    QLabel * txt;
    QGraphicsDropShadowEffect * effectButt;
    QThread * pressThread;
    DarkTask * pressTask;
    int lastPosi;
    int state;

signals:

    void askWait();
    void newState();
};


#endif
