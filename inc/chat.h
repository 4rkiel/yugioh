#ifndef CHATBOX
#define CHATBOX

#include <QFrame>

#include <QGridLayout>

#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QTime>

#include "../inc/flatButt.h"

class Chat : public QFrame {

Q_OBJECT

public:
    
    Chat();
    ~Chat();
    void addText(QString);

private:

    QGridLayout * layout;

    QLabel * title;
    QLabel * label;
    QLineEdit * input;
    FlatButt * send;

};

#endif
