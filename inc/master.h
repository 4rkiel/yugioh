#ifndef MASTER
#define MASTER

#include <QStackedWidget>
#include <QGridLayout>

#include "../inc/reseau.h"
#include "../inc/field.h"
#include "../inc/selector.h"

#include <iostream>
#include <QString>

class Master : public QFrame {

Q_OBJECT

public:
    
    Master();
    ~Master();


public slots:

    void emitIntro();
    void loadField(int);
	void sendErr(int);
    void test(QString);

signals:

    void introStack();


private:

	int mode;
    QStackedWidget * stacked;
    QGridLayout * layout;
    Field * field;
    Selector * selector;
    Reseau * network;
};

#endif
