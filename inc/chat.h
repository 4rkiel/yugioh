#ifndef CHATBOX
#define CHATBOX

#include <QFrame>
#include <QWidget>

#include <QGridLayout>
#include <QScrollArea>
#include <QVBoxLayout>

#include <QLabel>
#include <QTextEdit>
#include <QString>
#include <QLineEdit>
#include <QTime>
#include <QShortcut>


#include "../inc/darkButt.h"

class Chat : public QFrame {

Q_OBJECT

public:
    
    Chat();
    ~Chat();
    void addText(QString, int);
    void goFocus();

signals:

    void msgSent(QString);
    void rcvQuit();


public slots:

    void sendMsg();
    void moveScrollBarToBottom(int,int);
    void openQuit();

private:

    int last;

    QShortcut* shortcut;
    QGridLayout * layout;

    QScrollArea * labelBox;
    QWidget * labInner;
    QVBoxLayout * labLayout;
    QTextEdit * label;
    QLineEdit * input;
    DarkButt * send;

};

#endif
