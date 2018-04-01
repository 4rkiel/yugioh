#include "../inc/optab.h"

/******************************************************************************

    Widget recréant un QTabWidget personnalisé

	Permet d'afficher le sous-menu des Options

******************************************************************************/

OptionTab::OptionTab (){

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

        info = new QLabel (tr("Paramètres"));

        infoLayout -> addWidget(info);

        infoLayout -> addStretch(1);
        
        exitButt = new FlatButt("\uf060", "");
        exitButt -> setToolTip(tr("Fermer les paramètres"));
        connect(exitButt, SIGNAL(clicked()), this, SLOT(emitClose()));
        infoLayout -> addWidget(exitButt);


        
        
        infoBox -> setLayout(infoLayout);

    layout -> addWidget(infoBox, 0,0,1,3);


    tabInside = new QWidget;
    tabInside -> setObjectName("tabInside");
    tabInsideLayout = new QGridLayout;
    tabInsideLayout -> setSpacing(0);
    tabInsideLayout -> setMargin(0);
    tabInsideLayout -> setContentsMargins(30,0,30,0);


 
    optEffect = new QGraphicsDropShadowEffect(this);
    optEffect -> setBlurRadius(5);
    optEffect -> setXOffset(0);
    optEffect -> setYOffset(5);
    optEffect -> setColor(QColor(0,0,0,150));

    tabInside -> setGraphicsEffect(optEffect);




        // Tab box ............................................................

        tabBox = new QWidget;
        tabBox -> setObjectName("optionTab");
        tabBox -> setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Maximum);
        tabLayout = new QGridLayout;
        tabLayout -> setSpacing(0);
        tabLayout -> setMargin(0);


            optionButt = new QPushButton;
            optionButt->setDefault(true);
            optionButt -> setText("Options");
            optionButt -> setProperty("down", true);
            connect(optionButt, SIGNAL(clicked()), this, SLOT(setOption()));
            tabLayout -> addWidget(optionButt, 0, 0, 1, 1);
            

            accessButt = new QPushButton;
            accessButt->setDefault(true);
            accessButt -> setText(tr("Accessibilité"));
            accessButt -> setProperty("down", false);
            connect(accessButt, SIGNAL(clicked()), this, SLOT(setAccess()));
            tabLayout -> addWidget(accessButt, 0, 1, 1, 1);

/*
            raccButt = new QPushButton;
            raccButt -> setText("Options");
            raccButt -> setProperty("down", true);
            connect(raccButt, SIGNAL(clicked()), this, SLOT(setRacc()));
            tabLayout -> addWidget(raccButt, 0, 0, 1, 1);
*/ 

            QSpacerItem * spacerButt = new QSpacerItem(1,1,
                    QSizePolicy::Expanding,QSizePolicy::Preferred);
            tabLayout -> addItem(spacerButt, 0, 2);



        tabBox -> setLayout(tabLayout);

        tabInsideLayout -> addWidget(tabBox, 0, 0, 1, 1);



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
                shareChck -> setText(tr("Partage"));
                connect(shareChck, SIGNAL(toggled(bool)), this, SLOT(shareChange())); 
                optPaneLayout -> addWidget(shareChck);

                shareDesc = new QLabel;
                shareDesc -> setWordWrap(true);
                shareDesc -> setTextInteractionFlags(Qt::NoTextInteraction);
                shareDesc -> setText(tr("Partage les données d'utilisation"));
                optPaneLayout -> addWidget(shareDesc);


                // Langage
                
                langInput = new QComboBox;
                langInput -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
                langInput -> addItem(QString::fromUtf8("Français"));
                langInput -> addItem("English");
                connect(langInput,SIGNAL(currentIndexChanged(QString)),this,SLOT(langageChange()));
                optPaneLayout -> addWidget(langInput);

                langDesc = new QLabel;
                langDesc -> setTextInteractionFlags(Qt::NoTextInteraction);
                langDesc -> setText(tr("Langue de l'interface"));
                optPaneLayout -> addWidget(langDesc);


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
                largeChck -> setText(tr("Large texte"));
                connect(largeChck, SIGNAL(toggled(bool)), this, SLOT(largeChange())); 
                accPaneLayout -> addWidget(largeChck);

                largeDesc = new QLabel;
                largeDesc -> setWordWrap(true);
                largeDesc -> setTextInteractionFlags(Qt::NoTextInteraction);
                largeDesc -> setText(tr("Textes de grande taille"));
                accPaneLayout -> addWidget(largeDesc);


                // Dyslexie
                
                dyslexChck = new QCheckBox;
                dyslexChck -> setText(tr("Dyslexie"));
                connect(dyslexChck, SIGNAL(toggled(bool)), this, SLOT(dyslexChange())); 
                accPaneLayout -> addWidget(dyslexChck);

                dyslexDesc = new QLabel;
                dyslexDesc -> setWordWrap(true);
                dyslexDesc -> setTextInteractionFlags(Qt::NoTextInteraction);
                dyslexDesc -> setText(tr("Textes adaptés à la dyslexie"));
                accPaneLayout -> addWidget(dyslexDesc);


                // Contraste
                
                contrasteChck = new QCheckBox;
                contrasteChck -> setText(tr("Contraste élevé"));
                connect(contrasteChck, SIGNAL(toggled(bool)), this, SLOT(contrasteChange())); 
                accPaneLayout -> addWidget(contrasteChck);

                contrasteDesc = new QLabel;
                contrasteDesc -> setWordWrap(true);
                contrasteDesc -> setTextInteractionFlags(Qt::NoTextInteraction);
                contrasteDesc -> setText(tr("Augmenter les contrastes de l'application"));
                accPaneLayout -> addWidget(contrasteDesc);


                // Achromatopsie
                
                achromaChck = new QCheckBox;
                achromaChck -> setText(tr("Couleurs pour Dyschromatopsie"));
                connect(achromaChck, SIGNAL(toggled(bool)), this, SLOT(achromaChange())); 
                accPaneLayout -> addWidget(achromaChck);

                achromaDesc = new QLabel;
                achromaDesc -> setWordWrap(true);
                achromaDesc -> setTextInteractionFlags(Qt::NoTextInteraction);
                achromaDesc -> setText(tr("Adapter l'affichage des couleurs"));
                accPaneLayout -> addWidget(achromaDesc);

               

                // load settings

                loadAccSettings();


            accessScrollBox -> setLayout(accPaneLayout); 
            accessScroll -> setWidget(accessScrollBox);


            optionLayout -> addWidget(accessScroll);


        optionLayout -> setCurrentWidget(optionScroll);
        optBox -> setLayout(optionLayout);

    tabInsideLayout -> addWidget(optBox, 1, 0, 2, 1);

    tabInside -> setLayout(tabInsideLayout);

    layout -> addWidget(tabInside, 1, 0, 1, 1);

    //key shortcut
    shortcut = new QShortcut(QKeySequence("Escape"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(emitClose()));

    setLayout(layout);

}


