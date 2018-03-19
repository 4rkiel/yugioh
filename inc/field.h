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

#include "../inc/shadowButt.h"
#include "../inc/appIndicator.h"
#include "../inc/slotCard.h"


class Field : public QFrame {

Q_OBJECT

public:

    Field();
    ~Field();

public slots:
    void emitIntroStack();
    void openMenu();
    void closeMenu();
    void cardHover();

signals:
    void introStack();

public slots:
    void test();


private:
    QGridLayout * overLayout;
    QWidget * sceneBox;
    QGridLayout * sceneLayout;
    
        QWidget * leftBarBox;
        QGridLayout * leftBarLayout;
    
            AppIndicator * lifeAdv;
            AppIndicator * intel;
            ShadowButt * actionButt;


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

            AppIndicator * lifeSlf;
            AppIndicator * fullCard;
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
