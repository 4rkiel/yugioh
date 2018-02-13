#include "introButt.h"

IntroButt::IntroButt (){

    effectButt = new QGraphicsDropShadowEffect;
    effectButt -> setBlurRadius(5);
    effectButt -> setXOffset(0);
    effectButt -> setYOffset(5);
    effectButt -> setColor(QColor(0,0,0,200));

    setGraphicsEffect(effectButt);


    lastPosi = 5;


    connect(this, SIGNAL(released()), this, SLOT(buttonReleased()));
    connect(this, SIGNAL(pressed()), this, SLOT(buttonPressed()));

}

IntroButt::~IntroButt (){
    delete effectButt;
}


void Task::runButtonReleased(){

    int k = b -> lastPosi;

    for(; k<=5; k++){

        if (b -> inLock == 1){

            b -> lastPosi = k;

            g -> setBlurRadius(k);
            g -> setYOffset(k);
            b -> setGraphicsEffect(g);

            Sleeper::msleep(42);

        } else {
            break;
        }
    }
    
    emit workFinished();
}




void Task::runButtonPressed(){

    int k = b -> lastPosi;

    for(; k>=0; k--){
        if (b -> inLock == 0){

            b -> lastPosi = k;

            g -> setBlurRadius(k);
            g -> setYOffset(k);
            b -> setGraphicsEffect(g);

            Sleeper::msleep(42);

        } else {
            break;
        }
    }
    
    emit workFinished();
}



void IntroButt::buttonReleased(){

    QThread * threadButt = new QThread;
    Task * task = new Task;
    task -> moveToThread(threadButt);

    connect( threadButt, SIGNAL(started()), task, SLOT(runButtonReleased()) );

    connect( task, SIGNAL(workFinished()), threadButt, SLOT(quit()) );
    connect( threadButt, SIGNAL(finished()), task, SLOT(deleteLater()) );
    connect( threadButt, SIGNAL(finished()), threadButt, SLOT(deleteLater()) );


    task -> g = effectButt;
    task -> b = this;

    inLock = 1;

    threadButt -> start();
}




void IntroButt::buttonPressed(){

    QThread * threadButt = new QThread;
    Task * task = new Task;
    task -> moveToThread(threadButt);

    connect( threadButt, SIGNAL(started()), task, SLOT(runButtonPressed()) );

    connect( task, SIGNAL(workFinished()), threadButt, SLOT(quit()) );
    connect( threadButt, SIGNAL(finished()), task, SLOT(deleteLater()) );
    connect( threadButt, SIGNAL(finished()), threadButt, SLOT(deleteLater()) );

    task -> g = effectButt;
    task -> b = this;

    inLock = 0;

    threadButt -> start();
}
