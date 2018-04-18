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

#include <QFont>

#include "../inc/carte.h"

class Duplica : public QFrame {

Q_OBJECT

public:
    
    Duplica();
    ~Duplica();
    
    void reInit(Carte *);
   
//    void resizeEvent (QResizeEvent*);

signals:

    void clicked();

private:
 
    void setTitle(QString);
   	void setAttr(QString);
	void setLevel(int);
    void setSpellType(int);
    void setTrapType(int);
	void setPic(QString);
	void setType(int, int);
	void hideType();
    void setDesc(QString);
    void setStat(QString, QString);
	void hideStat();
    void setSpellColor();
    void setTrapColor();
    void setColor(int);

    void mousePressEvent (QMouseEvent *);

    QGraphicsDropShadowEffect * gffect;
    QGridLayout * layout;
    QShortcut *shortcut;
   
    QWidget * titleBox;
    QHBoxLayout * titleLayout;
    QGraphicsDropShadowEffect * effect;
    QLabel * title;
    QLabel * attr;

    QWidget * typeBox;
    QHBoxLayout * typeLayout;

    QLabel * pic;

    QScrollArea * descBox;
    QVBoxLayout * descLayout;
        QLabel * type;
        QLabel * desc;
        QLabel * atk;


};

#endif
