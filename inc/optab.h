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
#include <QEvent>
#include <QShortcut>

#include "../inc/flatButt.h"

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
    QShortcut *shortcut;

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

    QPushButton * optionButt;
    QPushButton * accessButt;

    QWidget * optBox;
    QStackedLayout * optionLayout;

    QScrollArea * optionScroll;
    QWidget * optionScrollBox;
    QVBoxLayout * optPaneLayout;

        QCheckBox * shareChck;
        QLabel * shareDesc;

        QComboBox * langInput;
        QLabel * langDesc;

    QScrollArea * accessScroll;
    QWidget * accessScrollBox;
    QVBoxLayout * accPaneLayout;

        QCheckBox * contrasteChck;
        QLabel * contrasteDesc;

        QCheckBox * achromaChck;
        QLabel * achromaDesc;

        QCheckBox * dyslexChck;
        QLabel * dyslexDesc;

        QCheckBox * largeChck;
        QLabel * largeDesc;

    void updateStyle(QPushButton * b);
    void loadOptSettings();
    void loadAccSettings();
    void changeEvent(QEvent *event);


    public slots:
    void setOption();
    void setAccess();
    void emitClose();

    void shareChange();   
    void contrasteChange();
    void dyslexChange();
    void achromaChange();
    void largeChange();
    void langageChange();

    signals:
    void introStack();
    void newSettings();
};


#endif
