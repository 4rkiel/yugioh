#include "../inc/ruletab.h"

/******************************************************************************

    Widget recréant un QTabWidget personnalisé
	
	Permet d'afficher le sous-menu des Règles (lecture et personnalisation)

******************************************************************************/

RuleTab::RuleTab (){

    readLangage();
    
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
            
            info = new QLabel (tr("Règles"));
            
            infoLayout -> addWidget(info);

            infoLayout -> addStretch(1);

            exitButt = new FlatButt("\uf060", "");
            exitButt -> setToolTip(tr("Fermer les règles"));
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



    ruEffect = new QGraphicsDropShadowEffect(this);
    ruEffect -> setBlurRadius(5);
    ruEffect -> setXOffset(0);
    ruEffect -> setYOffset(5);
    ruEffect -> setColor(QColor(0,0,0,150));

    tabInside -> setGraphicsEffect(ruEffect);




        // Tab box ............................................................

        tabBox = new QWidget;
        tabBox -> setObjectName("ruleTab");
        tabLayout = new QGridLayout;
        tabLayout -> setSpacing(0);
        tabLayout -> setMargin(0);
  
           
            persoButt = new QPushButton;
            persoButt->setDefault(true);
            persoButt -> setText(tr("Personnalisation"));
            persoButt -> setProperty("down", true);
            connect(persoButt, SIGNAL(clicked()), this, SLOT(setPerso()));

            tabLayout -> addWidget(persoButt, 0, 0, 1, 1);
            

            rulesButt = new QPushButton;
            rulesButt->setDefault(true);
            rulesButt -> setText(tr("Règles du Jeu"));
            rulesButt -> setProperty("down", false);
            connect(rulesButt, SIGNAL(clicked()), this, SLOT(setRules()));
            
            tabLayout -> addWidget(rulesButt, 0, 1, 1, 1);

            QSpacerItem * spacerButt = new QSpacerItem(1,1,
                    QSizePolicy::Expanding,QSizePolicy::Preferred);

            tabLayout -> addItem(spacerButt, 0, 2);

        tabBox -> setLayout(tabLayout);


    tabInsideLayout -> addWidget(tabBox, 0, 0, 1, 1);



        // Label Box ..........................................................

        ruleBox = new QWidget;
        ruleBox -> setObjectName("ruleBox");
        
        ruleLayout = new QGridLayout;
        ruleLayout -> setSpacing(0);
        ruleLayout -> setMargin(0);
		ruleLayout -> setContentsMargins(30,30,30,30);

		ruleStacked = new QStackedWidget;


            // Personnalisation ...............................................

            persoScroll = new QScrollArea;
            persoScroll -> setFrameShape(QFrame::NoFrame);
            persoScroll -> setWidgetResizable(true);
            persoScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            persoScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            persoScroll -> setFocusPolicy(Qt::NoFocus);

            persoScrollBox = new QWidget;
            persoScrollBox -> setObjectName("ruleScrollBox");
            persoPaneLayout = new QVBoxLayout;
            persoPaneLayout -> setAlignment(Qt::AlignTop);

            
            // life points

                lifePoints = new Combo;
                lifePoints -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
                lifePoints -> addItem("1000");
                lifePoints -> addItem("2000");
                lifePoints -> addItem("3000");
                lifePoints -> addItem("4000");
                lifePoints -> addItem("5000");
                lifePoints -> addItem("6000");
                lifePoints -> addItem("7000");
                lifePoints -> addItem("8000");
                lifePoints -> addItem("9000");
                persoPaneLayout -> addWidget(lifePoints);
                connect(lifePoints,SIGNAL(currentIndexChanged(QString)),this,SLOT(lifeChange()));

                lifeDesc = new QLabel;
                lifeDesc -> setTextInteractionFlags(Qt::NoTextInteraction);
                lifeDesc -> setText(tr("Nombre de points de vie"));
                persoPaneLayout -> addWidget(lifeDesc);

                // card draw number

                cardDrawNumber = new Combo;
                cardDrawNumber -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
                cardDrawNumber -> addItem("1");
                cardDrawNumber -> addItem("2");
                cardDrawNumber -> addItem("3");
                cardDrawNumber -> addItem("4");
                cardDrawNumber -> addItem("5");
                cardDrawNumber -> addItem("6");
                cardDrawNumber -> addItem("7");
                persoPaneLayout -> addWidget(cardDrawNumber);
                connect(cardDrawNumber,SIGNAL(currentIndexChanged(QString)),
                        this,SLOT(cardDrawNumberChange()));

                cardDrawDesc = new QLabel;
                cardDrawDesc -> setTextInteractionFlags(Qt::NoTextInteraction);
                cardDrawDesc -> setText(tr("Nombre de cartes piochées en début de tour"));
                persoPaneLayout -> addWidget(cardDrawDesc);

                // load settings

                loadPersoSettings();


            persoScrollBox -> setLayout(persoPaneLayout); 
            persoScroll -> setWidget(persoScrollBox);

            ruleStacked -> addWidget(persoScroll);

           


            // About ..........................................................

            ruleScroll = new QScrollArea;
            ruleScroll -> setFrameShape(QFrame::NoFrame);
            ruleScroll -> setWidgetResizable(true);
            ruleScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            ruleScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
 

                ruleLabel = new QLabel;

                    QFile file("i18n/"+valeur+"/rules.text");

                    QString text = "";
                    QString line;
                    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
                        QTextStream stream(&file);
                        while (!stream.atEnd()){
                            line = stream.readLine();
                            text = text + line + "\n";
                        }
                    }
                    file.close();

                ruleLabel -> setText(text);
                ruleLabel -> setWordWrap(true);
                ruleLabel -> setTextInteractionFlags(Qt::TextSelectableByMouse);
                ruleLabel->setTextFormat(Qt::RichText);
                ruleLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
                ruleLabel->setOpenExternalLinks(true);

            ruleScroll -> setWidget(ruleLabel);
            
            ruleStacked -> addWidget(ruleScroll);


			ruleStacked -> setCurrentWidget(persoScroll);
        
			ruleLayout -> addWidget(ruleBox);

		ruleBox -> setLayout(ruleLayout);

    tabInsideLayout -> addWidget(ruleBox, 1, 0, 1, 2);

    tabInside -> setLayout(tabInsideLayout);

    layout -> addWidget(tabInside, 1,1,2,1);

    //key shortcut
    shortcut = new QShortcut(QKeySequence("Escape"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(emitClose()));

    setLayout(layout);

}


