#include "intro.h"

Intro::Intro () {

    layout = new QGridLayout;
    layout -> setAlignment(Qt::AlignCenter);
    layout -> setSpacing(0);
    layout -> setMargin(0);


        // Intro Menu 

        introBox = new QWidget;
        introBox -> setObjectName("introBox");
        box = new QVBoxLayout;

        effect = new QGraphicsDropShadowEffect(this);
        effect -> setBlurRadius(5);
        effect -> setXOffset(0);
        effect -> setYOffset(5);
        effect -> setColor(QColor(0,0,0,150));

        introBox -> setGraphicsEffect(effect);


            // New Game Button
          
            QString strButton = QString::fromUtf8("Duel");
            newgame = new ShadowButt("\uf439", strButton);
            newgame -> setToolTip("Commencer une partie");
            connect(newgame, SIGNAL(clicked()), this, SLOT(emitNewStack()));
            box -> addWidget(newgame);


            // Options Button

            QString strDeck = QString::fromUtf8("Decks");
            decks = new ShadowButt("\uf02d", strDeck);
            decks -> setToolTip("Gestion des decks");
            box -> addWidget(decks);


            // Regles Button

            QString strRules = QString::fromUtf8("Règles");
            rules = new ShadowButt("\uf24e", strRules);
            rules -> setToolTip("Gestion de l'arbitrage");
            box -> addWidget(rules);


            // Options Button

            QString strOptions = QString::fromUtf8("Options");
            options = new ShadowButt("\uf085", strOptions);
            options -> setToolTip("Gestion des options");
            connect(options, SIGNAL(clicked()), this, SLOT(showOptions()));
            box -> addWidget(options);


            // Quit Button

            QString strQuit = QString::fromUtf8("Quitter");
            quit = new ShadowButt("\uf011", strQuit);
            quit -> setToolTip("Quitter l'application");
            connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
            box -> addWidget(quit);


        introBox -> setLayout(box);
        layout -> addWidget(introBox, 0, 0, 1, 1);



        // Shadow
        
        shadow = new QPushButton;
        shadow -> setObjectName("shadow");
        shadow -> setVisible(false);
        shadow -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(shadow, SIGNAL(clicked()), this, SLOT(showIntro()));
        
        layout -> addWidget(shadow, 0, 0, 1, 1);
        

        // Options
        
        optionBox = new OptionTab;
        connect(optionBox, SIGNAL(closeTab()), this, SLOT(showIntro()));
        
        layout -> addWidget(optionBox, 0, 0, 1, 1, Qt::AlignCenter);


    this -> setLayout(layout);
}

    
Intro::~Intro (){

    delete newgame;
    delete decks;
    delete rules;
    delete options;
    delete quit;

    delete effect;

    delete box;
    delete introBox;
    delete layout;

    delete shadow;

    delete optionBox;
}


void Intro::init (){
    newgame -> setFocus();
}


void Intro::emitNewStack (){
        emit newStack();
}


void Intro::showOptions (){
    introBox -> setVisible(false);
    shadow -> setVisible(true);
    optionBox -> setVisible(true);
}


void Intro::showRules (){
    introBox -> setVisible(false);
    shadow -> setVisible(true);
}


void Intro::showIntro (){
    optionBox -> setVisible(false);
    shadow -> setVisible(false);
    introBox -> setVisible(true);    
}
