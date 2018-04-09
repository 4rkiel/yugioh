#ifndef FLATEXPBUTT
#define FLATEXPBUTT

#include <QPushButton>

//#include <QHBoxLayout>
//#include <QVBoxLayout>
#include <QGridLayout>
//#include <QWidget>
#include <QString>
#include <QLabel>

#include <QEvent>
#include <QPixmap>
#include <QMouseEvent>

#include "../inc/superButt.h"

class FlatExpButt : public SuperButt {

    Q_OBJECT

public: 
    
    FlatExpButt(QString icoStr, QString txtStr);
    FlatExpButt(const QPixmap image, QString textStr);
    ~FlatExpButt();
    
    void leaveEvent(QEvent * event);
    void enterEvent(QEvent * event);


private:

	QGridLayout * layout;
    QLabel * ico;
    QLabel * txt;
};


#endif
