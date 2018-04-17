#ifndef MINIPOPUP
#define MINIPOPUP

#include <QWidget>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QStackedLayout>

#include <QPushButton>
#include <QLabel>

#include <QGraphicsDropShadowEffect>

#include <QShortcut>

#include "../inc/shadowButt.h"


class MiniPopup : public QWidget {

Q_OBJECT

public:

    MiniPopup();
    ~MiniPopup();

    
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


    void openSee();
    void openChoose();
    void openChooseLocked();
    void closeSee();

    void openMenu();
    void checkCloseMenu();
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

    bool locked;

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


        QWidget * seeBox;
        QGridLayout * seeLayout;

            ShadowButt * seeBack;
            QLabel * seeLabel;

            
            
/*
        QWidget * menuBox;
        QVBoxLayout * menuLayout;

            ShadowButt * quit;
            ShadowButt * back;
*/    

};

#endif
