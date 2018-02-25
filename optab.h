#ifndef TAB
#define TAB

#include <QWidget>
#include <QFrame>

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

#include "shadowButt.h"

class OptionTab : public QFrame {

    Q_OBJECT
    
    public:
    OptionTab();
    ~OptionTab();

    private:
    QGraphicsDropShadowEffect * optEffect;
    QGridLayout * layout;

    QWidget * tabBox;
    QGridLayout * tabLayout;

    QPushButton * currButt;
    
    QPushButton * optionButt;
    QPushButton * accessButt;
    QPushButton * aboutButt;
    ShadowButt * exitButt;

    QWidget * optBox;
    QStackedLayout * optionLayout;
    QScrollArea * aboutScroll;
    QLabel * optionLabel;
    QLabel * accessLabel;
    QLabel * aboutLabel;

    void updateStyle(QPushButton * b);
    
    public slots:
    void setOption();
    void setAccess();
    void setAbout();
    void emitClose();

    signals:
    void introStack();
};


#endif
