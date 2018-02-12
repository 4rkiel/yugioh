#include "intro.h"

Intro::Intro () {

    QGridLayout * layout = new QGridLayout;
    layout -> setAlignment(Qt::AlignCenter);

    QWidget * introBox = new QWidget;
    QVBoxLayout * box = new QVBoxLayout;

    layout -> addWidget(introBox, 0, 0);
    
    introBox -> setLayout(box);


    // Button

    button = new QPushButton("Button", this);
    
    QIcon icoButton("nyancat.png");
    button -> setIcon(icoButton);
    
    QString strButton = QString::fromUtf8("New Game");
    button -> setText(strButton);
    
    button -> setToolTip("Infobulle txt");

    effectButt = new QGraphicsDropShadowEffect;
    effectButt -> setBlurRadius(5);
    effectButt -> setXOffset(0);
    effectButt -> setYOffset(5);
    effectButt -> setColor(QColor(0,0,0,200));
    
    button -> setGraphicsEffect(effectButt);
    
    lastButt = 5;

    box -> addWidget(button);

    connect(button, SIGNAL(released()), this, SLOT(buttonReleased()));
    connect(button, SIGNAL(pressed()), this, SLOT(buttonPressed()));
    connect(button, SIGNAL(clicked()), this, SLOT(emitNewStack()));


    // Quit Button

    quit = new QPushButton("Quit", this);
     
    QIcon icoQuit("nyancat.png");
    quit -> setIcon(icoQuit);
    
    QString strQuit = QString::fromUtf8("Quit");
    quit -> setText(strQuit);
    
    quit -> setToolTip("Infobulle txt");

    effectQuit = new QGraphicsDropShadowEffect;
    effectQuit -> setBlurRadius(5);
    effectQuit -> setXOffset(0);
    effectQuit -> setYOffset(5);
    effectQuit -> setColor(QColor(0,0,0,200));

    quit -> setGraphicsEffect(effectQuit);

    lastQuit = 5;

    box -> addWidget(quit);

    connect(quit, SIGNAL(released()), this, SLOT(buttonReleased()));
    connect(quit, SIGNAL(pressed()), this, SLOT(buttonPressed()));
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));



    this -> setLayout(layout);
}

    
Intro::~Intro (){

    delete button;
    delete quit;
}



void Intro::emitNewStack (){
        emit newStack();
}


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
