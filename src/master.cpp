#include "../inc/master.h"

Master::Master (){

	mode = 0;

	Reseau * network = new Reseau;


    layout = new QGridLayout;
    layout -> setMargin(0);
    layout -> setSpacing(0);

    stacked = new QStackedWidget;

        
        // Selector

        selector = new Selector;

        connect(selector, SIGNAL(introStack()), this, SLOT(emitIntro()));
        connect(selector, SIGNAL(gameStack(int)), this, SLOT(loadField(int)));
        connect(selector, SIGNAL(createHost(QString)), network, SLOT(go(QString)));

		connect(network, SIGNAL(hostReady(int)), this, SLOT(loadField(int)));
		connect(selector, SIGNAL(sendIP(QString)), network, SLOT(mondieu(QString)));

		connect(network, SIGNAL(connectOK(int)), this, SLOT(loadField(int)));
		connect(network, SIGNAL(connectKO()), this, SLOT(sendErr()));
	

    stacked -> addWidget(selector);
       
	


    stacked -> setCurrentWidget(selector);

    layout -> addWidget(stacked);

    setLayout(layout);

}


Master::~Master (){

	if (mode == 0){

    	delete selector;
	
	} else {

    	delete field;
	}
    
	delete stacked;
    delete layout;
}



void Master::emitIntro (){

    emit introStack();
}

void Master::loadField (int x){


	// Field

    field = new Field;
        
    connect(field, SIGNAL(introStack()), this, SLOT(emitIntro()));
 
    stacked -> addWidget(field);
    stacked -> setCurrentWidget(field);

	delete selector;
	
	field -> init();
}

void Master::sendErr(){

}