RuleTab::~RuleTab (){

    delete ruEffect;
    delete shortcut;

    delete ruleLabel;
    delete ruleScroll;
    delete lifePoints;
    delete lifeDesc;
    delete cardDrawNumber;
    delete cardDrawDesc;

    delete persoPaneLayout;
    delete persoScrollBox;
    delete persoScroll;

        delete rulesButt;
        delete persoButt;
    
    delete tabLayout;
    delete tabBox;

	delete ruleStacked;
    delete ruleLayout;

    delete ruleBox;

    delete tabInsideLayout;
    delete tabInside;

    delete info;
    delete exitButt;
    delete infoLayout;
    delete iffect;
    delete infoBox;

    delete layout;
}


void RuleTab::init (){

    currButt = persoButt;
    persoButt -> setFocus();
}

void RuleTab::reInit (){

    updateStyle(currButt);
}


void RuleTab::setRules (){

    updateStyle(rulesButt);

        ruleStacked -> setCurrentWidget(ruleScroll);
    }


void RuleTab::setPerso (){

    updateStyle(persoButt);

    ruleStacked -> setCurrentWidget(persoScroll);
}


void RuleTab::updateStyle (QPushButton * b){
     
    currButt -> setProperty("down", false);
    b -> setProperty("down", true);

    currButt -> style() -> unpolish(currButt);
    currButt -> style() -> polish(currButt);
    
    b -> style() -> unpolish(b);
    b -> style() -> polish(b);

    currButt = b;
}


void RuleTab::emitClose (){

    emit introStack();
}


void RuleTab::loadPersoSettings (){

    QSettings settings;
    QString val1,val2;

    val1=settings.value("lifePoints","4000").toString();
    val2=settings.value("cardDrawNumber","1").toString();
    
    lifePoints->setCurrentIndex(lifePoints->findText(val1));
    cardDrawNumber->setCurrentIndex(cardDrawNumber->findText(val2));

}

void RuleTab::lifeChange(){

    QSettings settings;
    settings.setValue("lifePoints",lifePoints->currentText());

}

void RuleTab::cardDrawNumberChange(){

    QSettings settings;
    settings.setValue("cardDrawNumber",cardDrawNumber->currentText());

}


void RuleTab::readLangage(){
    QSettings settings;
    valeur = settings.value("langage", QLocale::system().name()).toString();
}
