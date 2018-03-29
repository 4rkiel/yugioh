#include "../inc/master.h"

Master::Master (){

	mode = 0;

	network = new Reseau;


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
        connect(selector, SIGNAL(sendIP(QString)), this, SLOT(test(QString)));
        connect(selector, SIGNAL(sendIP(QString)), network, SLOT(mondieu(QString)));

        // Load Joined Game
		connect(network, SIGNAL(connectOK(int)), this, SLOT(loadField(int)));
		
        // Host not found
        connect(network, SIGNAL(connectKO(int)), this, SLOT(sendErr(int)));
	

    stacked -> addWidget(selector);
       
	


    stacked -> setCurrentWidget(selector);

    layout -> addWidget(stacked);

    setLayout(layout);

}


Master::~Master (){

	if (mode < 10 || mode > 19){
        delete network; 
    }

	if (mode != 0){
        delete noyau;
   		delete field;
    }


	delete selector;
	delete stacked;
    delete layout;
}



void Master::emitIntro (){

    emit introStack();
}


void Master::loadField (int x){

    mode = x;

    if (mode >= 10 && mode <= 19){
        delete network;
    }

	// Field

    noyau = new Noyau;
    field = new Field;

	// Quit 

    connect(field, SIGNAL(introStack()), this, SLOT(emitIntro()));

        connect(noyau, SIGNAL(chat(QString)), field, SLOT(sendMsg(QString)));
    connect(network,SIGNAL(a_parser(QString)),noyau,SLOT(traiter(QString)));

	// send Msg // TODO traiter() -> Check if chat message + emit
  connect(field,SIGNAL(transmettre(QString)),network,SLOT(transmettre(QString)));





	// set carte

    connect(noyau, SIGNAL(visible(QString, int)), field, SLOT(setCarte(QString, int)));

	// pose carte

    connect(noyau, SIGNAL(defens(int)), field, SLOT(poseCarte(int)));

	// mask carte

    connect(noyau, SIGNAL(nonvis(int)), field, SLOT(maskCarte(int)));

	// rm carte

    connect(noyau, SIGNAL(destruction(int)), field, SLOT(rmCarte(int)));


    stacked -> addWidget(field);
    stacked -> setCurrentWidget(field);

	
	field -> init();
}

void Master::sendErr(int){

}

void Master::test(QString str){
    std::cout << str.toStdString() << "\n";
}

//void Master::cut(QString, int, int, bool, bool);
