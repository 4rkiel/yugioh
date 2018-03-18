#ifndef BUILDTAB
#define BUILDTAB

#include <QWidget>
#include <QFrame>

#include <QSettings>

#include <QStyle>
#include <QGraphicsDropShadowEffect>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedLayout>

#include <QScrollArea>
#include <QPushButton>
#include <QCheckBox>
#include <QSpacerItem>
#include <QComboBox>

#include "../inc/shadowButt.h"

class BuildTab : public QFrame {

Q_OBJECT
    
public:
    BuildTab();
    ~BuildTab();
    void init();
    void reInit();


private:
    QGraphicsDropShadowEffect * buildEffect;
    QGridLayout * layout;

    QWidget * infoBox;

        QGraphicsDropShadowEffect * iffect;
        QHBoxLayout * infoLayout;
        QLabel * info;


    QWidget * tabInside;
    QGridLayout * tabInsideLayout;

    QWidget * tabBox;
    QGridLayout * tabLayout;

    QPushButton * currButt;

    QPushButton * deckButt;
    QPushButton * cardButt;
    ShadowButt * exitButt;

    QWidget * buildBox;
    QStackedLayout * buildLayout;

    QScrollArea * deckScroll;

    QScrollArea * cardScroll;

    void updateStyle(QPushButton * b);


public slots:
    void emitClose();
    void setDeck();
    void setCard();


signals:
    void introStack();
};


#endif
