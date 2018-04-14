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

        int ai_mode;

        if(mode >= 11 && mode <= 13)
            ai_mode = 1; //file ai.data
        else
            ai_mode = 2; //file learning_ai.data

        ai = new Ai(noyau,ai_mode,2);//joueur 2
        
        //le noyau envoi un signal a l'ia pour lui dire de jouer
        //connect(noyau,SIGNAL(au_tour_de_l_ia()),ai,SLOT(a_ton_tour()));
        
        //l'ia envoi un signal au noyau pour lui dire l'action qu'elle effectue
        
        connect(ai,SIGNAL(attaquer(int,int)),noyau,SLOT(attaquer(int,int)));
        
        connect(ai,SIGNAL(poser(int,int,bool,bool)),noyau,SLOT(poser(int,int,bool,bool)));
        
        connect(ai,SIGNAL(switch_position(int)),noyau,SLOT(switch_position(int)));
        
        connect(ai,SIGNAL(detruire(int)),noyau,SLOT(detruire(int)));
        
    } else {

		// 

        if (network != NULL){

            connect(network,SIGNAL(a_parser(QString)),noyau,SLOT(traiter(QString)),Qt::QueuedConnection);

        }
            // send Msg // TODO traiter() -> Check if chat message + emit

        if (network != NULL){
            connect(field,SIGNAL(transmettre(QString)),network,SLOT(transmettre(QString)));
        }
        if (network != NULL){
            connect(noyau,SIGNAL(tiens(QString)),network,SLOT(transmettre(QString)));
        }
    }


    connect(noyau, SIGNAL(beginTour()), field, SLOT(unlockTick()),Qt::QueuedConnection);

    connect(noyau, SIGNAL(giveLife(int)), field, SLOT(initLife(int)),Qt::QueuedConnection);
    connect(noyau, SIGNAL(changeLife(int,bool)), field, SLOT(setLife(int,bool)),Qt::QueuedConnection);
    
    connect(noyau, SIGNAL(setTour(int)), field, SLOT(setTour(int)),Qt::QueuedConnection);

    connect(noyau, SIGNAL(sendInfo(QString)), field, SLOT(sendInfo(QString)));


    // Quit

    connect(field, SIGNAL(introStack()), this, SLOT(emitIntro()),Qt::QueuedConnection);


    // New chat msg

    connect(noyau, SIGNAL(chat(QString)), field, SLOT(sendMsg(QString)));







    // set carte

    connect(noyau, SIGNAL(visible(QString, int)), field, SLOT(setCarte(QString, int)),Qt::QueuedConnection);

    // pose carte

    connect(noyau, SIGNAL(defens(int)), field, SLOT(poseCarte(int)),Qt::QueuedConnection);

    // mask carte

    connect(noyau, SIGNAL(nonvis(int)), field, SLOT(maskCarte(int)),Qt::QueuedConnection);

    // rm carte

    connect(noyau, SIGNAL(destruction(int)), field, SLOT(rmCarte(int)),Qt::QueuedConnection);
    connect(field,SIGNAL(sendAtk()),noyau,SLOT(poserAtk()),Qt::QueuedConnection);
    connect(field,SIGNAL(sendDef()),noyau,SLOT(poserDef()),Qt::QueuedConnection);



    //pop-up
    connect(noyau,SIGNAL(dialogue()),field,SLOT(openChoosePosi()),Qt::QueuedConnection);

    //pop-op magie
    connect(noyau,SIGNAL(dialogueMagi()),field,SLOT(openChooseMagi()),Qt::QueuedConnection);
    connect(field,SIGNAL(sendVisi()),noyau,SLOT(poserMagV()),Qt::QueuedConnection);
    connect(field,SIGNAL(sendHide()),noyau,SLOT(poserMagH()),Qt::QueuedConnection);

    //pour poser une carte
    connect(field,SIGNAL(doubleClicked(int)),noyau,SLOT(poser_test(int)),Qt::QueuedConnection);


    //pour switch
    connect(noyau,SIGNAL(change_position(int)),field,SLOT(switchCarte(int)),Qt::QueuedConnection);



	// ask preview
    connect(field,SIGNAL(askPreview(int)),noyau,SLOT(donner_infos(int)),Qt::QueuedConnection);

	// give preview
    connect(noyau,SIGNAL(give_infos(QString,int,int,QString,int,QString,int,int)),
        field, SLOT(cardHover(QString,int,int,QString,int,QString,int,int)),Qt::QueuedConnection);

    // bi clicked
    connect(field,SIGNAL(monstClick(int,int)),noyau,SLOT(attaquerSlot(int,int)),Qt::QueuedConnection);

    //win
    connect(noyau,SIGNAL(je_gagne()),field,SLOT(openWin()),Qt::QueuedConnection);
    connect(noyau,SIGNAL(je_gagne()), this, SLOT(stopTick()));

    //lose
    connect(noyau,SIGNAL(je_perds()),field,SLOT(openLost()),Qt::QueuedConnection);
    connect(noyau,SIGNAL(je_perds()), this, SLOT(stopTick()));
	

    stacked -> addWidget(field);
    stacked -> setCurrentWidget(field);

    //montrer def caché
    connect(noyau,SIGNAL(montre(int)),field,SLOT(reveal(int)));

    field -> init();



    // Clock Thread

    mThread = new QThread;
    mTask = new MasterTask;
    mTask -> moveToThread(mThread);

	mTask -> threadLock = true;

    connect( mTask, SIGNAL(newTick()), this, SLOT(timeTicker())) ;
    connect( mTask, SIGNAL(newTick()), mTask, SLOT(masterLoop()));

    connect( mThread, SIGNAL(finished()), mTask, SLOT(deleteLater()));
    connect( mThread, SIGNAL(finished()), mThread, SLOT(deleteLater()) );

    //connect(mTask,SIGNAL(newTick()),network,SLOT(keepAlive()),Qt::QueuedConnection);
    //connect(network,SIGNAL(hasDied()),noyau,SIGNAL(je_gagne()),Qt::QueuedConnection);



    mThread -> start();
    mTask -> masterLoop();

    noyau->init();
}


void MasterTask::masterLoop (){

	if (threadLock){
	
		Sleeper::msleep(50);

    	emit newTick();
	}
}



void Master::timeTicker(){

	noyau -> comptageTick();
    field -> setProgress();
    //network -> keepAlive();
}


void Master::stopTick(){
	mTask -> threadLock = false;
}










/*void Master::test(QString str){
    std::cout << str.toStdString() << "\n";
}*/

//void Master::cut(QString, int, int, bool, bool);
