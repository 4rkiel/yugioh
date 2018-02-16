#include "shadowButt.h"

ShadowButt::ShadowButt (){

    effectButt = new QGraphicsDropShadowEffect(this);
    effectButt -> setBlurRadius(5);
    effectButt -> setXOffset(0);
    effectButt -> setYOffset(5);
    effectButt -> setColor(QColor(0,0,0,150));

    setGraphicsEffect(effectButt);


    lastPosi = 5;

    connect(this, SIGNAL(released()), this, SLOT(buttonReleased()));
    connect(this, SIGNAL(pressed()), this, SLOT(buttonPressed()));


    // run thread 

    pressThread = new QThread;
    pressTask = new ShadowTask;
    pressTask -> moveToThread(pressThread);


    connect( this, SIGNAL(askWait()), pressTask, SLOT(buttLoop()) );
    connect( this, SIGNAL(newState()), this, SLOT(runNewState()) );
    connect( pressTask, SIGNAL(newState()), this, SLOT(runNewState()) );

    connect( pressThread, SIGNAL(finished()), pressTask, SLOT(deleteLater()) );
    connect( pressThread, SIGNAL(finished()), pressThread, SLOT(deleteLater()) );

    pressThread -> start();

}



ShadowButt::~ShadowButt (){

    delete effectButt;

    pressThread -> quit();
}



void ShadowTask::buttLoop (){

    Sleeper::msleep(42);

    emit newState();

}


void ShadowButt::buttonPressed(){

    state = 0;
    
    emit newState();
}



void ShadowButt::buttonReleased(){

    state = 1;

    emit newState();
}



void ShadowButt::runNewState (){

    if (state == 0 && lastPosi > 1){

        lastPosi -- ;

        emit askWait();

    } else if (state == 1 && lastPosi < 5){

        lastPosi ++ ;
        
        emit askWait();
    }

    effectButt -> setBlurRadius(lastPosi);
    effectButt -> setYOffset(lastPosi);

    effectButt -> update();
}

