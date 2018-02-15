#ifndef GENPRO
#define GENPRO

#include <QProgressBar>

#include <QThread>

#include "sleeper.h"


class GenProgress;

class GenTask : public QObject {

    Q_OBJECT

    signals:
    void newProgress();
    void workFinished();

    public slots:
    void runProgress();

};





class GenProgress : public QProgressBar {

    Q_OBJECT

    public: 
    GenProgress();
    ~GenProgress();

    private:
    int genVal;
    QThread * threadGen;
    GenTask * task;

    signals:
    void endProgress();
    void newProgress();

    public slots:
    void updateProgress();
    void sendProgress();
    void deleteProgress();
};


#endif
