#ifndef COMBO
#define COMBO

#include <QComboBox>
#include <QWheelEvent>

class Combo : public QComboBox {

    Q_OBJECT

public:

    Combo (){
        setFocusPolicy(Qt::StrongFocus);
    }

protected:

    virtual void wheelEvent(QWheelEvent * event){
        if (!hasFocus()) {
            event->ignore();
        } else {
            QComboBox::wheelEvent(event);
        }
    }
};

#endif
