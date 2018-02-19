#include "intro.h"

Intro::Intro () {

    layout = new QGridLayout;
    layout -> setAlignment(Qt::AlignCenter);

    introBox = new QWidget;
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

    box -> addWidget(options);




    // Quit Button

    QString strQuit = QString::fromUtf8("Quitter");
    quit = new ShadowButt("\uf011", strQuit);
     
    quit -> setToolTip("Quitter l'application");

    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    
    box -> addWidget(quit);




    introBox -> setLayout(box);

    layout -> addWidget(introBox, 0, 0);

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
}


void Intro::init (){
    newgame -> setFocus();
}

void Intro::emitNewStack (){
        emit newStack();
}

