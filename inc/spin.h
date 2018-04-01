#ifndef SPINBOX
#define SPINBOX

#include <QSpinBox>
#include <QWheelEvent>

class Spin : public QSpinBox {

    Q_OBJECT

public:

    Spin (){
        setFocusPolicy(Qt::StrongFocus);
    }

protected:

    virtual void wheelEvent(QWheelEvent *event) {
        if (!hasFocus()) {
            event->ignore();
        } else {
            QSpinBox::wheelEvent(event);
        }
    }
};

#endif
