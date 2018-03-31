#ifndef STATSBOX
#define STATSBOX

#include <QFrame>

#include <QGridLayout>

#include <QLabel>
#include <QString>
#include <QProgressBar>

class Stats : public QFrame {

Q_OBJECT

public:
    
    Stats();
    ~Stats();
    
    void setTour(int);
    void setPhase(int);
    void resetProgress();
    void incProgress();


private:

    int state;

    QGridLayout * layout;

    QLabel * title;
    QLabel * tour;
    QLabel * phase;
    QLabel * txtPhase;

    QProgressBar * progress;

    QString ph1;
    QString ph2;
    QString ph3;
    QString ph4;

};

#endif
