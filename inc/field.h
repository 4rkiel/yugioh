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
#include "../inc/flatButt.h"
#include "../inc/shadowLab.h"
#include "../inc/slotCard.h"
#include "../inc/duplica.h"
#include "../inc/stats.h"
#include "../inc/chat.h"


class Field : public QFrame {

Q_OBJECT

public:

    Field();
    ~Field();
    void init();


public slots:

    void test();

    void setChat();
    void setStats();

    void setCarte(QString, int);
    void poseCarte(QString, int);
    void maskCarte(int);
    void rmCarte(int);


    void emitIntroStack();
    void openQuit();
    void closeQuit();
    void openMenu();
    void closeMenu();

    void previewClicked();
    void cardRightClicked(int x);
    void cardClicked(int x);
    void cardEntered(int x);
    void cardLeaved(int x);


signals:
    void introStack();


private:
    
    void cardHover();
    void cardOut();

    bool lockPreview;

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

                FlatButt * statsButt;
                FlatButt * chatButt;

            QWidget * side;
            QGridLayout * sidebar;

                QWidget * currentSide;
                Duplica * fullCard;
                Stats * stats;
                Chat * chat;


    QWidget * popupOuter;
    QGridLayout * popupOuterLayout;
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

        QWidget * menuBox;
        QVBoxLayout * menuLayout;

            ShadowButt * quit;
            ShadowButt * back;
};


#endif
