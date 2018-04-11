#include "../inc/netChoice.h"

/******************************************************************************

    Widget recréant un QTabWidget personnalisé

	Permet d'implémenter le sous-menu de choix de parties

******************************************************************************/

NetChoice::NetChoice () {

    layout = new QGridLayout;
    layout -> setAlignment(Qt::AlignCenter);
    layout -> setSpacing(0);
    layout -> setMargin(0);


        infoBox = new QWidget;
        infoBox -> setObjectName("infoBox");

        iffect = new QGraphicsDropShadowEffect;
        iffect -> setBlurRadius(5);
        iffect -> setXOffset(0);
        iffect -> setYOffset(5);
        iffect -> setColor(QColor(0,0,0,150));

        infoBox -> setGraphicsEffect(iffect);

        infoLayout = new QHBoxLayout;
        infoLayout -> setContentsMargins(0,0,0,0);
        infoLayout -> setSpacing(0);
        infoLayout -> setMargin(0);

	        info = new QLabel (tr("Trouver une Partie"));
    	    infoLayout -> addWidget(info);

			infoLayout -> addStretch(1);

            choice = new FlatButt("\uf060", "");
            choice -> setToolTip(tr("Retour"));
            connect(choice, SIGNAL(clicked()), this, SLOT(emitChoice()));
            infoLayout -> addWidget(choice);


        	infoBox -> setLayout(infoLayout);

        layout -> addWidget(infoBox, 0,0,1,3);
        
        
        
        // Intro Menu 

        introBox = new QWidget;
        introBox -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		introBox -> setObjectName("introBox");

        effect = new QGraphicsDropShadowEffect(this);
        effect -> setBlurRadius(5);
        effect -> setXOffset(0);
        effect -> setYOffset(5);
        effect -> setColor(QColor(0,0,0,150));

        introBox -> setGraphicsEffect(effect);

        box = new QVBoxLayout;

            box -> addStretch(1);


            // Gestion matchmaking


            // message d'attente
            msgAttente = new QLabel(tr("Recherche d'un adversaire en cours..."));

            msgAttente->setContentsMargins(185,0,0,100);
            msgAttente->setWordWrap(true);
            QFont f("",12,QFont::Normal);
            msgAttente -> setFont(f);
            msgAttente -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

            msgAttente2 = new QLabel(tr("Veuillez patienter"));
            msgAttente2 -> setAlignment(Qt::AlignCenter);
            msgAttente2->setWordWrap(true);

            // création du macthmaker

            matchmaker=new Matchmaking();
            connect(matchmaker, SIGNAL(sendIP(QString)), this, SLOT(emitClient(QString)));
            connect(matchmaker, SIGNAL(createHost(QString)), this, SLOT(emitHost(QString)));

            box->addWidget(msgAttente);
            box->addWidget(msgAttente2);
            
            box -> addStretch(1);


        introBox -> setLayout(box);
        layout -> addWidget(introBox, 2, 1, 1, 1);

        //key shortcut
        shortcut = new QShortcut(QKeySequence("Escape"), this);
        connect(shortcut, SIGNAL(activated()), this, SLOT(emitChoice()));

    setLayout(layout);
}

    
NetChoice::~NetChoice (){

    delete effect;
    delete msgAttente;
    delete msgAttente2;
    delete box;
    delete introBox;

    delete iffect;
    delete info;
    delete choice;
    delete infoLayout;
    delete infoBox;

    delete layout;
}


void NetChoice::init (){
//    local -> setFocus();
}



void NetChoice::emitChoice (){
    emit choiceStack();
}

void NetChoice::emitClient(QString ip){
    emit sendIP(ip);
}

void NetChoice::emitHost(QString ip){
    emit createHost(ip);
}


