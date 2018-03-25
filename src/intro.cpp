#include "../inc/intro.h"

#include <QHBoxLayout>

/******************************************************************************

	Widget du menu principal

	Contient les différents boutons, renvoyant aux divers sous-menus

******************************************************************************/


Intro::Intro () {

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

        info = new QLabel (tr("Menu Principal"));

        infoLayout -> addWidget(info);
        infoBox -> setLayout(infoLayout);

        layout -> addWidget(infoBox, 0,0,1,3);


        // Intro Menu 

        introBox = new QWidget;
        introBox -> setObjectName("introBox");

        effect = new QGraphicsDropShadowEffect;
        effect -> setBlurRadius(5);
        effect -> setXOffset(0);
        effect -> setYOffset(5);
        effect -> setColor(QColor(0,0,0,150));

        introBox -> setGraphicsEffect(effect);

        box = new QVBoxLayout;

            box -> addStretch(1);

            // New Game Button
          
            QString strButton = tr("Duel");
            choice = new ShadowButt("\uf439", strButton);
            choice -> setToolTip(tr("Commencer une partie"));
            connect(choice, SIGNAL(clicked()), this, SLOT(emitChoice()));
            box -> addWidget(choice);

            box -> addStretch(1);

            // Decks Button

            QString strDeck = tr("Decks");
            decks = new ShadowButt("\uf02d", strDeck);
            decks -> setToolTip(tr("Gestion des decks"));
            connect(decks, SIGNAL(clicked()), this, SLOT(emitDeck()));
            box -> addWidget(decks);

            box -> addStretch(1);

            // Regles Button

            QString strRules = tr("Règles");
            rules = new ShadowButt("\uf24e", strRules);
            rules -> setToolTip(tr("Gestion de l'arbitrage"));
            connect(rules, SIGNAL(clicked()), this, SLOT(emitRule()));
            box -> addWidget(rules);

            box -> addStretch(1);

            // Options Button

            QString strOptions = tr("Paramètres");
            options = new ShadowButt("\uf085", strOptions);
            options -> setToolTip(tr("Gestion des options"));
            connect(options, SIGNAL(clicked()), this, SLOT(emitOpt()));
            box -> addWidget(options);

            box -> addStretch(1);

            // Options Button

            QString strHelp = tr("Aide");
            help = new ShadowButt("\uf059", strHelp);
            help -> setToolTip(tr("Besoin d'aide ?"));
            connect(help, SIGNAL(clicked()), this, SLOT(emitHelp()));
            box -> addWidget(help);


            box -> addStretch(20);

            // Quit Button

            QString strQuit = tr("Quitter");
            quit = new ShadowButt("\uf011", strQuit);
            quit -> setToolTip(tr("Quitter l'application"));
            connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
            box -> addWidget(quit);

            
            box -> addStretch(1);

        introBox -> setLayout(box);
        layout -> addWidget(introBox, 2, 1, 1, 1);


    setLayout(layout);
}

    
Intro::~Intro (){

    delete choice;
    delete decks;
    delete rules;
    delete options;
    delete help;
    delete quit;

    delete effect;
    delete box;
    delete introBox;
    
    delete info;
    delete infoLayout;
    delete iffect;
    delete infoBox;
    
    delete layout;
}


void Intro::init (){
    choice -> setFocus();
}


void Intro::emitChoice (){
    emit choiceStack();
}

void Intro::emitDeck (){
    emit buildStack();
}

void Intro::emitRule (){
    emit ruleStack();
}

void Intro::emitOpt (){
    emit optStack();
}

void Intro::emitHelp (){
    emit helpStack();
}


