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

    clean();

    mode = 0;

    choice = new Choice;
    
    connect(choice, SIGNAL(introStack()), this, SLOT(emitIntro()));
    connect(choice, SIGNAL(soloStack()), this, SLOT(soloStack()));
    connect(choice, SIGNAL(joinStack()), this, SLOT(joinStack()));
    connect(choice, SIGNAL(hostStack()), this, SLOT(hostStack()));
    connect(choice, SIGNAL(netStack()), this, SLOT(netStack()));

    stacked -> addWidget(choice);


    stacked -> setCurrentWidget(choice);
    choice -> init();
}


void Selector::soloStack(){

    // Solo Choice

    clean();

    mode = 1;


    soloChoice = new SoloChoice;
    
    connect(soloChoice, SIGNAL(choiceStack()), this, SLOT(choiceStack()));
    connect(soloChoice, SIGNAL(gameStack(int)), this, SLOT(emitGame(int)));
    
    stacked -> addWidget(soloChoice);


    stacked -> setCurrentWidget(soloChoice);
    soloChoice -> init();
}


void Selector::joinStack(){

    // Join Choice

    clean();

    mode = 2;


    joinChoice = new JoinChoice;
    
    connect(joinChoice, SIGNAL(choiceStack()), this, SLOT(choiceStack()));
    
    stacked -> addWidget(joinChoice);


    stacked -> setCurrentWidget(joinChoice);
}


void Selector::hostStack(){

    // Host Choice

    clean();

    mode = 3;


    hostChoice = new HostChoice;
        
    connect(hostChoice, SIGNAL(choiceStack()), this, SLOT(choiceStack()));
        
    stacked -> addWidget(hostChoice);


    stacked -> setCurrentWidget(hostChoice);
}


void Selector::netStack(){

    // Net Choice

    clean();

    mode = 4;


    netChoice = new NetChoice;
    
    connect(netChoice, SIGNAL(choiceStack()), this, SLOT(choiceStack()));
        
    stacked -> addWidget(netChoice);


    stacked -> setCurrentWidget(netChoice);
}


void Selector::emitGame(int x){
    emit gameStack(x);
}
