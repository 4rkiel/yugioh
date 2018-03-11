#ifndef OPTAB
#define OPTAB

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

#include "../inc/shadowButt.h"

class OptionTab : public QFrame {

    Q_OBJECT
    
    public:
    OptionTab();
    ~OptionTab();
    void init();
    void reInit();

    private:
    QGraphicsDropShadowEffect * optEffect;
    QGridLayout * layout;

    QWidget * tabBox;
    QGridLayout * tabLayout;

    QPushButton * currButt;

    QPushButton * optionButt;
    QPushButton * accessButt;
    ShadowButt * exitButt;

    QWidget * optBox;
    QStackedLayout * optionLayout;

    QScrollArea * optionScroll;
    QWidget * optionScrollBox;
    QVBoxLayout * optPaneLayout;

        QCheckBox * shareChck;
        QLabel * shareDesc;

        QComboBox * langInput;
        QLabel * langDesc;

        QLabel * shortcutDesc;
    
    QScrollArea * accessScroll;
    QWidget * accessScrollBox;
    QVBoxLayout * accPaneLayout;

        QCheckBox * contrasteChck;
        QLabel * contrasteDesc;

        QCheckBox * achromaChck;
        QLabel * achromaDesc;

        QCheckBox * largeChck;
        QLabel * largeDesc;

    void updateStyle(QPushButton * b);
    void loadOptSettings();
    void loadAccSettings();


    public slots:
    void setOption();
    void setAccess();
    void emitClose();

    void shareChange();   
    void contrasteChange();
    void achromaChange();
    void largeChange();

    signals:
    void introStack();
    void newSettings();
};


#endif
