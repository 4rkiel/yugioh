#include "genProgress.h"

GenProgress::GenProgress (){

    setMinimum(0);
    setMaximum(100);

    genVal = 0;
    setValue(genVal);

    threadGen = new QThread;
    task = new GenTask;
    task -> moveToThread(threadGen);

    connect( task, SIGNAL(newProgress()), this, SLOT(updateProgress()) );
    
    connect( threadGen, SIGNAL(started()), task, SLOT(runProgress()) );
    
    connect( threadGen, SIGNAL(finished()), task, SLOT(deleteLater()) );
    connect( threadGen, SIGNAL(finished()), threadGen, SLOT(deleteLater()) );

    connect( task, SIGNAL(workFinished()), this, SLOT(deleteProgress()) );
    connect( task, SIGNAL(workFinished()), this, SLOT(sendProgress()) );
    
    threadGen -> start();
}


GenProgress::~GenProgress (){

    if (threadGen != nullptr){
        threadGen -> quit();
    }
}


void GenProgress::sendProgress (){
    emit endProgress();
}


void GenProgress::deleteProgress (){
    threadGen -> quit();
    threadGen = nullptr;
}


void GenProgress::updateProgress(){
    genVal ++;
    setValue(genVal);

    switch (genVal){
        case 25:
        case 50:
        case 75:
            emit newProgress();
            break;
        default:
            break;
    }
}


void GenTask::runProgress (){

    int k;
    for(k=0; k<=100; k++){

        emit newProgress();

        int s = (qrand() % 50);
        Sleeper::msleep(s);
    }

    emit workFinished();
}
