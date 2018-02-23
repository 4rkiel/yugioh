#ifndef TAB
#define TAB

#include <QWidget>
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>

#include <QGraphicsDropShadowEffect>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QTextStream>

class OptionTab : public QWidget {

    Q_OBJECT
    
    public:
    OptionTab();
    ~OptionTab();
    virtual void paintEvent(QPaintEvent *);

    private:
    QGraphicsDropShadowEffect * effect;
    QVBoxLayout * optionLayout;
    QWidget * tabBox;
    QHBoxLayout * tabLayout;

    QPushButton * optionButt;
    QPushButton * accessButt;
    QPushButton * aboutButt;
    QPushButton * exitButt;

    QScrollArea * aboutScroll;
    QLabel * optionLabel;
    QLabel * accessLabel;
    QLabel * aboutLabel;

    public slots:
    void setOption();
    void setAccess();
    void setAbout();
    void emitClose();

    signals:
    void closeTab();
};


#endif
