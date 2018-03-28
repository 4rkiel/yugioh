#ifndef STATSBOX
#define STATSBOX

#include <QFrame>

#include <QGridLayout>

#include <QLabel>
#include <QString>
#include <QShortcut>

class Stats : public QFrame {

Q_OBJECT

public:
    
    Stats();
    ~Stats();
    
    void setTour(int);
    void setPhase(int);

private:

    QGridLayout * layout;
    QShortcut *shortcut;

    QLabel * title;
    QLabel * tour;
    QLabel * phase;
    QLabel * txtPhase;

    QString ph1;
    QString ph2;
    QString ph3;
    QString ph4;

};

#endif
