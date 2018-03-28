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

        info = new QLabel (tr("Mode de Jeu"));

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
          
            QString strSolo = tr("Partie Locale Solo");
            solo = new ShadowButt("\uf007", strSolo);
            solo -> setToolTip(tr("Commencer une partie solo contre une IA"));
            connect(solo, SIGNAL(clicked()), this, SLOT(emitSolo()));
            box -> addWidget(solo);

            box -> addStretch(1);


            // Private Join Button
          
            QString strPrivate = tr("Rejoindre Partie Privée");
            group = new ShadowButt("\uf1eb", strPrivate);
            group -> setToolTip(tr("Rejoindre une Partie Privée"));
            connect(group, SIGNAL(clicked()), this, SLOT(emitJoin()));
            box -> addWidget(group);

            box -> addStretch(1);
          

            // Private Host Button
          
            QString strHost = tr("Héberger Partie Privée");
            host = new ShadowButt("\uf233", strHost);
            host -> setToolTip(tr("Héberger une Partie Privée"));
            connect(host, SIGNAL(clicked()), this, SLOT(emitHost()));
            box -> addWidget(host);

            box -> addStretch(1);


            // MatchMaking Button
          
            QString strOnline = tr("Trouver une Partie");
            online = new ShadowButt("\uf0ac", strOnline);
            online -> setToolTip(tr("Commencer une Partie Online"));
            connect(online, SIGNAL(clicked()), this, SLOT(emitNet()));
            box -> addWidget(online);

            box -> addStretch(20);
            

            // Back Button

            QString strIntro = tr("Retour");
            intro = new ShadowButt("\uf060", strIntro);
            intro -> setToolTip(tr("Retour au Menu"));
            connect(intro, SIGNAL(clicked()), this, SLOT(emitIntro()));
            box -> addWidget(intro);
            
            box -> addStretch(1);


        introBox -> setLayout(box);
        layout -> addWidget(introBox, 2, 1, 1, 1);

        // key shortcuts
        shortcut = new QShortcut(QKeySequence("Escape"), this);
        connect(shortcut, SIGNAL(activated()), this, SLOT(emitIntro()));

    setLayout(layout);
}

    
Choice::~Choice (){

    delete intro;
    delete online;
    delete group;
    delete solo;

    delete effect;
    delete shortcut;

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

