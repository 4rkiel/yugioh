#ifndef FLATBUTT
#define FLATBUTT

#include <QPushButton>

#include <QHBoxLayout>
#include <QString>
#include <QLabel>

#include "../inc/superButt.h"

class FlatButt : public SuperButt {

    Q_OBJECT

    public: 
    FlatButt(QString icoStr, QString txtStr);
    ~FlatButt();

    private:
	QHBoxLayout * layout;
    QLabel * ico;
    QLabel * txt;
};


#endif
