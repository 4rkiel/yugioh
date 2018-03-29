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
        infoLayout -> setContentsMargins(0,0,0,0);
        infoLayout -> setSpacing(0);
        infoLayout -> setMargin(0);
        infoLayout -> setSizeConstraint(QLayout::SetMinimumSize);
		
            // WAMI

	        info = new QLabel (tr("Menu Principal"));

    	    infoLayout -> addWidget(info);

        
			infoLayout -> addStretch(1);


            // Quit Button

            quit = new FlatButt("\uf011", "");
            quit -> setToolTip(tr("Quitter l'application"));
            connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
            infoLayout -> addWidget(quit);

 

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
		box -> setContentsMargins(0,0,0,0);
		box -> setSpacing(0);
		box -> setMargin(0);
            
			
            // New Game Button
          
            QString strButton = tr("Duel");
            choice = new FlatExpButt("\uf439", strButton);
            choice -> setToolTip(tr("Commencer une partie"));
            connect(choice, SIGNAL(clicked()), this, SLOT(emitMaster()));
            box -> addWidget(choice);

			sep1 = new QFrame;
			sep1 -> setFixedHeight(1);
			sep1 -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            box -> addWidget(sep1);


            // Decks Button

            QString strDeck = tr("Decks");
            decks = new FlatExpButt("\uf02d", strDeck);
            decks -> setToolTip(tr("Gestion des decks"));
            connect(decks, SIGNAL(clicked()), this, SLOT(emitDeck()));
            box -> addWidget(decks);

			sep2 = new QFrame;
 			sep2 -> setFixedHeight(1);
			sep2 -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
			box -> addWidget(sep2);


            // Regles Button

            QString strRules = tr("Règles");
            rules = new FlatExpButt("\uf24e", strRules);
            rules -> setToolTip(tr("Gestion de l'arbitrage"));
            connect(rules, SIGNAL(clicked()), this, SLOT(emitRule()));
            box -> addWidget(rules);

			sep3 = new QFrame;
	 		sep3 -> setFixedHeight(1);
			sep3 -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            box -> addWidget(sep3);



            // Options Button

            QString strOptions = tr("Paramètres");
            options = new FlatExpButt("\uf085", strOptions);
            options -> setToolTip(tr("Gestion des options"));
            connect(options, SIGNAL(clicked()), this, SLOT(emitOpt()));
            box -> addWidget(options);

			sep4 = new QFrame;
 	 		sep4 -> setFixedHeight(1);
			sep4 -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
			box -> addWidget(sep4);




            // Options Button

            QString strHelp = tr("Aide");
            help = new FlatExpButt("\uf059", strHelp);
            help -> setToolTip(tr("Besoin d'aide ?"));
            connect(help, SIGNAL(clicked()), this, SLOT(emitHelp()));
            box -> addWidget(help);

/*
           
            box -> addStretch(1);
*/
            //key shortcut
            shortcut = new QShortcut(QKeySequence("Escape"), this);
            connect(shortcut, SIGNAL(activated()), qApp, SLOT(quit()));

        introBox -> setLayout(box);
        layout -> addWidget(introBox, 2, 1, 1, 1);


    setLayout(layout);
}

    
Intro::~Intro (){

	delete sep1;
	delete sep2;
	delete sep3;
	delete sep4;

    delete choice;
    delete decks;
    delete rules;
    delete options;
    delete help;
//    delete quit;

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


void Intro::emitMaster (){
    emit masterStack();
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


