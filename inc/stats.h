#ifndef STATSBOX
#define STATSBOX

#include <QFrame>

#include <QGridLayout>

#include <QLabel>

class Stats : public QFrame {

Q_OBJECT

public:
    
    Stats();
    ~Stats();

private:

    QGridLayout * layout;

    QLabel * label;

};

#endif
