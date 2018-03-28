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
#include <QStackedLayout>

#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QCheckBox>
#include <QSpacerItem>
#include <QComboBox>
#include <QEvent>

#include "../inc/shadowButt.h"

class RuleTab : public QFrame {

    Q_OBJECT
    
    public:
    RuleTab();
    ~RuleTab();
    void init();
    void reInit();

    private:
    QString valeur;
    QGraphicsDropShadowEffect * ruEffect;
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

    QPushButton * persoButt;
    QPushButton * rulesButt;
    ShadowButt * exitButt;

    QWidget * ruleBox;
    QStackedLayout * ruleLayout;

    QScrollArea * persoScroll;
    QWidget * persoScrollBox;
    QVBoxLayout * persoPaneLayout;
/*
        QCheckBox * shareChck;
        QLabel * shareDesc;

        QComboBox * langInput;
        QLabel * langDesc;

        QLabel * shortcutDesc;
*/

    QComboBox* lifePoints;
    QLabel* lifeDesc;
    QComboBox* cardDrawNumber;
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
