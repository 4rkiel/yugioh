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
//        connect(network, SIGNAL(connectOK(int)), this, SLOT(loadField(int)));

        // Host not found
//        connect(network, SIGNAL(connectKO(int)), this, SLOT(sendErr(int)));


    stacked -> addWidget(selector);




    stacked -> setCurrentWidget(selector);

    layout -> addWidget(stacked);

    setLayout(layout);

}


Master::~Master (){

    if (mode != 0){

        if (mode < 10 || mode > 19){

            delete network;

        } else {

            //!\ LUCAS !!!! Ici pour detruire l'IA a la fermeture

            //delete ia;

            // delete monPointeurIA


        }

        delete noyau;
        delete field;

        mThread -> quit();
    }


    delete selector;
    delete stacked;
    delete layout;
}



void Master::emitIntro (){

    emit introStack();
}



void Master::sendErr(int){

}



void Master::loadField (int x){

    mode = x;

    // Field


    field = new Field;
    noyau = new Noyau;


    if (mode >= 10 && mode <= 19){

        delete network;

        // mode pour le niveau de l'IA
        // 11:easy
        // 12:medium
        // 13:hard
        // 14:learning

        int ai_data;

        if(mode >= 11 && mode <= 13)
            ai_data = 1; //file ai.data
        else
            ai_data = 2; //file learning_ai.data

        ai = new Ai(noyau,ai_data);
        
        //le noyau envoi un signal a l'ia pour lui dire de jouer
        //connect(noyau,SIGNAL(au_tour_de_l_ia()),ai,SLOT(a_ton_tour()));
        
        //l'ia envoi un signal au noyau pour lui dire l'action qu'elle effectue
        connect(ai,SIGNAL(attaquer(int,int)),noyau,SLOT(attaquer(int,int)));
        //connect(ai,SIGNAL(defendre(int),noyau,SLOT(defendre(int)));
        //connect(ai,SIGNAL(piocher(int)),noyau,SLOT(piocher(int)));
        
    } else {

		// 

        if (network != NULL){

            connect(network,SIGNAL(a_parser(QString)),noyau,SLOT(traiter(QString)));

        }
            // send Msg // TODO traiter() -> Check if chat message + emit

        if (network != NULL){
            connect(field,SIGNAL(transmettre(QString)),network,SLOT(transmettre(QString)));
        }
        if (network != NULL){
            connect(noyau,SIGNAL(tiens(QString)),network,SLOT(transmettre(QString)));
        }
    }


	connect(noyau, SIGNAL(giveLife(int)), field, SLOT(initLife(int)));
    connect(noyau, SIGNAL(changeLife(int,bool)), field, SLOT(setLife(int,bool)));
    
	connect(noyau, SIGNAL(setTour(int)), field, SLOT(setTour(int)));

	connect(noyau, SIGNAL(sendInfo(QString)), field, SLOT(sendInfo(QString)));


    // Quit

    connect(field, SIGNAL(introStack()), this, SLOT(emitIntro()));


    // New chat msg

    connect(noyau, SIGNAL(chat(QString)), field, SLOT(sendMsg(QString)));







    // set carte

    connect(noyau, SIGNAL(visible(QString, int)), field, SLOT(setCarte(QString, int)));

    // pose carte

    connect(noyau, SIGNAL(defens(int)), field, SLOT(poseCarte(int)));

    // mask carte

    connect(noyau, SIGNAL(nonvis(int)), field, SLOT(maskCarte(int)));

    // rm carte

    connect(noyau, SIGNAL(destruction(int)), field, SLOT(rmCarte(int)));
    connect(field,SIGNAL(sendAtk()),noyau,SLOT(poserAtk()));
    connect(field,SIGNAL(sendDef()),noyau,SLOT(poserDef()));



    //pop-up
    connect(noyau,SIGNAL(dialogue()),field,SLOT(openChoosePosi()));

    //pour poser une carte
    connect(field,SIGNAL(doubleClicked(int)),noyau,SLOT(poser_test(int)));

    //pour switch
    connect(noyau,SIGNAL(change_position(int)),field,SLOT(switchCarte(int)));



	// ask preview
	connect(field,SIGNAL(askPreview(int)),noyau,SLOT(donner_infos(int)));

	// give preview
    connect(noyau,SIGNAL(give_infos(QString,int,int,QString,int,QString,int,int)),
		field, SLOT(cardHover(QString,int,int,QString,int,QString,int,int)));

    // bi clicked
    connect(field,SIGNAL(monstClick(int,int)),noyau,SLOT(attaquerSlot(int,int)));

    stacked -> addWidget(field);
    stacked -> setCurrentWidget(field);

    field -> init();



    // Clock Thread

    mThread = new QThread;
    mTask = new MasterTask;
    mTask -> moveToThread(mThread);


    connect( mTask, SIGNAL(newTick()), this, SLOT(timeTicker()) );
    connect( mTask, SIGNAL(newTick()), mTask, SLOT(masterLoop()) );

    connect( mThread, SIGNAL(finished()), mTask, SLOT(deleteLater()) );
    connect( mThread, SIGNAL(finished()), mThread, SLOT(deleteLater()) );



    mThread -> start();
    mTask -> masterLoop();

    noyau->init();
}


void MasterTask::masterLoop (){

    Sleeper::msleep(50);

    emit newTick();
}



void Master::timeTicker(){
   // std::cout << "Tick\n";

    field -> setProgress();
}












void Master::test(QString str){
    std::cout << str.toStdString() << "\n";
}

//void Master::cut(QString, int, int, bool, bool);
