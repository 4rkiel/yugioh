#ifndef ZBUTT
#define ZBUTT

#include <QPushButton>
#include <QMouseEvent>
#include "../inc/superButt.h"

class zButt : public SuperButt {

    Q_OBJECT

signals:
    void rightClicked();
    void doubleClicked();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
};


#endif
