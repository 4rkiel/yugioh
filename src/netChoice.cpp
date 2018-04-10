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

            box->addWidget(msgAttente);
            box->addWidget(msgAttente2);


            // initialisation du socket

            socket=new QUdpSocket(this);
            socket->bind(QHostAddress::LocalHostIPv6,9001);
            QHostAddress adresse = QHostAddress::LocalHostIPv6;
            quint16 port = 9000;
            QByteArray paquet;
            paquet.append("Hello du client");

            //envoi de "hi" au serveur
            socket->writeDatagram(paquet,adresse,port);


			// 2 on response

				// 2.1 Si client (connexion)

					// Recuperer l'adresse de l'host dans la reponse

					// Faire :
					// emit sendIP(QString)

            connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));


				// 2.2 Si host (mise en attente)

					// Faire (avec sa propre adresse) :
					// emit createHost(QString)


            
            box -> addStretch(1);


        introBox -> setLayout(box);
        layout -> addWidget(introBox, 2, 1, 1, 1);

        //key shortcut
        shortcut = new QShortcut(QKeySequence("Escape"), this);
        connect(shortcut, SIGNAL(activated()), this, SLOT(emitChoice()));

    setLayout(layout);
}

    
NetChoice::~NetChoice (){

    delete socket;
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

void NetChoice::readyRead(){

    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    //le client reçoit la réponse du serveur et la stock
    socket->readDatagram(buffer.data(),buffer.size(),0,0);
    QString msgRec(buffer.data());
    std::cout << msgRec.toStdString() << std::endl;

}
