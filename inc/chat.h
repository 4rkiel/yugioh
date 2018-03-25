#ifndef CHATBOX
#define CHATBOX

#include <QFrame>

#include <QGridLayout>

#include <QLabel>

class Chat : public QFrame {

Q_OBJECT

public:
    
    Chat();
    ~Chat();

private:

    QGridLayout * layout;

    QLabel * label;

};

#endif
