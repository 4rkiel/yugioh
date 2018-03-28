#ifndef DUPLICA
#define DUPLICA

#include <QFrame>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QWidget>
#include <QPushButton>
#include <QShortcut>

class Duplica : public QFrame {

Q_OBJECT

public:
    
    Duplica();
    ~Duplica();
    void setTitle(QString str);
    void setPic(QString str);
    void setDesc(QString str);
    void setStat(QString strAtk, QString strDef);
    //    void resizeEvent (QResizeEvent*);

signals:

    void clicked();

private:

    void mousePressEvent (QMouseEvent *);

    QGraphicsDropShadowEffect * gffect;
    QGridLayout * layout;
    QShortcut *shortcut;
    QLabel * title;
    QGraphicsDropShadowEffect * effect;
    
    QLabel * pic;

    QScrollArea * descBox;
    QVBoxLayout * descLayout;
        QLabel * desc;
        QLabel * atk;


};

#endif
