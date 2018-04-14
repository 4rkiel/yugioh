#include "../inc/keyfilter.h"

Keyfilter::Keyfilter(){

}

bool Keyfilter::eventFilter(QObject* o,QEvent* event)
{
    if (event->type()==QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if ( (key->key()==Qt::Key_Left) || (key->key()==Qt::Key_Up) ) {
            //up or left
            QKeyEvent * event2 = new QKeyEvent (QEvent::KeyPress,Qt::Key_Tab,Qt::ShiftModifier);
            QApplication::postEvent(o,event2);
        } else if ( (key->key()==Qt::Key_Right) || (key->key()==Qt::Key_Down) ) {
            //up or left
            QKeyEvent * event2 = new QKeyEvent (QEvent::KeyPress,Qt::Key_Tab,Qt::NoModifier);
            QApplication::postEvent(o,event2);
        }
        else {
            return QObject::eventFilter(o,event);
        }
        return true;
    } else {
        return QObject::eventFilter(o,event);
    }
    return false;
}
