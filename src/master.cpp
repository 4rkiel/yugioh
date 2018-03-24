#include "../inc/master.h"

Master::Master (){

    layout = new QStackedLayout;

    field = new Field;

    connect(field, SIGNAL(introStack()), this, SLOT(emitIntro()));


    layout -> addWidget(field);

    layout -> setCurrentWidget(field);
    setLayout(layout);

    

}


Master::~Master (){

    delete field;
    delete layout;
}



void Master::emitIntro (){

    emit introStack();
}
