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
#include "../inc/flatButt.h"
#include "../inc/cardEditor.h"
#include "../inc/deckedit.h"
#include "../inc/parser.h"
#include "../inc/deckselector.h"

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
        FlatButt * exitButt;

    QShortcut* shortcut;
    QWidget * tabInside;
    QGridLayout * tabInsideLayout;

    QWidget * tabBox;
    QGridLayout * tabLayout;

    QPushButton * currButt;

    QPushButton * deckButt;
    QPushButton * cardButt;
    QPushButton * cardEditButt;
    QPushButton * deckEditButt;

    QWidget * buildBox;
    QStackedLayout * buildLayout;

    QScrollArea * deckScroll;
    deckEdit * deck;
    //DeckSelector* deck;

    QScrollArea * cardScroll;

    QScrollArea * cardEditScroll;
	CardEditor * editeur;

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
