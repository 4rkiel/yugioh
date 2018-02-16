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

    newgame = new ShadowButt;
    
    QIcon icoButton("puzzle.png");
    newgame -> setIcon(icoButton);
    
    QString strButton = QString::fromUtf8("New Game");
    newgame -> setText(strButton);
    
    newgame -> setToolTip("Infobulle txt");
 
    connect(newgame, SIGNAL(clicked()), this, SLOT(emitNewStack()));
    
    box -> addWidget(newgame);



    // Options Button

    options = new ShadowButt;
    
    QIcon icoOptions("puzzle.png");
    options -> setIcon(icoOptions);
    
    QString strOptions = QString::fromUtf8("Options");
    options -> setText(strOptions);
    
    options -> setToolTip("Infobulle txt");

    box -> addWidget(options);



    // Options Button

    rules = new ShadowButt;
    
    QIcon icoRules("puzzle.png");
    rules -> setIcon(icoRules);
    
    QString strRules = QString::fromUtf8("Rules");
    rules -> setText(strRules);
    
    rules -> setToolTip("Infobulle txt");

    box -> addWidget(rules);



    // Quit Button

    quit = new ShadowButt;
     
    QIcon icoQuit("puzzle.png");
    quit -> setIcon(icoQuit);
    
    QString strQuit = QString::fromUtf8("Quit");
    quit -> setText(strQuit);
    
    quit -> setToolTip("Infobulle txt");

    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    
    box -> addWidget(quit);



    introBox -> setLayout(box);

    layout -> addWidget(introBox, 0, 0);

    this -> setLayout(layout);
}

    
Intro::~Intro (){

    delete newgame;
    delete options;
    delete rules;
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

