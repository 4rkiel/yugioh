#ifndef APP
#define APP

#include <QApplication>
#include <QFrame>
#include <QWidget>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QStackedLayout>

#include <QPushButton>
#include <QString>
#include <QLabel>

#include <QGraphicsDropShadowEffect>

#include "shadowButt.h"

class App : public QFrame {

    Q_OBJECT
 
    public:
    App();
    ~App();

    public slots:
    void emitNewStack();
    void openMenu();
    void closeMenu();

    signals:
    void newStack();

    private:
    QGridLayout * overLayout;
    QWidget * sceneBox;
    QGridLayout * sceneLayout;
    
        QWidget * leftBarBox;
        QVBoxLayout * leftBarLayout;
    
            QLabel * lifeAdv;
        
        QWidget * arenaBox;
        QGridLayout * arenaLayout;
    
        QWidget * rightBarBox;
        QVBoxLayout * rightBarLayout;

            QLabel * lifeSlf;
            ShadowButt * menuButt;

    QWidget * popupOuter;
    QGridLayout * popupOuterLayout;
    QPushButton * popupShadow;
    QWidget * popupBox;
    QStackedLayout * popupLayout;
    
        QWidget * menuOuter;
        QGridLayout * menuOuterLayout;

        QWidget * menuBox;
        QVBoxLayout * menuLayout;

            QGraphicsDropShadowEffect * popupEffect;
            ShadowButt * quit;
            ShadowButt * back;
};


#endif
