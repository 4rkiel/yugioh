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
            
            delete ai_main;
            delete ai_battle;
            
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

    cout << "construct ai" << endl;
        ai_main = new Ai_main(noyau,2,2);//joueur 2 (adverse)
        ai_battle = new Ai_battle(noyau,2,2);//joueur 2 (adverse)


    if (mode >= 10 && mode <= 19){

        delete network;
        noyau->online = false;
        
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
        
        if(mode==11)
            noyau->deckAdverse(0);
        if(mode==12)
            noyau->deckAdverse(1);
        if(mode==13)
            noyau->deckAdverse(2);
        
        
        /*TODO: le noyau envoi un signal a l'ia pour lui dire de jouer la main phase*/

        connect(noyau,SIGNAL(ai_main_phase()),ai_main,SLOT(play()));
        
        /*TODO: le noyau envoi un signal à l'ia pour lui dire que la battle phase a commencé et
        le noyau renvoit ce signal aussi à chaque fois que l'adversaire effectu une action pendant la battle phase*/
        
        connect(noyau,SIGNAL(ai_battle_phase()),ai_battle,SLOT(play()));
        
        
        //MAIN PHASE//
        
        connect(noyau,SIGNAL(main_phase_ia()),ai_main,SLOT(play()));
        
        connect(ai_main,SIGNAL(signal_poser(int,int,bool,bool)),noyau,SLOT(poser(int,int,bool,bool)));
        
        connect(ai_main,SIGNAL(signal_switch_position(int)),noyau,SLOT(switch_position(int)));
        
        connect(ai_main,SIGNAL(signal_sacrifier_poser(int,int,int,bool,bool)),noyau,SLOT(sacrifier_poser(int,int,int,bool,bool)));
        
        connect(ai_main,SIGNAL(signal_sacrifier_sacrifier_poser(int,int,int,int,bool,bool)),noyau,SLOT(sacrifier_sacrifier_poser(int,int,int,int,bool,bool)));
        
        //connect(ai_main,SIGNAL(signal_activate(int)),noyau,SLOT(activate(int)));
        
        
        //BATTLE PHASE//
        
        connect(noyau,SIGNAL(battle_phase_ia()),ai_battle,SLOT(play()));
        
        connect(ai_battle,SIGNAL(signal_attaquer(int,int)),noyau,SLOT(attaquer(int,int)));
        

    } else {

        delete ai_main;
        delete ai_battle;
        noyau->online = true;
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
        if(network!=NULL)
        connect(network,SIGNAL(hasDied()),noyau,SIGNAL(je_gagne()),Qt::QueuedConnection);
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
    connect(noyau,SIGNAL(give_infos(Carte *)),
        field, SLOT(cardHover(Carte *)),Qt::QueuedConnection);

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
    connect(noyau,SIGNAL(montre(QString,int)),field,SLOT(reveal(QString,int)));

    //sacrifice
    connect(noyau,SIGNAL(dialogueSac1(int,std::vector<Carte*>*)),
            field,SLOT(openChoose(int,std::vector<Carte*>*)));

    connect(field, SIGNAL(chosenOne(std::vector<int>)), 
            noyau, SLOT(prepSac(std::vector<int>)));
    connect(noyau,SIGNAL(openChoosePosi()),field,SLOT(openChoosePosi()));

    //voir certaines zones
    connect(noyau,SIGNAL(openSee(std::vector<Carte*>*)),field,SLOT(openSee(std::vector<Carte*>*)));

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