OptionTab::~OptionTab (){

    delete optEffect;

        delete contrasteChck;
        delete contrasteDesc;

        delete achromaChck;
        delete achromaDesc;

        delete dyslexChck;
        delete dyslexDesc;

        delete largeChck;
        delete largeDesc;


    delete accPaneLayout;
    delete accessScrollBox;
    delete accessScroll;

        delete shareChck;
        delete shareDesc;

        delete langInput;
        delete langDesc;

    delete optPaneLayout;
    delete optionScrollBox;
    delete optionScroll;

        delete accessButt;
        delete optionButt;
    
    delete tabLayout;
    delete tabBox;
    delete optionLayout;

    delete optBox;

    delete tabInsideLayout;
    delete tabInside;

    delete info;
    delete exitButt;
    delete infoLayout;
    delete iffect;
    delete infoBox;

    delete layout;
}

void OptionTab::init (){

    currButt = optionButt;
    optionButt -> setFocus();
}

void OptionTab::reInit(){
    updateStyle(currButt);
}

void OptionTab::setOption (){

    updateStyle(optionButt);

    optionLayout -> setCurrentWidget(optionScroll);
}


void OptionTab::setAccess (){
 
    updateStyle(accessButt);
    
    optionLayout -> setCurrentWidget(accessScroll);
}


void OptionTab::updateStyle (QPushButton * b){

    currButt -> setProperty("down", false);
    b -> setProperty("down", true);

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

    if (settings.value("dyslexie", Qt::Unchecked).toBool()){
        dyslexChck -> setCheckState(Qt::Checked);
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


    QString val = settings.value("langage", "fr_FR").toString();

    if (val == "fr_FR"){
        langInput -> setCurrentIndex(langInput -> findText(QString::fromUtf8("Français")));
    } else if (val == "en_US"){
        langInput -> setCurrentIndex(langInput -> findText("English"));
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

void OptionTab::langageChange(){

    QSettings settings;
    if(langInput -> currentText()==QString::fromUtf8("Français"))
        settings.setValue("langage", "fr_FR");

    if(langInput -> currentText()=="English")
        settings.setValue("langage", "en_US");

    emit newSettings();
}

void OptionTab::achromaChange (){

    QSettings settings;
    settings.setValue("achroma", achromaChck -> isChecked());

    emit newSettings();
}

void OptionTab::dyslexChange (){

    QSettings settings;
    settings.setValue("dyslexie", dyslexChck -> isChecked());

    emit newSettings();
}

void OptionTab::largeChange (){

    QSettings settings;
    settings.setValue("large", largeChck -> isChecked());

    emit newSettings();
}

//fonction qui change dynamiquement la langue
void OptionTab::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        info->setText(tr("Paramètres"));
        exitButt -> setToolTip(tr("Fermer les paramètres"));
		accessButt -> setText(tr("Accessibilité"));
        shareChck -> setText(tr("Partage"));
        shareDesc -> setText(tr("Partage les données d'utilisation"));
        langDesc -> setText(tr("Langue de l'interface"));
        largeChck -> setText(tr("Large texte"));
        largeDesc -> setText(tr("Textes de grande taille"));
        contrasteChck -> setText(tr("Contraste élevé"));
        contrasteDesc -> setText(tr("Augmenter les contrastes de l'application"));
        dyslexChck -> setText(tr("Dyslexie"));
        dyslexDesc -> setText(tr("Textes adaptés à la dyslexie"));
        achromaChck -> setText(tr("Couleurs pour Dyschromatopsie"));
        achromaDesc -> setText(tr("Adapter l'affichage des couleurs"));
    } else
        QWidget::changeEvent(event);
}

