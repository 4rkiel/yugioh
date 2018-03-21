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


            // Local Button
          
            QString strLocal = QString::fromUtf8("Local");
            local = new ShadowButt("\uf007", strLocal);
            local -> setToolTip("Commencer une Partie Solo");
            connect(local, SIGNAL(clicked()), this, SLOT(emitLocal()));
            box -> addWidget(local);

            box -> addStretch(1);
           

            // Private Online Button
          
            QString strPrivate = QString::fromUtf8("Privée");
            group = new ShadowButt("\uf0c0", strPrivate);
            group -> setToolTip("Commencer une Partie Privée");
            connect(group, SIGNAL(clicked()), this, SLOT(emitLocal()));
            box -> addWidget(group);

            box -> addStretch(1);
           

            // MatchMaking Button
          
            QString strOnline = QString::fromUtf8("Online");
            online = new ShadowButt("\uf0ac", strOnline);
            online -> setToolTip("Commencer une Partie Online");
            connect(online, SIGNAL(clicked()), this, SLOT(emitLocal()));
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
    delete local;

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
    local -> setFocus();
}



void Choice::emitIntro (){
    emit introStack();
}

void Choice::emitLocal (){
    emit localStack();
}

