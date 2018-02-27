#include "optab.h"

OptionTab::OptionTab (){

    layout = new QGridLayout;
    layout -> setSpacing(0);
    layout -> setMargin(0);
    
    optEffect = new QGraphicsDropShadowEffect(this);
    optEffect -> setBlurRadius(5);
    optEffect -> setXOffset(0);
    optEffect -> setYOffset(5);
    optEffect -> setColor(QColor(0,0,0,150));

    setGraphicsEffect(optEffect);

        // Tab box ............................................................

        tabBox = new QWidget;
        tabBox -> setObjectName("optionTab");
        tabLayout = new QGridLayout;
        tabLayout -> setSpacing(0);
        tabLayout -> setMargin(0);
  
            exitButt = new ShadowButt("\uf00d", "");
            exitButt -> setToolTip("Fermer les paramètres");
            connect(exitButt, SIGNAL(clicked()), this, SLOT(emitClose()));
            
            tabLayout -> addWidget(exitButt, 0, 4, 1, 1);



            optionButt = new QPushButton;
            optionButt -> setText("Options");
            optionButt -> setProperty("down", true);
            connect(optionButt, SIGNAL(clicked()), this, SLOT(setOption()));
            tabLayout -> addWidget(optionButt, 0, 0, 1, 1);
            

            accessButt = new QPushButton;
            accessButt -> setText("Accessibilité");
            accessButt -> setProperty("down", false);
            connect(accessButt, SIGNAL(clicked()), this, SLOT(setAccess()));
            tabLayout -> addWidget(accessButt, 0, 1, 1, 1);

            aboutButt = new QPushButton;
            aboutButt -> setText("A Propos");
            aboutButt -> setProperty("down", false);
            connect(aboutButt, SIGNAL(clicked()), this, SLOT(setAbout()));
            tabLayout -> addWidget(aboutButt, 0, 2, 1, 1);

            QSpacerItem * spacerButt = new QSpacerItem(1,1,
                    QSizePolicy::Expanding,QSizePolicy::Preferred);
            tabLayout -> addItem(spacerButt, 0, 3);

        tabBox -> setLayout(tabLayout);


    layout -> addWidget(tabBox, 0, 0, 1, 1);



        // Label Box ..........................................................

        optBox = new QWidget;
        optBox -> setObjectName("optBox");
        
        optionLayout = new QStackedLayout;
        optionLayout -> setSpacing(0);
        optionLayout -> setMargin(0);


            // Options ........................................................

            optionScroll = new QScrollArea;
            optionScroll -> setFrameShape(QFrame::NoFrame);
            optionScroll -> setWidgetResizable(true);
            optionScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            optionScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            optionScroll -> setFocusPolicy(Qt::NoFocus);

            optionScrollBox = new QWidget;
            optPaneLayout = new QVBoxLayout;
            optPaneLayout -> setAlignment(Qt::AlignTop);

                // Share
                
                shareChck = new QCheckBox;
                shareChck -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
                shareChck -> setText("Partage");
                connect(shareChck, SIGNAL(toggled(bool)), this, SLOT(shareChange())); 
                optPaneLayout -> addWidget(shareChck);

                shareDesc = new QLabel;
                shareDesc -> setWordWrap(true);
                shareDesc -> setTextInteractionFlags(Qt::NoTextInteraction);
                shareDesc -> setText("Partage les données d'utilisation");
                optPaneLayout -> addWidget(shareDesc);


                // Langage
                
                langInput = new QComboBox;
                langInput -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
                langInput -> addItem("Français");
                langInput -> addItem("English");
                optPaneLayout -> addWidget(langInput);

                langDesc = new QLabel;
                langDesc -> setTextInteractionFlags(Qt::NoTextInteraction);
                langDesc -> setText("Langue de l'interface");
                optPaneLayout -> addWidget(langDesc);

                // Shortcut

                shortcutDesc = new QLabel;
                shortcutDesc -> setTextInteractionFlags(Qt::NoTextInteraction);
                shortcutDesc -> setText("Raccourcis Clavier");
                optPaneLayout -> addWidget(shortcutDesc);
            

                // load settings

                loadOptSettings();


            optionScrollBox -> setLayout(optPaneLayout); 
            optionScroll -> setWidget(optionScrollBox);

            optionLayout -> addWidget(optionScroll);

            
            // Accessibility ..................................................

            accessScroll = new QScrollArea;
            accessScroll -> setFrameShape(QFrame::NoFrame);
            accessScroll -> setWidgetResizable(true);
            accessScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            accessScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            accessScroll -> setFocusPolicy(Qt::NoFocus);

            accessScrollBox = new QWidget;
            accPaneLayout = new QVBoxLayout;
            accPaneLayout -> setAlignment(Qt::AlignTop);

             
                // Large text
                
                largeChck = new QCheckBox;
                largeChck -> setText("Large texte");
                connect(largeChck, SIGNAL(toggled(bool)), this, SLOT(largeChange())); 
                accPaneLayout -> addWidget(largeChck);

                largeDesc = new QLabel;
                largeDesc -> setWordWrap(true);
                largeDesc -> setTextInteractionFlags(Qt::NoTextInteraction);
                largeDesc -> setText("Textes de grande taille");
                accPaneLayout -> addWidget(largeDesc);


                // Contraste
                
                contrasteChck = new QCheckBox;
                contrasteChck -> setText("Contraste élevé");
                connect(contrasteChck, SIGNAL(toggled(bool)), this, SLOT(contrasteChange())); 
                accPaneLayout -> addWidget(contrasteChck);

                contrasteDesc = new QLabel;
                contrasteDesc -> setWordWrap(true);
                contrasteDesc -> setTextInteractionFlags(Qt::NoTextInteraction);
                contrasteDesc -> setText("Augmenter les contrastes de l'application");
                accPaneLayout -> addWidget(contrasteDesc);


                // Achromatopsie
                
                achromaChck = new QCheckBox;
                achromaChck -> setText("Couleurs pour Dyschromatopsie");
                connect(achromaChck, SIGNAL(toggled(bool)), this, SLOT(achromaChange())); 
                accPaneLayout -> addWidget(achromaChck);

                achromaDesc = new QLabel;
                achromaDesc -> setWordWrap(true);
                achromaDesc -> setTextInteractionFlags(Qt::NoTextInteraction);
                achromaDesc -> setText("Adapter l'affichage des couleurs");
                accPaneLayout -> addWidget(achromaDesc);

               

                // load settings

                loadAccSettings();


            accessScrollBox -> setLayout(accPaneLayout); 
            accessScroll -> setWidget(accessScrollBox);


            optionLayout -> addWidget(accessScroll);


            // About ..........................................................

            aboutScroll = new QScrollArea;
            aboutScroll -> setFrameShape(QFrame::NoFrame);
            aboutScroll -> setWidgetResizable(true);
            aboutScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            aboutScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
 

                aboutLabel = new QLabel;

                    QFile file("i18n/fr_FR/about.text");

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

            
            optionLayout -> addWidget(aboutScroll);


        optionLayout -> setCurrentWidget(optionScroll);
        optBox -> setLayout(optionLayout);

    layout -> addWidget(optBox, 1, 0, 1, 2);

    setLayout(layout);

}


