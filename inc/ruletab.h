#ifndef RUTAB
#define RUTAB

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
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QCheckBox>
#include <QSpacerItem>
#include <QEvent>
#include <QShortcut>

#include "../inc/flatButt.h"
#include "../inc/combo.h"

class RuleTab : public QFrame {

    Q_OBJECT
    
    public:
    RuleTab();
    ~RuleTab();
    void init();
    void reInit();

    private:
    QString valeur;
    QShortcut *shortcut;
    QGraphicsDropShadowEffect * ruEffect;
    QGridLayout * layout;

    QWidget * infoBox;

        QGraphicsDropShadowEffect * iffect;
        QHBoxLayout * infoLayout;
        QLabel * info;
        FlatButt * exitButt;

    QWidget * tabInside;
    QGridLayout * tabInsideLayout;

    QWidget * tabBox;
    QGridLayout * tabLayout;

    QPushButton * currButt;

    QPushButton * persoButt;
    QPushButton * rulesButt;

    QWidget * ruleBox;
    QGridLayout * ruleLayout;
	QStackedWidget * ruleStacked;

    QScrollArea * persoScroll;
    QWidget * persoScrollBox;
    QVBoxLayout * persoPaneLayout;
/*
        QCheckBox * shareChck;
        QLabel * shareDesc;

        Combo * langInput;
        QLabel * langDesc;

        QLabel * shortcutDesc;
*/

    Combo* lifePoints;
    QLabel* lifeDesc;
    Combo* cardDrawNumber;
    QLabel* cardDrawDesc;

    QScrollArea * ruleScroll;
    QLabel * ruleLabel;

    void updateStyle(QPushButton * b);
    void loadPersoSettings();
    void readLangage();

    public slots:
    void setPerso();
    void setRules();
    void emitClose();
    void cardDrawNumberChange();
    void lifeChange();
/*
    void shareChange();   
    void contrasteChange();
    void achromaChange();
    void largeChange();
*/
    signals:
    void introStack();
};


#endif
