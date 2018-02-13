#include "intro.h"

Intro::Intro () {

    QGridLayout * layout = new QGridLayout;
    layout -> setAlignment(Qt::AlignCenter);

    QWidget * introBox = new QWidget;
    QVBoxLayout * box = new QVBoxLayout;


    // New Game Button

    newgame = new IntroButt;
    
    QIcon icoButton("nyancat.png");
    newgame -> setIcon(icoButton);
    
    QString strButton = QString::fromUtf8("New Game");
    newgame -> setText(strButton);
    
    newgame -> setToolTip("Infobulle txt");

    connect(newgame, SIGNAL(clicked()), this, SLOT(emitNewStack()));
    
    box -> addWidget(newgame);


    // Options Button

    options = new IntroButt;
    
    QIcon icoOptions("nyancat.png");
    options -> setIcon(icoOptions);
    
    QString strOptions = QString::fromUtf8("Options");
    options -> setText(strOptions);
    
    options -> setToolTip("Infobulle txt");

    box -> addWidget(options);




    // Quit Button

    quit = new IntroButt;
     
    QIcon icoQuit("nyancat.png");
    quit -> setIcon(icoQuit);
    
    QString strQuit = QString::fromUtf8("Quit");
    quit -> setText(strQuit);
    
    quit -> setToolTip("Infobulle txt");

    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    
    box -> addWidget(quit);



    layout -> addWidget(introBox, 0, 0);

    introBox -> setLayout(box);

    this -> setLayout(layout);
}

    
Intro::~Intro (){

    delete newgame;
    delete options;
    delete quit;
}



void Intro::emitNewStack (){
        emit newStack();
}

/*
void Task::runButtonReleased(){

    int k = 0;
    
    if (b == dad -> button){
        k = dad -> lastButt;
    } else if (b == dad -> quit){
        k = dad -> lastQuit;
    }
  
    for(; k<=5; k++){
    
        if (b == dad -> button && dad -> buttLock == 1){

            dad -> lastButt = k;
 
            g -> setBlurRadius(k);
            g -> setYOffset(k);
            b -> setGraphicsEffect(g);
            
            Sleeper::msleep(42);

        } else if (b == dad -> quit && dad -> quitLock == 1) {
 
            dad -> lastQuit = k;
            
            g -> setBlurRadius(k);
            g -> setYOffset(k);
            b -> setGraphicsEffect(g);
            
            Sleeper::msleep(42);
        
        } else {
            break;
        }
    }
}


void Task::runButtonPressed(){

    int k = 0;
   
    if (b == dad -> button){
        k = dad -> lastButt;
    } else if (b == dad -> quit){
        k = dad -> lastQuit;
    }
   
    for(; k>=0; k--){
        if (b == dad -> button && dad -> buttLock == 0){
         
            dad -> lastButt = k;

            g -> setBlurRadius(k);
            g -> setYOffset(k);
            b -> setGraphicsEffect(g);
            Sleeper::msleep(42);
            
        } else if (b == dad -> quit && dad -> quitLock == 0) {
         
            dad -> lastQuit = k;

            g -> setBlurRadius(k);
            g -> setYOffset(k);
            b -> setGraphicsEffect(g);
            Sleeper::msleep(42);

        } else {
            break;
        }
    }
}


void Intro::buttonReleased(){

    threadButt = new QThread;
    task = new Task;
    task -> moveToThread(threadButt);

    connect( threadButt, SIGNAL(started()), task, SLOT(runButtonReleased()) );

    connect( task, SIGNAL(workFinished()), threadButt, SLOT(quit()) );
    connect( threadButt, SIGNAL(finished()), task, SLOT(deleteLater()) );
    connect( threadButt, SIGNAL(finished()), threadButt, SLOT(deleteLater()) );

    if (sender() == button){
    
        task -> g = effectButt;
        task -> b = button;

        task -> dad = this;
        buttLock = 1;

        threadButt -> start();

    } else if (sender() == quit){
     
        task -> g = effectQuit;
        task -> b = quit;
    
        task -> dad = this;
        quitLock = 1;

        threadButt -> start();
    }
}


void Intro::buttonPressed(){

    threadButt = new QThread;
    task = new Task;
    task -> moveToThread(threadButt);

    connect( threadButt, SIGNAL(started()), task, SLOT(runButtonPressed()) );

    connect( task, SIGNAL(workFinished()), threadButt, SLOT(quit()) );
    connect( threadButt, SIGNAL(finished()), task, SLOT(deleteLater()) );
    connect( threadButt, SIGNAL(finished()), threadButt, SLOT(deleteLater()) );

    if (sender() == button){
    
        task -> g = effectButt;
        task -> b = button;
        
        task -> dad = this;
        buttLock = 0;

        threadButt -> start();

    } else if (sender() == quit){
     
        task -> g = effectQuit;
        task -> b = quit;
    
        task -> dad = this;
        quitLock = 0;

        threadButt -> start();
    }
}

*/
