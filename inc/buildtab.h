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
#include <QLabel>
#include <QFile>
#include <QTextStream>
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
    QGraphicsDropShadowEffect * helpEffect;
    QGridLayout * layout;

    QWidget * tabBox;
    QGridLayout * tabLayout;

    QPushButton * currButt;

    QPushButton * helpButt;
    QPushButton * aboutButt;
    ShadowButt * exitButt;

    QWidget * helpBox;
    QStackedLayout * helpLayout;

    QScrollArea * helpScroll;
    QLabel * helpLabel; 

    QScrollArea * aboutScroll;
    QLabel * aboutLabel;

    void updateStyle(QPushButton * b);

    public slots:
    void setHelp();
    void setAbout();
    void emitClose();
    
    signals:
    void introStack();
};


#endif
