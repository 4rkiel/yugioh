#include "../inc/soloChoice.h"

/******************************************************************************

    Widget recréant un QTabWidget personnalisé

	Une fois le choix Solo réalisé: il faut choisir le type d'IA comme
    adversaire

******************************************************************************/

SoloChoice::SoloChoice () {

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
            
            info = new QLabel (tr("Partie Solo"));

            infoLayout -> addWidget(info);

            infoLayout -> addStretch(1);
       
            // Back Button
            
            choice = new FlatButt("\uf060", "");
            choice -> setToolTip(tr("Retour au Menu"));
            connect(choice, SIGNAL(clicked()), this, SLOT(emitBack()));
            //infoLayout -> addWidget(choice);
            infoBox -> setLayout(infoLayout);

        layout -> addWidget(infoBox, 0,0,1,3);
        
        
        
        // Intro Menu 

        introBox = new QWidget;
        introBox -> setObjectName("introBox");

        effect = new QGraphicsDropShadowEffect(this);
        effect -> setBlurRadius(5);
        effect -> setXOffset(0);
        effect -> setYOffset(5);
        effect -> setColor(QColor(0,0,0,150));

        introBox -> setGraphicsEffect(effect);

        box = new QVBoxLayout;
        box -> setContentsMargins(0,0,0,0);
        box -> setSpacing(0);
        box -> setMargin(0);
            
 
            // Text

            intro = new QLabel;
            intro -> setObjectName("introText");
            intro -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
            QString strIntro = tr("Choix de la difficulté");
            intro -> setText(strIntro);
            intro -> setContentsMargins(30,30,30,30);
            box -> addWidget(intro);
          

            // Easy
            
            QString strEasy = tr("Facile");
            easy = new FlatExpButt("\uf443", strEasy);
            easy -> setToolTip(tr("Adversaire débutant"));
            connect(easy, SIGNAL(clicked()), this, SLOT(emitEasy()));
            box -> addWidget(easy);

            sep1 = new QFrame;
            sep1 -> setFixedHeight(1);
            sep1 -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            box -> addWidget(sep1);
            

            // Medium
            
            QString strMed = tr("Normal");
            med = new FlatExpButt("\uf447", strMed);
            med -> setToolTip(tr("Adversaire expert"));
            connect(med, SIGNAL(clicked()), this, SLOT(emitMed()));
            box -> addWidget(med);

 
            sep2 = new QFrame;
            sep2 -> setFixedHeight(1);
            sep2 -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            box -> addWidget(sep2);
          
              
            // Hard
            
            QString strHard = tr("Difficile");
            hard = new FlatExpButt("\uf445", strHard);
            hard -> setToolTip(tr("Adversaire expert"));
            connect(hard, SIGNAL(clicked()), this, SLOT(emitHard()));
            box -> addWidget(hard);

        introBox -> setLayout(box);

        layout -> setRowStretch(1,1);
        layout -> addWidget(introBox, 2, 1, 4, 1);
        layout -> setRowStretch(6,1);

        // key shortcut
        shortcut = new QShortcut(QKeySequence("Escape"), this);
        connect(shortcut, SIGNAL(activated()), this, SLOT(emitBack()));

    setLayout(layout);
}

    
SoloChoice::~SoloChoice (){

    delete shortcut;
    
    delete intro;
    delete easy;
    delete med;
    delete hard;

    delete sep1;
    delete sep2;

    delete effect;

    delete box;
    delete introBox;

    delete iffect;
    delete info;
    delete choice;
    delete infoLayout;
    delete infoBox;

    delete layout;
}


void SoloChoice::init (){
    choice -> setFocus();
    infoLayout -> addWidget(choice);
}



void SoloChoice::emitBack (){
    emit choiceStack();
}


void SoloChoice::emitEasy (){
    emit gameStack(11);
}


void SoloChoice::emitMed (){
    emit gameStack(12);
}


void SoloChoice::emitHard (){
    emit gameStack(13);
}
