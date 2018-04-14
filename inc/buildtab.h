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
#include <QStackedWidget>

#include <QScrollArea>
#include <QPushButton>
#include <QCheckBox>
#include <QSpacerItem>
#include <QComboBox>

#include <QString>
#include <QShortcut>

#include "../inc/darkButt.h"
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
    QGridLayout * buildLayout;
    QStackedWidget * buildStacked;

    QScrollArea * deckScroll;
    DeckSelector * deck;

		Parser * parse;
		deckEdit * editor;

    QScrollArea * cardScroll;

    QScrollArea * cardEditScroll;
	CardEditor * editeur;

    QWidget * popup;
	QGridLayout * popLayout;

    DarkButt * closePop;

    DarkButt * addDeck;

    void updateStyle(QPushButton * b);


public slots:

    void emitClose();
    void setDeck();
    void setCard();
    void newDeck();
    void openDeck(QString);
    void closeDeck();

signals:
    void introStack();
    void nousFocus();
    void focusDeck();
};


#endif
