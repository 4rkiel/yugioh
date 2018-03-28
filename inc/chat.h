#ifndef CHATBOX
#define CHATBOX

#include <QFrame>
#include <QWidget>

#include <QGridLayout>
#include <QScrollArea>
#include <QVBoxLayout>

#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QTime>
#include <QShortcut>

#include "../inc/flatButt.h"

class Chat : public QFrame {

Q_OBJECT

public:
    
    Chat();
    ~Chat();
    void addText(QString);

signals:

    void msgSent(QString);


public slots:

    void sendMsg();
    void moveScrollBarToBottom(int,int);

private:

    QGridLayout * layout;
    QShortcut *shortcut;

    QLabel * title;
    QScrollArea * labelBox;
    QWidget * labInner;
    QVBoxLayout * labLayout;
    QLabel * label;
    QLineEdit * input;
    FlatButt * send;

};

#endif
