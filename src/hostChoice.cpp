#include "../inc/hostChoice.h"

/******************************************************************************

    Widget recréant un QTabWidget personnalisé

	Permet d'implémenter le sous-menu de choix de parties

******************************************************************************/

HostChoice::HostChoice () {

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

        info = new QLabel ("Partie Privée : Hébergement");

        infoLayout -> addWidget(info);
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

        box = new QGridLayout;


            // Back Button
            
            QString strBack = QString::fromUtf8("Retour");
            choice = new ShadowButt("\uf060", strBack);
            choice -> setToolTip("Retour au Menu");
            connect(choice, SIGNAL(clicked()), this, SLOT(emitChoice()));

            box -> addWidget(choice, 7,0,1,3);

           
            // Text

            box -> setRowStretch(0,10);

            intro = new QLabel;
            intro -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
            QString strIntro = QString::fromUtf8(
                "En attente de connexion....................."
            );
            intro -> setText(strIntro);
            intro -> setWordWrap(true);
            intro -> setContentsMargins(30,0,30,0);

            box -> addWidget(intro,1,1,1,1);
            
            box -> setRowStretch(2,10);
            
            
            // IP
            
            QString ip;

            foreach (
                const QHostAddress &address, 
                QNetworkInterface::allAddresses()
            ){
                if (
                    address.protocol() == QAbstractSocket::IPv4Protocol 
                    && address != QHostAddress(QHostAddress::LocalHost)
                ){
                    ip = address.toString();
                }
            }
             
            phrase = new QLabel;
            ip = "Adresse IP : " + ip;
            phrase -> setText(ip);
            phrase -> setWordWrap(true);
            phrase -> setContentsMargins(30,0,30,0);
            phrase -> setTextInteractionFlags(Qt::TextSelectableByMouse); 
            box -> addWidget(phrase,3,1,1,1);
            
            box -> setRowStretch(4,2);
            
           

            adr = new QLabel;
            QString strPhrase = QString::fromUtf8("Port : 7777");
            adr -> setText(strPhrase);
            adr -> setWordWrap(true);
            adr -> setContentsMargins(30,0,30,0);
            adr -> setTextInteractionFlags(Qt::TextSelectableByMouse);
            box -> addWidget(adr,5,1,1,1);    

            
            box -> setRowStretch(6,25);
            box -> setRowStretch(8,1);


        introBox -> setLayout(box);
        layout -> addWidget(introBox, 2, 1, 1, 1);


    setLayout(layout);
}

    
HostChoice::~HostChoice (){

    delete intro;
    delete phrase;
    delete adr;
    delete choice;

    delete effect;

    delete box;
    delete introBox;

    delete iffect;
    delete info;
    delete infoLayout;
    delete infoBox;

    delete layout;
}


void HostChoice::init (){
//    local -> setFocus();
}



void HostChoice::emitChoice (){
    emit choiceStack();
}

