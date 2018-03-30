#ifndef HELPTAB
#define HELPTAB

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
#include <QShortcut>

#include "../inc/flatButt.h"

class HelpTab : public QFrame {

    Q_OBJECT
    
    public:
    HelpTab();
    ~HelpTab();
    void init();
    void reInit();

    private:
    QString valeur;
    QShortcut* shortcut;
    QGraphicsDropShadowEffect * helpEffect;
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

    QPushButton * helpButt;
    QPushButton * aboutButt;

    QWidget * helpBox;
    QStackedLayout * helpLayout;

    QScrollArea * helpScroll;
    QLabel * helpLabel; 

    QScrollArea * aboutScroll;
    QLabel * aboutLabel;

    void updateStyle(QPushButton * b);
    void readLangage();

    public slots:
    void setHelp();
    void setAbout();
    void emitClose();
    
    signals:
    void introStack();
};


#endif
