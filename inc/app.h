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
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QPropertyAnimation>


#include <QThread>

#include "../inc/sleeper.h"

#include "../inc/shadowButt.h"
#include "../inc/appIndicator.h"
#include "../inc/card.h"


class App;

class AppTask : public QObject {

    Q_OBJECT

    public slots:
    void appLoop();

    signals:
    void newState();

};

class App : public QFrame {

    Q_OBJECT
    //Q_PROPERTY(QTransform transfrom READ transform WRITE setTransform)

    public:
    App();
    ~App();
    void init();
    void resizeEvent(QResizeEvent *);

    public slots:
    void emitIntroStack();
    void openMenu();
    void closeMenu();
    void runNewState();

    signals:
    void introStack();
    void askWait();
    void newState();

    private:
    void rotateXApp();
    void rotateYApp(int x);
        
    QThread * appThread;
    AppTask * appTask;

    int lastPosi;

    QGridLayout * overLayout;
    QWidget * sceneBox;
    QGridLayout * sceneLayout;
    
        QWidget * leftBarBox;
        QGridLayout * leftBarLayout;
    
            AppIndicator * lifeAdv;
            AppIndicator * card;
            ShadowButt * actionButt;

        QGraphicsView * arenaView;
        QGraphicsScene * arenaScene;
        QGraphicsProxyWidget * arenaProxy;
        QPropertyAnimation * arenaAnim;
        
        QWidget * arenaBox;
        QGridLayout * arenaLayout;
      
            QWidget * advBox;
            QGridLayout * advLayout;
                
                QWidget * advHand;
                QHBoxLayout * advHandLayout;
               
                    Card * advHand0;
                    Card * advHand1;
                    Card * advHand2;
                    Card * advHand3;
                    Card * advHand4;
                    Card * advHand5;
                    Card * advHand6;

                QWidget * advMagic;
                QHBoxLayout * advMagicLayout;
                
                    Card * advMagic0;
                    Card * advMagic1;
                    Card * advMagic2;
                    Card * advMagic3;
                    Card * advMagic4;
                    Card * advMagic5;
                    Card * advMagic6;

                QWidget * advMonst; 
                QHBoxLayout * advMonstLayout; 
                 
                    Card * advMonst0;
                    Card * advMonst1;
                    Card * advMonst2;
                    Card * advMonst3;
                    Card * advMonst4;
                    Card * advMonst5;
                    Card * advMonst6;
                
           QWidget * slfBox;
           QGridLayout * slfLayout;

                QWidget * slfMonst; 
                QHBoxLayout * slfMonstLayout; 
                 
                    Card * slfMonst0;
                    Card * slfMonst1;
                    Card * slfMonst2;
                    Card * slfMonst3;
                    Card * slfMonst4;
                    Card * slfMonst5;
                    Card * slfMonst6;

                QWidget * slfMagic; 
                QHBoxLayout * slfMagicLayout; 
                 
                    Card * slfMagic0;
                    Card * slfMagic1;
                    Card * slfMagic2;
                    Card * slfMagic3;
                    Card * slfMagic4;
                    Card * slfMagic5;
                    Card * slfMagic6;

                QWidget * slfHand; 
                QHBoxLayout * slfHandLayout; 

                    Card * slfHand0;
                    Card * slfHand1;
                    Card * slfHand2;
                    Card * slfHand3;
                    Card * slfHand4;
                    Card * slfHand5;
                    Card * slfHand6;

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
