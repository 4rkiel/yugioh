#include "../inc/selector.h"

Selector::Selector (){

    mode = 0;

    layout = new QGridLayout;
    layout -> setMargin(0);
    layout -> setSpacing(0);

    stacked = new QStackedWidget;


        choice = new Choice;

        connect(choice, SIGNAL(introStack()), this, SLOT(emitIntro()));
        connect(choice, SIGNAL(soloStack()), this, SLOT(soloStack()));
        connect(choice, SIGNAL(joinStack()), this, SLOT(joinStack()));
        connect(choice, SIGNAL(hostStack()), this, SLOT(hostStack()));
        connect(choice, SIGNAL(netStack()), this, SLOT(netStack()));

        stacked -> addWidget(choice);


        stacked -> setCurrentWidget(choice);
        choice -> init();


    layout -> addWidget(stacked);

    setLayout(layout);
}



Selector::~Selector (){

    switch (mode){
        case 0:
    
            delete choice;
            break;

        case 1:
        
            delete soloChoice;
            break;

        case 2:
    
            delete joinChoice;
            break;

        case 3:
    
            delete hostChoice;
            break;

        case 4:
        
            delete netChoice;
            break;
    }
    
    
    delete stacked;
    delete layout;
}


void Selector::clean (){

    switch (mode){
        case 0:
            
            delete choice;
            break;

        case 1:

            delete soloChoice;
            break;

        case 2:

            delete joinChoice;
            break;

        case 3:

            delete hostChoice;
            break;

        case 4:

            delete netChoice;
            break;
    }
}


void Selector::emitIntro (){

    emit introStack();
}


void Selector::choiceStack(){

    // General Choice

    choice = new Choice;
    
    stacked -> addWidget(choice);
    stacked -> setCurrentWidget(choice);

    connect(choice, SIGNAL(soloStack()), this, SLOT(soloStack()));
    connect(choice, SIGNAL(joinStack()), this, SLOT(joinStack()));
    connect(choice, SIGNAL(hostStack()), this, SLOT(hostStack()));
    connect(choice, SIGNAL(netStack()), this, SLOT(netStack()));
    connect(choice, SIGNAL(introStack()), this, SLOT(emitIntro()));

    choice -> init();
    
    clean();
    mode = 0;
    
}


void Selector::soloStack(){

    // Solo Choice

    soloChoice = new SoloChoice;
   
    stacked -> addWidget(soloChoice);
    stacked -> setCurrentWidget(soloChoice);
 
    connect(soloChoice, SIGNAL(choiceStack()), this, SLOT(choiceStack()));
    connect(soloChoice, SIGNAL(gameStack(int)), this, SLOT(emitGame(int)));
    
    soloChoice -> init();
    
    clean();
    mode = 1;

}


void Selector::joinStack(){

    // Join Choice

    joinChoice = new JoinChoice;

    stacked -> addWidget(joinChoice);
    stacked -> setCurrentWidget(joinChoice);
    
    connect(joinChoice, SIGNAL(choiceStack()), this, SLOT(choiceStack()));
	connect(joinChoice, SIGNAL(sendIP(QString)), this, SLOT(connectIP(QString)));


    clean();
    mode = 2;


}


void Selector::hostStack(){

    // Host Choice

    hostChoice = new HostChoice;
   
    stacked -> addWidget(hostChoice);
    stacked -> setCurrentWidget(hostChoice);
 
    connect(hostChoice, SIGNAL(choiceStack()), this, SLOT(choiceStack()));
    connect(hostChoice, SIGNAL(createHost(QString)), this, SLOT(transmitHost(QString)));
    
    hostChoice -> init();

    clean();
    mode = 3;


}


void Selector::netStack(){

    // Net Choice

    netChoice = new NetChoice;
    
    stacked -> addWidget(netChoice);
    stacked -> setCurrentWidget(netChoice);
    
    connect(netChoice, SIGNAL(choiceStack()), this, SLOT(choiceStack()));

    clean();
    mode = 4;


}



void Selector::transmitHost(QString str){
	emit createHost(str);
}


void Selector::connectIP(QString str){
    emit sendIP(str);
}


void Selector::emitGame(int x){
    emit gameStack(x);
}
