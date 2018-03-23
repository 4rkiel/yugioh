#include "../inc/buildtab.h"

/******************************************************************************
	
	Widget recréant un QTabWidget personnalisé
	
	Implémente le sous-menu de Création de Deck/Edition de Cartes

******************************************************************************/


BuildTab::BuildTab (){

    layout = new QGridLayout;
    layout -> setSpacing(0);
    layout -> setMargin(0);
    
        infoBox = new QWidget;
        infoBox -> setObjectName("infoBox");
        infoBox -> setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Maximum);

        iffect = new QGraphicsDropShadowEffect;
        iffect -> setBlurRadius(5);
        iffect -> setXOffset(0);
        iffect -> setYOffset(5);
        iffect -> setColor(QColor(0,0,0,150));

        infoBox -> setGraphicsEffect(iffect);

        infoLayout = new QHBoxLayout;

        info = new QLabel ("Decks");

        infoLayout -> addWidget(info);
        infoBox -> setLayout(infoLayout);

    layout -> addWidget(infoBox, 0,0,1,3);


    tabInside = new QWidget;
    tabInside -> setObjectName("tabInside");
    tabInsideLayout = new QGridLayout;
    tabInsideLayout -> setSpacing(0);
    tabInsideLayout -> setMargin(0);
    tabInsideLayout -> setContentsMargins(30,0,30,0);



    buildEffect = new QGraphicsDropShadowEffect(this);
    buildEffect -> setBlurRadius(5);
    buildEffect -> setXOffset(0);
    buildEffect -> setYOffset(5);
    buildEffect -> setColor(QColor(0,0,0,150));

    tabInside -> setGraphicsEffect(buildEffect);



        // Tab box ............................................................

        tabBox = new QWidget;
        tabBox -> setObjectName("buildTab");
        tabLayout = new QGridLayout;
        tabLayout -> setSpacing(0);
        tabLayout -> setMargin(0);
  
            exitButt = new ShadowButt("\uf060", tr("Retour"));
            exitButt -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
            exitButt -> setToolTip("Fermer le menu d'édition");
            connect(exitButt, SIGNAL(clicked()), this, SLOT(emitClose()));
            
            tabLayout -> addWidget(exitButt, 0, 4, 1, 1);


            deckButt = new QPushButton;
            deckButt -> setText("Decks");
            deckButt -> setProperty("down", true);
            connect(deckButt, SIGNAL(clicked()), this, SLOT(setDeck()));

            tabLayout -> addWidget(deckButt, 0, 0, 1, 1);
            

            cardButt = new QPushButton;
            cardButt -> setText("Cartes");
            cardButt -> setProperty("down", false);
            connect(cardButt, SIGNAL(clicked()), this, SLOT(setCard()));

            tabLayout -> addWidget(cardButt, 0, 1, 1, 1);

            cardEditButt = new QPushButton;
            cardEditButt -> setText("Editeur de Carte");
            cardEditButt -> setProperty("down", false);
            connect(cardEditButt, SIGNAL(clicked()), this, SLOT(setEditeurCarte()));

            tabLayout -> addWidget(cardEditButt, 0, 2, 1, 1);
                       

            QSpacerItem * spacerButt = new QSpacerItem(1,1,
                    QSizePolicy::Expanding,QSizePolicy::Preferred);
            
            tabLayout -> addItem(spacerButt, 0, 3);

        tabBox -> setLayout(tabLayout);


    tabInsideLayout -> addWidget(tabBox, 0, 0, 1, 1);



        // Label Box ..........................................................

        buildBox = new QWidget;
        buildBox -> setObjectName("buildBox");
        
        buildLayout = new QStackedLayout;
        buildLayout -> setSpacing(0);
        buildLayout -> setMargin(0);


            // Help ...........................................................

            deckScroll = new QScrollArea;
            deckScroll -> setFrameShape(QFrame::NoFrame);
            deckScroll -> setWidgetResizable(true);
            deckScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            deckScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            deckScroll -> setFocusPolicy(Qt::NoFocus);


            buildLayout -> addWidget(deckScroll);

           


            // About ..........................................................

            cardScroll = new QScrollArea;
            cardScroll -> setFrameShape(QFrame::NoFrame);
            cardScroll -> setWidgetResizable(true);
            cardScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            cardScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);


            buildLayout -> addWidget(cardScroll);



            // cardEdit .......................................................

            cardEditScroll = new QScrollArea;
            cardEditScroll -> setFrameShape(QFrame::NoFrame);
            cardEditScroll -> setWidgetResizable(true);
            cardEditScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            cardEditScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

            cardEditScroll->setWidget(new editeur_de_carte());

            buildLayout -> addWidget(cardEditScroll);



        buildLayout -> setCurrentWidget(deckScroll);
        buildBox -> setLayout(buildLayout);

    tabInsideLayout -> addWidget(buildBox, 1, 0, 1, 2);

    tabInside -> setLayout(tabInsideLayout);

    layout -> addWidget(tabInside,1,1,2,1);

    setLayout(layout);

}


BuildTab::~BuildTab (){
    
    delete buildEffect;
    
    delete cardScroll;

    delete deckScroll;

        delete exitButt;
        delete deckButt;
        delete cardButt;
    
    delete buildLayout;
    delete buildBox;
    delete tabLayout;
    delete tabBox;
    
    delete tabInsideLayout;
    delete tabInside;

    delete info;
    delete infoLayout;
    delete iffect;
    delete infoBox;

    delete layout;
}


void BuildTab::init (){

    currButt = deckButt;
    deckButt -> setFocus();
}

void BuildTab::reInit (){

    updateStyle(currButt);
}


void BuildTab::setDeck (){

    updateStyle(deckButt);

    buildLayout -> setCurrentWidget(deckScroll);
}


void BuildTab::setCard (){

    updateStyle(cardButt);

    buildLayout -> setCurrentWidget(cardScroll);
}

void BuildTab::setEditeurCarte()
{
    updateStyle(cardEditButt);
    buildLayout -> setCurrentWidget(cardEditScroll);
}


void BuildTab::updateStyle (QPushButton * b){
     
    currButt -> setProperty("down", false);
    b -> setProperty("down", true);

    currButt -> style() -> unpolish(currButt);
    currButt -> style() -> polish(currButt);
    
    b -> style() -> unpolish(b);
    b -> style() -> polish(b);

    currButt = b;
}


void BuildTab::emitClose (){

    emit introStack();
}


