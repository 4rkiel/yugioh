#ifndef KEYFILTER
#define KEYFILTER

#include <QApplication>
#include <QFrame>
#include <QString>
#include <QEvent>
#include <iostream>
#include <sstream>
#include <QKeyEvent>
#include <QLineEdit>
#include <QTextEdit>
#include "slotCard.h"
#include "combo.h"

class Keyfilter : public QObject {

    Q_OBJECT

    public:
    Keyfilter();

    public slots:

    signals:

    private:

    protected:
    bool eventFilter(QObject *, QEvent *);


};


#endif
