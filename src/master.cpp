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

        // Go back signal
        connect(selector, SIGNAL(introStack()), this, SLOT(emitIntro()));
        
        // Load Solo Game
        connect(selector, SIGNAL(gameStack(int)), this, SLOT(loadField(int)));

        // Ask for being server
        connect(selector, SIGNAL(createHost(QString)), network, SLOT(go(QString)));

        // Load Host Game
		connect(network, SIGNAL(hostReady(int)), this, SLOT(loadField(int)));
		
        // Ask for being host
        connect(selector, SIGNAL(sendIP(QString)), network, SLOT(mondieu(QString)));

        // Load Joined Game
		connect(network, SIGNAL(connectOK(int)), this, SLOT(loadField(int)));
		
        // Host not found
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

    mode = x;

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
