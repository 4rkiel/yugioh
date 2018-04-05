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

#include <QSettings>
#include <QProgressBar>

#include <QStyle>

#include <vector>
#include <QShortcut>

#include "../inc/shadowButt.h"
#include "../inc/flatButt.h"
#include "../inc/shadowLab.h"
#include "../inc/slotCard.h"
#include "../inc/duplica.h"
#include "../inc/stats.h"
#include "../inc/chat.h"
#include "../inc/popup.h"


#include <iostream>


class Field : public QFrame {

Q_OBJECT

public:

    Field();
    ~Field();
    void init();


public slots:

    void setProgress();

    void setPhase(int);
    void setTour(int);
	void sendMsg(QString);

    void setCarte(QString, int);
    void poseCarte(int);
    void maskCarte(int);
    void rmCarte(int);
	void switchCarte(int);

    void emitIntroStack();
    void emitAtk();
    void emitDef();
    void openChoosePosi();

    void previewClicked();
    void cardDoubleClicked(int x);
    void cardRightClicked(int x);
    void cardClicked(int x);
    void cardEntered(int x);
    void cardLeaved(int x);


signals:

    void introStack();
    void sendAtk();
    void sendDef();
    void transmettre(QString);
	void doubleClicked(int);
	void biClick(int, int);


private:
    
    void cardHover();
    void cardOut();

    int retained;
    bool lockPreview;
    QString baseLife;
    

    QGridLayout * layout;

    QWidget * infoBox;

        QGraphicsDropShadowEffect * iffect;
        QHBoxLayout * infoLayout;

        QWidget * lifeBox;
        QHBoxLayout * lifeLayout;
        QLabel * lifeAdv;
        QLabel * icoAdv;
        QProgressBar * progressAdv;
        QLabel * icoLife;
        QLabel * lifeSlf;
        QLabel * icoSlf;
        QProgressBar * progressSlf;
        FlatButt * menuButt;


    QWidget * overField;
    QGridLayout * overLayout;
    QWidget * sceneBox;
    QGridLayout * sceneLayout;
    QShortcut * shortcut;
    Popup * popup;
    
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
    
            QWidget * side;
            QGridLayout * sidebar;

                Duplica * fullCard;
                Chat * chat;

};


#endif
