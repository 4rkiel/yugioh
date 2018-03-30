#ifndef SHADOWBUTT
#define SHADOWBUTT

#include <QPushButton>

#include <QHBoxLayout>
#include <QString>
#include <QLabel>

#include <QGraphicsDropShadowEffect>
#include <QColor>

#include <QThread>

#include "../inc/superButt.h"
#include "../inc/sleeper.h"


class ShadowButt;

class ShadowTask : public QObject {

    Q_OBJECT

    public slots:
    void buttLoop(); 

    signals:
    void newState();
};




class ShadowButt : public SuperButt {

    Q_OBJECT

    public: 
    ShadowButt(QString icoStr, QString txtStr);
    ~ShadowButt();
	void setText(QString str);

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
    ShadowTask * pressTask;
    int lastPosi;
    int state;

    signals:
    void askWait();
    void newState();
};


#endif
