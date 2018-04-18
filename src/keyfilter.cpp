#include "../inc/keyfilter.h"

Keyfilter::Keyfilter(){

}

bool Keyfilter::eventFilter(QObject* o,QEvent* event){

    QLineEdit* temp=NULL;
    if (event->type()==QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);

        if ( (key->key()==Qt::Key_Left) || (key->key()==Qt::Key_Up) ) {
            //up or left
            if((temp=static_cast<QLineEdit*>(qApp->focusObject()))!=NULL && QString(qApp->focusObject()->metaObject()->className())=="QLineEdit"){
                if(temp->text().isEmpty()){
                    QKeyEvent * event2 = new QKeyEvent (QEvent::KeyPress,Qt::Key_Tab,Qt::ShiftModifier);
                    QApplication::postEvent(o,event2);
                }
                else return QObject::eventFilter(o,event);
            }
            else{
                QKeyEvent * event2 = new QKeyEvent (QEvent::KeyPress,Qt::Key_Tab,Qt::ShiftModifier);
                QApplication::postEvent(o,event2);
            }
        }

         else if ( (key->key()==Qt::Key_Right) || (key->key()==Qt::Key_Down) ) {
            //right or down
            if((temp=static_cast<QLineEdit*>(qApp->focusObject()))!=NULL && QString(qApp->focusObject()->metaObject()->className())=="QLineEdit"){
                if(temp->text().isEmpty()){
                    QKeyEvent * event2 = new QKeyEvent (QEvent::KeyPress,Qt::Key_Tab,Qt::NoModifier);
                    QApplication::postEvent(o,event2);
                }
                else return QObject::eventFilter(o,event);
            }
            else{
                QKeyEvent * event2 = new QKeyEvent (QEvent::KeyPress,Qt::Key_Tab,Qt::NoModifier);
                QApplication::postEvent(o,event2);
            }
        }

        else if ( (key->key()==Qt::Key_Return) ) {
             //return
             if((temp=static_cast<QLineEdit*>(qApp->focusObject()))!=NULL && QString(qApp->focusObject()->metaObject()->className())!="QLineEdit"){
                 QKeyEvent * event2 = new QKeyEvent (QEvent::KeyPress,Qt::Key_Space,Qt::NoModifier);
                 QApplication::postEvent(o,event2);
                 QKeyEvent * event3 = new QKeyEvent (QEvent::KeyRelease,Qt::Key_Space,Qt::NoModifier);
                 QApplication::postEvent(o,event3);
             }
             else return QObject::eventFilter(o,event);
        }

        else {
            return QObject::eventFilter(o,event);
        }
        return true;
    }
    else {
        return QObject::eventFilter(o,event);
    }
    return false;
}
