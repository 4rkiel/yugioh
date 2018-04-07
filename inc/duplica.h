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
    void setTitle(QString);
   	void setAttr(int);
	void setLevel(int);
	void setPic(QString);
	void setType(int);
    void setDesc(QString);
    void setStat(QString, QString);
	
//    void resizeEvent (QResizeEvent*);

signals:

    void clicked();

private:

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
