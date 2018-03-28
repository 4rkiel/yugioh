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
#include <QShortcut>

#include "../inc/shadowButt.h"

class SoloChoice : public QFrame {

    Q_OBJECT
    
    public:
    SoloChoice();
    ~SoloChoice();
    void init();

    public slots:
    void emitBack();
    void emitEasy();
    void emitMed();
    void emitHard();

    signals:
    void choiceStack();
    void gameStack(int);

    private:
    QGridLayout * layout;
    QShortcut *shortcut;

    QWidget * infoBox;

        QGraphicsDropShadowEffect * iffect;
        QHBoxLayout * infoLayout;
        QLabel * info;
    
    QWidget * introBox;
    
        QGridLayout * box;
        QGraphicsDropShadowEffect * effect;

        QLabel * intro;
        ShadowButt * easy;
        ShadowButt * med;
        ShadowButt * hard;
        ShadowButt * choice;

};


#endif
