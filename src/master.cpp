#include "../inc/master.h"

Master::Master (){

    layout = new QGridLayout;
    layout -> setMargin(0);
    layout -> setSpacing(0);

    stacked = new QStackedWidget;

        
        // Selector

        selector = new Selector;

        connect(selector, SIGNAL(introStack()), this, SLOT(emitIntro()));
        connect(selector, SIGNAL(gameStack(int)), this, SLOT(loadField(int)));

    stacked -> addWidget(selector);


        // Field

        field = new Field;
        
        connect(field, SIGNAL(introStack()), this, SLOT(emitIntro()));
        



    stacked -> setCurrentWidget(selector);

    layout -> addWidget(stacked);

    setLayout(layout);

}


Master::~Master (){

    delete selector;
    delete field;
    delete stacked;
    delete layout;
}



void Master::emitIntro (){

    emit introStack();
}

void Master::loadField (int x){

    stacked -> addWidget(field);
    stacked -> setCurrentWidget(field);
    field -> init();
}
