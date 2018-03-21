#ifndef DUPLICA
#define DUPLICA

#include <QFrame>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QWidget>

class Duplica : public QFrame {

Q_OBJECT

public:
    
    Duplica();
    ~Duplica();
    void resizeEvent (QResizeEvent*);

private:

    QGraphicsDropShadowEffect * gffect;
    QGridLayout * layout;
    
    QLabel * title;
    QGraphicsDropShadowEffect * effect;
    
    QLabel * pic;

    QWidget * descBox;
    QVBoxLayout * descLayout;
        QLabel * desc;
        QLabel * atk;


};

#endif
