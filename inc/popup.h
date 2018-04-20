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

    void openQuit();
    void openEnd();
    
public slots:

    void emitIntroStack();
    

    void openWin();
    void closeWin();

    void openLost();
    void closeLost();

    void closeEnd();

    void closeQuit();

    void openMenu();
    void closeMenu();


signals:

    void introStack();
    void moiFocus();
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

        
        QWidget * quitBox;
        QGridLayout * quitLayout;

            ShadowButt * quitno;
            ShadowButt * quitya;
            QLabel * quitLabel;

        QWidget * endBox;
        QGridLayout * endLayout;

            ShadowButt * endno;
            ShadowButt * endya;
            QLabel * endLabel;

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


};

#endif
