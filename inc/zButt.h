#ifndef ZBUTT
#define ZBUTT

#include <QPushButton>
#include <QMouseEvent>

class zButt : public QPushButton {

    Q_OBJECT

signals:
    void rightClicked();
    void doubleClicked();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);

};


#endif
