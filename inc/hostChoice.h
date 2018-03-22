#ifndef HOSTCHOICE
#define HOSTCHOICE

#include <QApplication>
#include <QFrame>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QGraphicsDropShadowEffect>

#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QNetworkInterface>

#include "../inc/shadowButt.h"

class HostChoice : public QFrame {

    Q_OBJECT
    
    public:
    HostChoice();
    ~HostChoice();
    void init();

    public slots:
    void emitChoice();

    signals:
    void choiceStack();

    private:
    QGridLayout * layout;

    QWidget * infoBox;

        QGraphicsDropShadowEffect * iffect;
        QHBoxLayout * infoLayout;
        QLabel * info;
    
    QWidget * introBox;
    
        QGridLayout * box;
        QGraphicsDropShadowEffect * effect;

        QLabel * intro;
        QLabel * phrase;
        QLabel * adr;
        ShadowButt * choice;

};


#endif
