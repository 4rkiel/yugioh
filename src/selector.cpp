#include "../inc/selector.h"

Selector::Selector (){

    layout = new QGridLayout;
    layout -> setMargin(0);
    layout -> setSpacing(0);

    stacked = new QStackedWidget;



    // General Choice

        choice = new Choice;
        
        connect(choice, SIGNAL(introStack()), this, SLOT(emitIntro()));
        connect(choice, SIGNAL(soloStack()), this, SLOT(soloStack()));
        connect(choice, SIGNAL(joinStack()), this, SLOT(joinStack()));
        connect(choice, SIGNAL(hostStack()), this, SLOT(hostStack()));
        connect(choice, SIGNAL(netStack()), this, SLOT(netStack()));

    stacked -> addWidget(choice);



    // Solo Choice

        soloChoice = new SoloChoice;
        
        connect(soloChoice, SIGNAL(choiceStack()), this, SLOT(choiceStack()));
        connect(soloChoice, SIGNAL(gameStack(int)), this, SLOT(emitGame(int)));
        
    stacked -> addWidget(soloChoice);



    // Join Choice

        joinChoice = new JoinChoice;
        
        connect(joinChoice, SIGNAL(choiceStack()), this, SLOT(choiceStack()));
        
    stacked -> addWidget(joinChoice);



    // Host Choice

        hostChoice = new HostChoice;
        
        connect(hostChoice, SIGNAL(choiceStack()), this, SLOT(choiceStack()));
        
    stacked -> addWidget(hostChoice);



    // Net Choice

        netChoice = new NetChoice;
        
        connect(netChoice, SIGNAL(choiceStack()), this, SLOT(choiceStack()));
        
    stacked -> addWidget(netChoice);






    stacked -> setCurrentWidget(choice);

    layout -> addWidget(stacked);

    setLayout(layout);

}


Selector::~Selector (){

    delete choice;
    delete soloChoice;
    delete joinChoice;
    delete hostChoice;
    delete netChoice;
    delete stacked;
    delete layout;
}



void Selector::emitIntro (){

    emit introStack();
}

void Selector::choiceStack(){

    stacked -> setCurrentWidget(choice);
}

void Selector::soloStack(){

    stacked -> setCurrentWidget(soloChoice);
}

void Selector::joinStack(){

    stacked -> setCurrentWidget(joinChoice);
}

void Selector::hostStack(){

    stacked -> setCurrentWidget(hostChoice);
}

void Selector::netStack(){

    stacked -> setCurrentWidget(netChoice);
}

void Selector::emitGame(int x){
    emit gameStack(x);
}
