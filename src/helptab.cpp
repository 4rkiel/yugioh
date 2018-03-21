#include "../inc/helptab.h"
#include <iostream>


/******************************************************************************

	Widget recréant un QTabWidget personnalisé

	Permet d'afficher le sous-menu d'aide

******************************************************************************/
		

HelpTab::HelpTab (){

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

        info = new QLabel ("Aide");

        infoLayout -> addWidget(info);
        infoBox -> setLayout(infoLayout);


    layout -> addWidget(infoBox, 0,0,1,3);
    
    
    tabInside = new QWidget;
    tabInside -> setObjectName("tabInside");
    tabInsideLayout = new QGridLayout;
    tabInsideLayout -> setSpacing(0);
    tabInsideLayout -> setMargin(0);
    tabInsideLayout -> setContentsMargins(30,0,30,0);
    
    
    helpEffect = new QGraphicsDropShadowEffect(this);
    helpEffect -> setBlurRadius(5);
    helpEffect -> setXOffset(0);
    helpEffect -> setYOffset(5);
    helpEffect -> setColor(QColor(0,0,0,150));

    tabInside -> setGraphicsEffect(helpEffect);




        // Tab box ............................................................

        tabBox = new QWidget;
        tabBox -> setObjectName("helpTab");
        tabLayout = new QGridLayout;
        tabLayout -> setSpacing(0);
        tabLayout -> setMargin(0);
  
            exitButt = new ShadowButt("\uf060", "Retour");
            exitButt -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
            exitButt -> setToolTip("Fermer l'aide");
            connect(exitButt, SIGNAL(clicked()), this, SLOT(emitClose()));
            
            tabLayout -> addWidget(exitButt, 0, 4, 1, 1);


            helpButt = new QPushButton;
            helpButt -> setText("Informations");
            helpButt -> setProperty("down", true);
            connect(helpButt, SIGNAL(clicked()), this, SLOT(setHelp()));

            tabLayout -> addWidget(helpButt, 0, 0, 1, 1);
            

            aboutButt = new QPushButton;
            aboutButt -> setText("A Propos");
            aboutButt -> setProperty("down", false);
            connect(aboutButt, SIGNAL(clicked()), this, SLOT(setAbout()));

            tabLayout -> addWidget(aboutButt, 0, 1, 1, 1);
            

            QSpacerItem * spacerButt = new QSpacerItem(1,1,
                    QSizePolicy::Expanding,QSizePolicy::Preferred);
            
            tabLayout -> addItem(spacerButt, 0, 2);

        tabBox -> setLayout(tabLayout);


    tabInsideLayout -> addWidget(tabBox, 0, 0, 1, 1);



        // Label Box ..........................................................

        helpBox = new QWidget;
        helpBox -> setObjectName("helpBox");
        
        helpLayout = new QStackedLayout;
        helpLayout -> setSpacing(0);
        helpLayout -> setMargin(0);


            // Help ...........................................................

            helpScroll = new QScrollArea;
            helpScroll -> setFrameShape(QFrame::NoFrame);
            helpScroll -> setWidgetResizable(true);
            helpScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            helpScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            helpScroll -> setFocusPolicy(Qt::NoFocus);

                helpLabel = new QLabel;

                    QFile hfile("i18n/fr_FR/help.text");

                    QString htext = "";
                    QString hline;
                    if (hfile.open(QIODevice::ReadOnly | QIODevice::Text)){
                        QTextStream hstream(&hfile);
                        while (!hstream.atEnd()){
                            hline = hstream.readLine();
                            htext = htext + hline + "\n";
                        }
                    }
                    hfile.close();

                helpLabel -> setText(htext);
                helpLabel -> setWordWrap(true);
                helpLabel -> setTextInteractionFlags(Qt::TextSelectableByMouse);
                helpLabel->setTextFormat(Qt::RichText);
                helpLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
                helpLabel->setOpenExternalLinks(true);

                helpScroll -> setWidget(helpLabel);

            helpLayout -> addWidget(helpScroll);

           


            // About ..........................................................

            aboutScroll = new QScrollArea;
            aboutScroll -> setFrameShape(QFrame::NoFrame);
            aboutScroll -> setWidgetResizable(true);
            aboutScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            aboutScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            readLangage();


                aboutLabel = new QLabel;
                    QFile file("i18n/"+valeur+"/about.text");

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

                aboutLabel -> setText(text);
                aboutLabel -> setWordWrap(true);
                aboutLabel -> setTextInteractionFlags(Qt::TextSelectableByMouse);
                aboutLabel->setTextFormat(Qt::RichText);
                aboutLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
                aboutLabel->setOpenExternalLinks(true);

                aboutScroll -> setWidget(aboutLabel);

            helpLayout -> addWidget(aboutScroll);


        helpLayout -> setCurrentWidget(helpScroll);
        helpBox -> setLayout(helpLayout);

    tabInsideLayout -> addWidget(helpBox, 1, 0, 1, 2);

    tabInside -> setLayout(tabInsideLayout);

    layout -> addWidget(tabInside, 1, 0, 1, 1);

    setLayout(layout);

}


HelpTab::~HelpTab (){
    
    delete helpEffect;

    delete aboutLabel;
    delete aboutScroll;

    delete helpLabel;
    delete helpScroll;

        delete exitButt;
        delete aboutButt;
        delete helpButt;
    
    delete helpLayout;
    delete helpBox;
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


void HelpTab::init (){

    currButt = helpButt;
    helpButt -> setFocus();
}

void HelpTab::reInit (){

    updateStyle(currButt);
}


void HelpTab::setHelp (){

    updateStyle(helpButt);

    helpLayout -> setCurrentWidget(helpScroll);
}


void HelpTab::setAbout (){

    updateStyle(aboutButt);

    helpLayout -> setCurrentWidget(aboutScroll);
}


void HelpTab::updateStyle (QPushButton * b){
     
    currButt -> setProperty("down", false);
    b -> setProperty("down", true);

    currButt -> style() -> unpolish(currButt);
    currButt -> style() -> polish(currButt);
    
    b -> style() -> unpolish(b);
    b -> style() -> polish(b);

    currButt = b;
}


void HelpTab::emitClose (){

    emit introStack();
}

void HelpTab::readLangage(){
    QSettings settings;
    valeur = settings.value("langage", QLocale::system().name()).toString();
}

