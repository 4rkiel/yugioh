#ifndef SOLOCHOICE
#define SOLOCHOICE

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

class SoloChoice : public QFrame {

    Q_OBJECT
    
    public:
    SoloChoice();
    ~SoloChoice();
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
        ShadowButt * choice;

};


#endif