#ifndef FIELD
#define FIELD

#include <QApplication>
#include <QFrame>
#include <QWidget>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QScrollArea>
#include <QScrollBar>

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
#include "../inc/minipopup.h"
#include "../inc/carte.h"


#include <iostream>


class Field : public QFrame {

Q_OBJECT

public:

    Field();
    ~Field();
    void init();
    

public slots:

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void switchChat();
    void switchField();
    void getsFocus();
    void abandonFocus();
    void setProgress();
    void setTour(int);
	void sendMsg(QString);
	void sendInfo(QString);

	void unlockTick();
	void relockTick();

	void setLife(int, bool);
	void initLife(int);

	void reveal(QString, int);
    void setCarte(QString, int);
    void poseCarte(int);
    void maskCarte(int);
    void rmCarte(int);
	void switchCarte(int);

    void emitIntroStack();
    void emitAtk();
    void emitDef();
    void emitVisi();
    void emitHide();
    void openChoosePosi();
    void openChooseMagi();
    void openWin();
    void openLost();
    void openQuit();

    void miniClose();
    void miniReopen();

    void previewClicked();
    void cardDoubleClicked(int);
    void cardRightClicked(int);
    void cardClicked(int);
    void cardEntered(int);
    void cardLeaved();

    void cardHover(Carte *);


signals:

    void introStack();
    void sendAtk();
    void sendDef();
    void sendVisi();
    void sendHide();
    void transmettre(QString);
	void doubleClicked(int);
	void monstClick(int, int);
	void askPreview(int);


private:

//    void resizeVictor();
    void dealWithHand(int);
    void readLangage();

    void cardOut();
	void resetProgress();
    int plusDroite_Self();

    void miniSave();

    int retained;
    int maxPhase;

	bool lockTick;
    bool miniPopSave;

	bool lockPreview;
	int previewed;

	QString baseLife;
    QString langage;
    

    QGridLayout * layout;

    QWidget * infoBox;

        QGraphicsDropShadowEffect * iffect;
        QHBoxLayout * infoLayout;

        QWidget * lifeBox;
        QGridLayout * lifeLayout;
        QLabel * lifeAdv;
        QLabel * icoAdv;
        QProgressBar * progressAdv;
        QLabel * icoLife;
        QProgressBar * progressLeft;
        QProgressBar * progressRight;
        QLabel * lifeSlf;
        QLabel * icoSlf;
        QProgressBar * progressSlf;
        FlatButt * menuButt;


    QWidget * overField;
    QGridLayout * overLayout;
    QWidget * sceneBox;
    QGridLayout * sceneLayout;
    QShortcut * shortcut;
    QShortcut * shortcut2;
    QShortcut * shortcut3;
    QShortcut * shortcut4;
    QShortcut * shortcut5;
    Popup * popup;
    
        std::vector<SlotCard *> * fieldStack;
        
        QWidget * arenaBox;
        QGridLayout * arenaLayout;

        MiniPopup * minipop;


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

                QScrollArea * slfScroll;
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
