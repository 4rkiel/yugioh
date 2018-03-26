#ifndef HISTOBOX
#define HISTOBOX

#include <QFrame>

#include <QGridLayout>

#include <QLabel>

class History : public QFrame {

Q_OBJECT

public:
    
    History();
    ~History();

private:

    QGridLayout * layout;

    QLabel * label;

};

#endif
