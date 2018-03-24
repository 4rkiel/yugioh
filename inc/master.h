#ifndef MASTER
#define MASTER

#include <QStackedLayout>

#include "../inc/field.h"

class Master : public QFrame {

Q_OBJECT

public:
    
    Master();
    ~Master();


public slots:

    void emitIntro();


signals:

    void introStack();


private:

    QStackedLayout * layout;
    Field * field;


};

#endif
