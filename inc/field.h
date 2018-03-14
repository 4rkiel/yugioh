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

#include "../inc/shadowButt.h"
#include "../inc/appIndicator.h"
#include "../inc/slotCard.h"
#include "../inc/slotDeck.h"


class Field : public QFrame {

Q_OBJECT

public:

    Field();
    ~Field();

public slots:
    void emitIntroStack();
    void openMenu();
    void closeMenu();

signals:
    void introStack();

private:
    QGridLayout * overLayout;
    QWidget * sceneBox;
    QGridLayout * sceneLayout;
    
        QWidget * leftBarBox;
        QGridLayout * leftBarLayout;
    
            AppIndicator * lifeAdv;
            AppIndicator * card;
            ShadowButt * actionButt;

        QWidget * arenaBox;
        QGridLayout * arenaLayout;
      
            QWidget * advBox;
            QGridLayout * advLayout;
                
                QWidget * advHand;
                QHBoxLayout * advHandLayout;
               
                    SlotDeck * advHand0;
                    SlotCard * advHand1;
                    SlotCard * advHand2;
                    SlotCard * advHand3;
                    SlotCard * advHand4;
                    SlotCard * advHand5;
                    SlotCard * advHand6;

                QWidget * advMagic;
                QHBoxLayout * advMagicLayout;
                
                    SlotCard * advMagic0;
                    SlotCard * advMagic1;
                    SlotCard * advMagic2;
                    SlotCard * advMagic3;
                    SlotCard * advMagic4;
                    SlotCard * advMagic5;
                    SlotCard * advMagic6;

                QWidget * advMonst; 
                QHBoxLayout * advMonstLayout; 
                 
                    SlotCard * advMonst0;
                    SlotCard * advMonst1;
                    SlotCard * advMonst2;
                    SlotCard * advMonst3;
                    SlotCard * advMonst4;
                    SlotCard * advMonst5;
                    SlotCard * advMonst6;
                
           QWidget * slfBox;
           QGridLayout * slfLayout;

                QWidget * slfMonst; 
                QHBoxLayout * slfMonstLayout; 
                 
                    SlotCard * slfMonst0;
                    SlotCard * slfMonst1;
                    SlotCard * slfMonst2;
                    SlotCard * slfMonst3;
                    SlotCard * slfMonst4;
                    SlotCard * slfMonst5;
                    SlotCard * slfMonst6;

                QWidget * slfMagic; 
                QHBoxLayout * slfMagicLayout; 
                 
                    SlotCard * slfMagic0;
                    SlotCard * slfMagic1;
                    SlotCard * slfMagic2;
                    SlotCard * slfMagic3;
                    SlotCard * slfMagic4;
                    SlotCard * slfMagic5;
                    SlotCard * slfMagic6;

                QWidget * slfHand; 
                QHBoxLayout * slfHandLayout; 

                    SlotCard * slfHand0;
                    SlotCard * slfHand1;
                    SlotCard * slfHand2;
                    SlotCard * slfHand3;
                    SlotCard * slfHand4;
                    SlotCard * slfHand5;
                    SlotDeck * slfHand6;

        QWidget * rightBarBox;
        QVBoxLayout * rightBarLayout;

            AppIndicator * lifeSlf;
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
