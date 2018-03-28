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

#include <QString>
#include <QShortcut>

#include "../inc/shadowButt.h"
#include "../inc/editeur_de_carte.h"
#include "../inc/deckedit.h"

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
    QPushButton * cardEditButt;
    QPushButton * deckEditButt;
    ShadowButt * exitButt;

    QWidget * buildBox;
    QStackedLayout * buildLayout;

    QScrollArea * deckScroll;
	deckEdit * deck;

    QScrollArea * cardScroll;

    QScrollArea * cardEditScroll;
	editeur_de_carte * editeur;

    void updateStyle(QPushButton * b);


public slots:
    void emitClose();
    void setDeck();
    void setCard();
    void setEditeurCarte();


signals:
    void introStack();
};


#endif