OptionTab::~OptionTab (){

    delete optEffect;

    delete aboutLabel;
    delete aboutScroll;

        delete contrasteChck;
        delete contrasteDesc;

        delete achromaChck;
        delete achromaDesc;
        
        delete largeChck;
        delete largeDesc;


    delete accPaneLayout;
    delete accessScrollBox;
    delete accessScroll;

        delete shareChck;
        delete shareDesc;

        delete langInput;
        delete langDesc;

        delete shortcutDesc;

    delete optPaneLayout;
    delete optionScrollBox;
    delete optionScroll;

        delete exitButt;
        delete aboutButt;
        delete accessButt;
        delete optionButt;
    
    delete tabLayout;
    delete tabBox;
    delete optionLayout;

    delete optBox;

    delete layout;
}

void OptionTab::init (){

    currButt = optionButt;
    optionButt -> setFocus();
}


void OptionTab::setOption (){

    currButt -> setProperty("down", false);
    optionButt -> setProperty("down", true);

    updateStyle(optionButt);

    optionLayout -> setCurrentWidget(optionScroll);
}


void OptionTab::setAccess (){
 
    currButt -> setProperty("down", false);
    accessButt -> setProperty("down", true);
   
    updateStyle(accessButt);
    
    optionLayout -> setCurrentWidget(accessScroll);
}


void OptionTab::setAbout (){
 
    currButt -> setProperty("down", false);
    aboutButt -> setProperty("down", true);

    updateStyle(aboutButt);

    optionLayout -> setCurrentWidget(aboutScroll);
}


void OptionTab::updateStyle (QPushButton * b){
    
    currButt -> style() -> unpolish(currButt);
    currButt -> style() -> polish(currButt);
    
    b -> style() -> unpolish(b);
    b -> style() -> polish(b);

    currButt = b;
}


void OptionTab::emitClose (){

    emit introStack();
}


void OptionTab::loadAccSettings (){

    QSettings settings;

    if (settings.value("contraste", Qt::Unchecked).toBool()){
        contrasteChck -> setCheckState(Qt::Checked);
    }

    if (settings.value("achroma", Qt::Unchecked).toBool()){
        achromaChck -> setCheckState(Qt::Checked);
    }

    if (settings.value("large", Qt::Unchecked).toBool()){
        largeChck -> setCheckState(Qt::Checked);
    }

}


void OptionTab::loadOptSettings (){

    QSettings settings;
    
    if (settings.value("share", Qt::Unchecked).toBool()){
        shareChck -> setCheckState(Qt::Checked);
    }

}


void OptionTab::shareChange (){

    QSettings settings;
    settings.setValue("share", shareChck -> isChecked());

    emit newSettings();
}



void OptionTab::contrasteChange (){

    QSettings settings;
    settings.setValue("contraste", contrasteChck -> isChecked());

    emit newSettings();
}



void OptionTab::achromaChange (){

    QSettings settings;
    settings.setValue("achroma", achromaChck -> isChecked());

    emit newSettings();
}



void OptionTab::largeChange (){

    QSettings settings;
    settings.setValue("large", largeChck -> isChecked());

    emit newSettings();
}



