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

    void openMagi();
    void closeMagi();
    void visiMode();
    void hideMode();


    void openWin();
    void closeWin();

    void openLost();
    void closeLost();

    void openQuit();
    void closeQuit();

    void openMenu();
    void closeMenu();


signals:

    void introStack();

    void sendAtk();
    void sendDef();
    void moiFocus();

    void sendVisi();
    void sendHide();
    void focusField();


private:

    QWidget * current;
    
    QShortcut * shortcut;
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

        QWidget * magiBox;
        QGridLayout * magiLayout;

            ShadowButt * magiback;
            ShadowButt * magino;
            ShadowButt * magiya;
            QLabel * magiLabel;



        QWidget * quitBox;
        QGridLayout * quitLayout;

            ShadowButt * quitno;
            ShadowButt * quitya;
            QLabel * quitLabel;


        QWidget * winBox;
        QGridLayout * winLayout;

            ShadowButt * winBack;
            ShadowButt * winQuit;
            QLabel * winLabel;

        QWidget * lostBox;
        QGridLayout * lostLayout;

            ShadowButt * lostBack;
            ShadowButt * lostQuit;
            QLabel * lostLabel;

            
            
/*
        QWidget * menuBox;
        QVBoxLayout * menuLayout;

            ShadowButt * quit;
            ShadowButt * back;
*/    

};

#endif
