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
        infoLayout -> setContentsMargins(0,0,0,0);
        infoLayout -> setSpacing(0);
        infoLayout -> setMargin(0);
        
            info = new QLabel (tr("Mode de Jeu"));

            infoLayout -> addWidget(info);
            
            infoLayout -> addStretch(1);
 
            // Back Button

            intro = new FlatButt("\uf060", "");
            intro -> setToolTip(tr("Retour au Menu"));
            connect(intro, SIGNAL(clicked()), this, SLOT(emitIntro()));
//            infoLayout -> addWidget(intro);
            
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
        box -> setContentsMargins(0,0,0,0);
        box -> setSpacing(0);
        box -> setMargin(0);
            

            // Local playerButton
          
            QString strSolo = tr("Partie Locale Solo");
            solo = new FlatExpButt("\uf007", strSolo);
            solo -> setToolTip(tr("Commencer une partie solo contre une IA"));
            connect(solo, SIGNAL(clicked()), this, SLOT(emitSolo()));
            box -> addWidget(solo);

            sep1 = new QFrame;
            sep1 -> setFixedHeight(1);
            sep1 -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            box -> addWidget(sep1);


            // Private Join Button
          
            QString strPrivate = tr("Rejoindre Partie Privée");
            group = new FlatExpButt("\uf1eb", strPrivate);
            group -> setToolTip(tr("Rejoindre une Partie Privée"));
            connect(group, SIGNAL(clicked()), this, SLOT(emitJoin()));
            box -> addWidget(group);
          
            sep2 = new QFrame;
            sep2 -> setFixedHeight(1);
            sep2 -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            box -> addWidget(sep2);


            // Private Host Button
          
            QString strHost = tr("Héberger Partie Privée");
            host = new FlatExpButt("\uf233", strHost);
            host -> setToolTip(tr("Héberger une Partie Privée"));
            connect(host, SIGNAL(clicked()), this, SLOT(emitHost()));
            box -> addWidget(host);

            sep3 = new QFrame;
            sep3 -> setFixedHeight(1);
            sep3 -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            box -> addWidget(sep3);


            // MatchMaking Button
          
            QString strOnline = tr("Trouver une Partie");
            online = new FlatExpButt("\uf0ac", strOnline);
            online -> setToolTip(tr("Commencer une Partie Online"));
            connect(online, SIGNAL(clicked()), this, SLOT(emitNet()));
            box -> addWidget(online);



        introBox -> setLayout(box);
        
        layout -> setRowStretch(1,1);
        layout -> addWidget(introBox, 2, 1, 4, 1);
        layout -> setRowStretch(6,1);

        // key shortcuts
        shortcut = new QShortcut(QKeySequence("Escape"), this);
        connect(shortcut, SIGNAL(activated()), this, SLOT(emitIntro()));

    setLayout(layout);
    solo -> setFocus();
}

    
Choice::~Choice (){

    delete sep1;
    delete sep2;
    delete sep3;
    
    delete online;
    delete host;
    delete group;
    delete solo;

    delete effect;
    delete shortcut;

    delete box;
    delete introBox;

    delete iffect;
    delete intro;
    delete info;
    delete infoLayout;
    delete infoBox;

    delete layout;
}


void Choice::init (){
    solo -> setFocus();
    infoLayout -> addWidget(intro);
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

