#include "../inc/choice.h"

/******************************************************************************

    Widget recréant un QTabWidget personnalisé

	Permet d'implémenter le sous-menu de choix de parties

******************************************************************************/

Choice::Choice () {

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

        info = new QLabel ("Mode de Jeu");

        infoLayout -> addWidget(info);
        infoBox -> setLayout(infoLayout);

        layout -> addWidget(infoBox, 0,0,1,3);
        
        
        
        // Intro Menu 

        introBox = new QWidget;
        introBox -> setObjectName("introBox");

        effect = new QGraphicsDropShadowEffect(this);
        effect -> setBlurRadius(5);
        effect -> setXOffset(0);
        effect -> setYOffset(5);
        effect -> setColor(QColor(0,0,0,150));

        introBox -> setGraphicsEffect(effect);

        box = new QVBoxLayout;

            box -> addStretch(1);


            // Local playerButton
          
            QString strSolo = QString::fromUtf8("Partie Solo");
            solo = new ShadowButt("\uf007", strSolo);
            solo -> setToolTip("Commencer une partie solo contre une IA");
            connect(solo, SIGNAL(clicked()), this, SLOT(emitSolo()));
            box -> addWidget(solo);

            box -> addStretch(1);


            // Private Join Button
          
            QString strPrivate = QString::fromUtf8("Rejoindre Partie Privée");
            group = new ShadowButt("\uf1eb", strPrivate);
            group -> setToolTip("Rejoindre une Partie Privée");
            connect(group, SIGNAL(clicked()), this, SLOT(emitJoin()));
            box -> addWidget(group);

            box -> addStretch(1);
          

            // Private Host Button
          
            QString strHost = QString::fromUtf8("Héberger Partie Privée");
            host = new ShadowButt("\uf233", strHost);
            host -> setToolTip("Héberger une Partie Privée");
            connect(host, SIGNAL(clicked()), this, SLOT(emitHost()));
            box -> addWidget(host);

            box -> addStretch(1);


            // MatchMaking Button
          
            QString strOnline = QString::fromUtf8("Trouver une Partie");
            online = new ShadowButt("\uf0ac", strOnline);
            online -> setToolTip("Commencer une Partie Online");
            connect(online, SIGNAL(clicked()), this, SLOT(emitNet()));
            box -> addWidget(online);

            box -> addStretch(20);
            

            // Back Button

            QString strIntro = QString::fromUtf8("Retour");
            intro = new ShadowButt("\uf060", strIntro);
            intro -> setToolTip("Retour au Menu");
            connect(intro, SIGNAL(clicked()), this, SLOT(emitIntro()));
            box -> addWidget(intro);
            
            box -> addStretch(1);


        introBox -> setLayout(box);
        layout -> addWidget(introBox, 2, 1, 1, 1);


    setLayout(layout);
}

    
Choice::~Choice (){

    delete intro;
    delete online;
    delete group;
    delete solo;

    delete effect;

    delete box;
    delete introBox;

    delete iffect;
    delete info;
    delete infoLayout;
    delete infoBox;

    delete layout;
}


void Choice::init (){
    solo -> setFocus();
}



void Choice::emitIntro (){
    emit introStack();
}

void Choice::emitSolo (){
    emit soloStack();
}

void Choice::emitJoin (){
    emit joinStack();
}

void Choice::emitHost (){
    emit hostStack();
}

void Choice::emitNet (){
    emit netStack();
}

