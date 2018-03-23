#include "../inc/ruletab.h"

/******************************************************************************

    Widget recréant un QTabWidget personnalisé
	
	Permet d'afficher le sous-menu des Règles (lecture et personnalisation)

******************************************************************************/

RuleTab::RuleTab (){

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

        info = new QLabel ("Règles");

        infoLayout -> addWidget(info);
        infoBox -> setLayout(infoLayout);

    layout -> addWidget(infoBox, 0,0,1,3);


    tabInside = new QWidget;
    tabInside -> setObjectName("tabInside");
    tabInsideLayout = new QGridLayout;
    tabInsideLayout -> setSpacing(0);
    tabInsideLayout -> setMargin(0);
    tabInsideLayout -> setContentsMargins(30,0,30,0);



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
  
            exitButt = new ShadowButt("\uf060", "Retour");
            exitButt -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
            exitButt -> setToolTip("Fermer les règles");
            connect(exitButt, SIGNAL(clicked()), this, SLOT(emitClose()));
            
            tabLayout -> addWidget(exitButt, 0, 4, 1, 1);


            persoButt = new QPushButton;
            persoButt -> setText("Personnalisation");
            persoButt -> setProperty("down", true);
            connect(persoButt, SIGNAL(clicked()), this, SLOT(setPerso()));

            tabLayout -> addWidget(persoButt, 0, 0, 1, 1);
            

            rulesButt = new QPushButton;
            rulesButt -> setText("Règles du Jeu");
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
        
        ruleLayout = new QStackedLayout;
        ruleLayout -> setSpacing(0);
        ruleLayout -> setMargin(0);


            // Personnalisation ...............................................

            persoScroll = new QScrollArea;
            persoScroll -> setFrameShape(QFrame::NoFrame);
            persoScroll -> setWidgetResizable(true);
            persoScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            persoScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            persoScroll -> setFocusPolicy(Qt::NoFocus);

            persoScrollBox = new QWidget;
            persoPaneLayout = new QVBoxLayout;
            persoPaneLayout -> setAlignment(Qt::AlignTop);

            /*
                // Share
                
                shareChck = new QCheckBox;
                shareChck -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
                shareChck -> setText("Partage");
                connect(shareChck, SIGNAL(toggled(bool)), this, SLOT(shareChange())); 
                persoPaneLayout -> addWidget(shareChck);

                shareDesc = new QLabel;
                shareDesc -> setWordWrap(tperse);
                shareDesc -> setTextInteractionFlags(Qt::NoTextInteraction);
                shareDesc -> setText("Partage les données d'utilisation");
                persoPaneLayout -> addWidget(shareDesc);


                // Langage
                
                langInput = new QComboBox;
                langInput -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
                langInput -> addItem("Français");
                langInput -> addItem("English");
                persoPaneLayout -> addWidget(langInput);

                langDesc = new QLabel;
                langDesc -> setTextInteractionFlags(Qt::NoTextInteraction);
                langDesc -> setText("Langue de l'interface");
                persoPaneLayout -> addWidget(langDesc);

                // Shortcut

                shortcutDesc = new QLabel;
                shortcutDesc -> setTextInteractionFlags(Qt::NoTextInteraction);
                shortcutDesc -> setText("Raccourcis Clavier");
                persoPaneLayout -> addWidget(shortcutDesc);
            
            */
//
                // load settings

                loadPersoSettings();


            persoScrollBox -> setLayout(persoPaneLayout); 
            persoScroll -> setWidget(persoScrollBox);

            ruleLayout -> addWidget(persoScroll);

           


            // About ..........................................................

            ruleScroll = new QScrollArea;
            ruleScroll -> setFrameShape(QFrame::NoFrame);
            ruleScroll -> setWidgetResizable(true);
            ruleScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            ruleScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
 

                ruleLabel = new QLabel;

                    QFile file("i18n/"+QLocale::system().name()+"/rules.text");

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
            
            ruleLayout -> addWidget(ruleScroll);


        ruleLayout -> setCurrentWidget(persoScroll);
        ruleBox -> setLayout(ruleLayout);

    tabInsideLayout -> addWidget(ruleBox, 1, 0, 1, 2);

    tabInside -> setLayout(tabInsideLayout);

    layout -> addWidget(tabInside, 1,1,2,1);

    setLayout(layout);

}


RuleTab::~RuleTab (){

    delete ruEffect;

    delete ruleLabel;
    delete ruleScroll;

    delete persoPaneLayout;
    delete persoScrollBox;
    delete persoScroll;

        delete exitButt;
        delete rulesButt;
        delete persoButt;
    
    delete tabLayout;
    delete tabBox;
    delete ruleLayout;

    delete ruleBox;

    delete tabInsideLayout;
    delete tabInside;

    delete info;
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

        ruleLayout -> setCurrentWidget(ruleScroll);
    }


void RuleTab::setPerso (){

    updateStyle(persoButt);

    ruleLayout -> setCurrentWidget(persoScroll);
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
/*
    QSettings settings;
    
    if (settings.value("share", Qt::Unchecked).toBool()){
        shareChck -> setCheckState(Qt::Checked);
    }
*/
}

/*
void RuleTab::shareChange (){

    QSettings settings;
    settings.setValue("share", shareChck -> isChecked());
}



void RuleTab::contrasteChange (){

    QSettings settings;
    settings.setValue("contraste", contrasteChck -> isChecked());
}



void RuleTab::achromaChange (){

    QSettings settings;
    settings.setValue("achroma", achromaChck -> isChecked());
}



void RuleTab::largeChange (){

    QSettings settings;
    settings.setValue("large", largeChck -> isChecked());
}

*/

