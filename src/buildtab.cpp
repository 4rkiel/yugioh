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
        infoLayout -> setContentsMargins(0,0,0,0);
        infoLayout -> setSpacing(0);
        infoLayout -> setMargin(0);

            info = new QLabel (tr("Decks"));

            infoLayout -> addWidget(info);
       
            infoLayout -> addStretch(1);

            exitButt = new FlatButt("\uf060", "");
            exitButt -> setToolTip(tr("Fermer le menu d'édition"));
            connect(exitButt, SIGNAL(clicked()), this, SLOT(emitClose()));
            infoLayout -> addWidget(exitButt);

        
        infoBox -> setLayout(infoLayout);

    layout -> addWidget(infoBox, 0,0,1,3);


    tabInside = new QWidget;
    tabInside -> setObjectName("tabInside");
    tabInsideLayout = new QGridLayout;
    tabInsideLayout -> setSpacing(0);
    tabInsideLayout -> setMargin(0);
    tabInsideLayout -> setContentsMargins(30,0,30,30);



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

        
            deckButt = new QPushButton;
            deckButt->setDefault(true);
            deckButt -> setText(tr("Editeur de Decks"));
            deckButt -> setProperty("down", true);
            connect(deckButt, SIGNAL(clicked()), this, SLOT(setDeck()));

            tabLayout -> addWidget(deckButt, 0, 0, 1, 1);
            

            cardButt = new QPushButton;
            cardButt->setDefault(true);
            cardButt -> setText(tr("Editeur de Carte"));
            cardButt -> setProperty("down", false);
            connect(cardButt, SIGNAL(clicked()), this, SLOT(setCard()));

            tabLayout -> addWidget(cardButt, 0, 1, 1, 1);
                       

            QSpacerItem * spacerButt = new QSpacerItem(1,1,
                    QSizePolicy::Expanding,QSizePolicy::Preferred);
            
            tabLayout -> addItem(spacerButt, 0, 3);

        tabBox -> setLayout(tabLayout);


    tabInsideLayout -> addWidget(tabBox, 0, 0, 1, 1);



        // Label Box ..........................................................

        buildBox = new QWidget;
        buildBox -> setObjectName("buildBox");
        
        buildLayout = new QGridLayout;
        buildLayout -> setSpacing(0);
        buildLayout -> setMargin(0);
        buildLayout -> setContentsMargins(30,30,30,30);

        buildStacked = new QStackedWidget;


            Parser *parserAllMighty = new Parser;
            vector<Carte*> *allCard = parserAllMighty->all_cards;


            // Deck Edit ......................................................

            deckScroll = new QScrollArea;
            deckScroll -> setFrameShape(QFrame::NoFrame);
            deckScroll -> setWidgetResizable(true);
            deckScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            deckScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            deckScroll -> setFocusPolicy(Qt::NoFocus);
            deckScroll -> setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

            deck = new deckEdit(allCard);
            deckScroll->setWidget(deck);

//            deck = new DeckSelector;
//            deckScroll->setWidget(deck);

            buildStacked -> addWidget(deckScroll);

           


            // Card Edit .......................................................

            cardScroll = new QScrollArea;
            cardScroll -> setFrameShape(QFrame::NoFrame);
            cardScroll -> setWidgetResizable(true);
            cardScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            cardScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            cardScroll -> setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

			editeur = new CardEditor;
            cardScroll->setWidget(editeur);

            buildStacked -> addWidget(cardScroll);

            
            buildStacked -> setCurrentWidget(deckScroll);

        buildLayout -> addWidget(buildStacked);

        buildBox -> setLayout(buildLayout);

    tabInsideLayout -> addWidget(buildBox, 1, 0, 1, 2);

    tabInside -> setLayout(tabInsideLayout);

    //key shortcut
    shortcut = new QShortcut(QKeySequence("Escape"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(emitClose()));

    layout -> addWidget(tabInside,1,1,2,1);

    
    popup = new QWidget;
    popup -> setStyleSheet("background: rgba(0,0,0,100);");
    popup -> setVisible(false);

    layout -> addWidget(popup, 0, 0, 3, 2);



    setLayout(layout);

}


BuildTab::~BuildTab (){

    delete buildEffect;

	delete editeur;
    delete cardScroll;

    delete deck;
    delete deckScroll;

        delete deckButt;
        delete cardButt;
    
    delete buildStacked;
    delete buildLayout;
    delete buildBox;
    delete tabLayout;
    delete tabBox;
    
    delete tabInsideLayout;
    delete tabInside;

    delete info;
    delete exitButt;
    delete infoLayout;
    delete iffect;
    delete infoBox;

    delete popup;

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

    buildStacked -> setCurrentWidget(deckScroll);
}


void BuildTab::setCard (){

    updateStyle(cardButt);

    buildStacked -> setCurrentWidget(cardScroll);
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


void BuildTab::openDeck (){

    popup -> setVisible(true);
}
