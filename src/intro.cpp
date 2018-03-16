#include "../inc/intro.h"

Intro::Intro () {

    layout = new QGridLayout;
    layout -> setAlignment(Qt::AlignCenter);
    layout -> setSpacing(0);
    layout -> setMargin(0);


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


            // New Game Button
          
            QString strButton = QString::fromUtf8("Duel");
            choice = new ShadowButt("\uf439", strButton);
            choice -> setToolTip("Commencer une partie");
            connect(choice, SIGNAL(clicked()), this, SLOT(emitChoice()));
            box -> addWidget(choice);


            // Decks Button

            QString strDeck = QString::fromUtf8("Decks");
            decks = new ShadowButt("\uf02d", strDeck);
            decks -> setToolTip("Gestion des decks");
            box -> addWidget(decks);


            // Regles Button

            QString strRules = QString::fromUtf8("Règles");
            rules = new ShadowButt("\uf24e", strRules);
            rules -> setToolTip("Gestion de l'arbitrage");
            connect(rules, SIGNAL(clicked()), this, SLOT(emitRule()));
            box -> addWidget(rules);


            // Options Button

            QString strOptions = QString::fromUtf8("Paramètres");
            options = new ShadowButt("\uf085", strOptions);
            options -> setToolTip("Gestion des options");
            connect(options, SIGNAL(clicked()), this, SLOT(emitOpt()));
            box -> addWidget(options);


            // Options Button

            QString strHelp = QString::fromUtf8("Aide");
            help = new ShadowButt("\uf059", strHelp);
            help -> setToolTip("Besoin d'aide ?");
            connect(help, SIGNAL(clicked()), this, SLOT(emitHelp()));
            box -> addWidget(help);



            // Quit Button

            QString strQuit = QString::fromUtf8("Quitter");
            quit = new ShadowButt("\uf011", strQuit);
            quit -> setToolTip("Quitter l'application");
            connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
            box -> addWidget(quit);


        introBox -> setLayout(box);
        layout -> addWidget(introBox, 0, 0, 1, 1);


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
    delete layout;
}


void Intro::init (){
    choice -> setFocus();
}


void Intro::emitChoice (){
    emit choiceStack();
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

