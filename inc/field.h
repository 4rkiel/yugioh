#ifndef FIELD
#define FIELD

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

#include <vector>
#include <iostream>

#include "../inc/shadowButt.h"
#include "../inc/shadowLab.h"
#include "../inc/slotCard.h"
#include "../inc/duplica.h"
#include "../inc/stats.h"
#include "../inc/history.h"
#include "../inc/chat.h"


class Field : public QFrame {

Q_OBJECT

public:

    Field();
    ~Field();
    void init();

public slots:
    void emitIntroStack();
    void openMenu();
    void closeMenu();
    void cardHover();
    void cardRightClicked(int x);
    void cardClicked(int x);
    void cardEntered(int x);
    void cardLeaved(int x);

signals:
    void introStack();

public slots:
    void test();
    void setChat();
    void setHisto();
    void setStats();

private:
    QGridLayout * overLayout;
    QWidget * sceneBox;
    QGridLayout * sceneLayout;
    
        std::vector<SlotCard *> * fieldStack;
        
        QWidget * arenaBox;
        QGridLayout * arenaLayout;
      
            QWidget * advBox;
            QGridLayout * advLayout;
                
                QWidget * advHand;
                QHBoxLayout * advHandLayout;
               
                QWidget * advMagic;
                QHBoxLayout * advMagicLayout;
                
                QWidget * advMonst; 
                QHBoxLayout * advMonstLayout; 
                
           QWidget * slfBox;
           QGridLayout * slfLayout;

                QWidget * slfMonst; 
                QHBoxLayout * slfMonstLayout; 
                 
                QWidget * slfMagic; 
                QHBoxLayout * slfMagicLayout; 
                 
                QWidget * slfHand; 
                QHBoxLayout * slfHandLayout; 

        QWidget * rightBarBox;
        QGridLayout * rightBarLayout;
    
            ShadowLab * lifeAdv;
            ShadowLab * intel;
            ShadowButt * actionButt;

            ShadowLab * lifeSlf;
            ShadowButt * menuButt;

            QWidget * sideTool;
            QGridLayout * sideToolLayout;

                QPushButton * statsButt;
                QPushButton * histoButt;
                QPushButton * chatButt;

            QWidget * side;
            QGridLayout * sidebar;

                QWidget * currentSide;
                Duplica * fullCard;
                Stats * stats;
                History * history;
                Chat * chat;


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
