#ifndef ZBUTT
#define ZBUTT

#include <QPushButton>
#include <QMouseEvent>

class zButt : public QPushButton {

    Q_OBJECT

public:
	virtual ~zButt() {};

signals:
    void rightClicked();

protected:
    void mousePressEvent(QMouseEvent *e);

};


#endif
