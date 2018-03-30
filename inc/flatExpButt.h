#ifndef FLATEXPBUTT
#define FLATEXPBUTT

#include <QPushButton>

//#include <QHBoxLayout>
//#include <QVBoxLayout>
#include <QGridLayout>
//#include <QWidget>
#include <QString>
#include <QLabel>

#include "../inc/superButt.h"

class FlatExpButt : public SuperButt {

    Q_OBJECT

    public: 
    FlatExpButt(QString icoStr, QString txtStr);
    ~FlatExpButt();

    private:
//	QVBoxLayout * vlay;
//	QWidget * wid;
	QGridLayout * layout;
    QLabel * ico;
    QLabel * txt;
};


#endif
