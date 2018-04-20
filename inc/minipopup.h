#ifndef MINIPOPUP
#define MINIPOPUP

#include <QWidget>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QStackedLayout>

#include <QPushButton>
#include <QLabel>

#include <QGraphicsDropShadowEffect>

#include <QShortcut>

#include <vector>

#include "../inc/shadowButt.h"
#include "../inc/popCard.h"
#include "../inc/carte.h"

class MiniPopup : public QWidget {

Q_OBJECT

public:

    MiniPopup();
    ~MiniPopup();

    
public slots:

    void emitIntroStack();
    
    void openPosi();
    void closePosi();
    void atkMode();
    void defMode();

    void openMagi();
    void closeMagi();
    void visiMode();
    void hideMode();

    void cardClicked(int);

    void openSee(std::vector <Carte *> *);
    void openChoose(int, std::vector <Carte *> *);
    void openChooseLocked(int, std::vector <Carte *> *);
    void populate(std::vector <Carte *> *);
    void closeSee();

    void openMenu();
    void checkCloseMenu();
    void closeMenu();


signals:

    void introStack();

    void sendAtk();
    void sendDef();
    void moiFocus();

    void sendVisi();
    void sendHide();
    void focusField();

    void chosenOne(std::vector<int>);

private:

    std::vector <int> stock;

    bool locked;
    bool waiting;
    int need;

    QWidget * current;
    
    QShortcut * shortcut;
    QGridLayout * layout;
    QPushButton * popupShadow;
    QWidget * popupBox;
    QGraphicsDropShadowEffect * popupEffect;

    QStackedLayout * popupLayout;

        QWidget * menuOuter;
        QGridLayout * menuOuterLayout;

        
        QWidget * posiBox;
        QGridLayout * posiLayout;

            ShadowButt * posiback;
            ShadowButt * posino;
            ShadowButt * posiya;
            QLabel * posiLabel;

        QWidget * magiBox;
        QGridLayout * magiLayout;

            ShadowButt * magiback;
            ShadowButt * magino;
            ShadowButt * magiya;
            QLabel * magiLabel;


        QWidget * seeBox;
        QGridLayout * seeLayout;

            QLabel * seeLabel;
            
            QWidget * seeList;
            QGridLayout * listLayout;
            
            ShadowButt * seeBack;


};

#endif
