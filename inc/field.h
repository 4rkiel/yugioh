#ifndef FIELD
#define FIELD

#include <QApplication>
#include <QFrame>
#include <QWidget>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QScrollArea>

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
    void resizeEvent(QResizeEvent* event);

public slots:

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


    void previewClicked();
    void cardDoubleClicked(int);
    void cardRightClicked(int);
    void cardClicked(int);
    void cardEntered(int);
    void cardLeaved();

    void cardHover(QString, int, int, QString, int, QString, int, int);


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

    void resizeVictor();
    void dealWithHand(int);

    void cardOut();
	void resetProgress();

    int retained;
    int maxPhase;

	bool lockTick;

	bool lockPreview;
	int previewed;

	QString baseLife;
    

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
