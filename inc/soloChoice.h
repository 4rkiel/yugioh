#ifndef SOLOCHOICE
#define SOLOCHOICE

#include <QApplication>
#include <QFrame>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QGraphicsDropShadowEffect>

#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QNetworkInterface>
#include <QShortcut>

#include "../inc/flatExpButt.h"
#include "../inc/flatButt.h"

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
        FlatButt * choice;
    
    QWidget * introBox;
    
        QVBoxLayout * box;
        QGraphicsDropShadowEffect * effect;

        QLabel * intro;
        FlatExpButt * easy;
        FlatExpButt * med;
        FlatExpButt * hard;

        QFrame * sep1;
        QFrame * sep2;


};


#endif
