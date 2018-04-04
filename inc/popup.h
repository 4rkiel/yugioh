#ifndef POPUP
#define POPUP

#include <QWidget>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QStackedLayout>

#include <QPushButton>
#include <QLabel>

#include <QGraphicsDropShadowEffect>

#include <QShortcut>

#include "../inc/shadowButt.h"


class Popup : public QWidget {

Q_OBJECT

public:

    Popup();
    ~Popup();

    
public slots:

    void emitIntroStack();
    
    void openPosi();
    void closePosi();
    void atkMode();
    void defMode();

    void openQuit();
    void closeQuit();
    void openMenu();
    void closeMenu();


signals:

    void introStack();
    void sendAtk();
    void sendDef();

private:

    QWidget * current;
    
    
    QGridLayout * layout;
    QPushButton * popupShadow;
    QWidget * popupBox;
    QGraphicsDropShadowEffect * popupEffect;

    QStackedLayout * popupLayout;

        QWidget * menuOuter;
        QGridLayout * menuOuterLayout;

        
        QWidget * posiBox;
        QGridLayout * posiLayout;

            ShadowButt * posiback;
            ShadowButt * posino;
            ShadowButt * posiya;
            QLabel * posiLabel;


        QWidget * quitBox;
        QGridLayout * quitLayout;

            ShadowButt * quitno;
            ShadowButt * quitya;
            QLabel * quitLabel;

        QWidget * menuBox;
        QVBoxLayout * menuLayout;

            ShadowButt * quit;
            ShadowButt * back;
    

};

#endif
