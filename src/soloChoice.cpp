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

        info = new QLabel (tr("Partie Solo"));

        infoLayout -> addWidget(info);
        infoBox -> setLayout(infoLayout);

        layout -> addWidget(infoBox, 0,0,1,3);
        
        
        
        // Intro Menu 

        introBox = new QWidget;
        introBox -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        introBox -> setObjectName("introBox");

        effect = new QGraphicsDropShadowEffect(this);
        effect -> setBlurRadius(5);
        effect -> setXOffset(0);
        effect -> setYOffset(5);
        effect -> setColor(QColor(0,0,0,150));

        introBox -> setGraphicsEffect(effect);

        box = new QGridLayout;


            // Back Button
            
            QString strBack = tr("Retour");
            choice = new ShadowButt("\uf060", strBack);
            choice -> setToolTip(tr("Retour au Menu"));

            connect(choice, SIGNAL(clicked()), this, SLOT(emitBack()));

            box -> addWidget(choice, 7,0,1,3);

            
             
            // Hard
            
            QString strHard = tr("Difficile");
            hard = new ShadowButt("\uf445", strHard);
            hard -> setToolTip(tr("Adversaire expert"));
            connect(hard, SIGNAL(clicked()), this, SLOT(emitHard()));

            box -> addWidget(hard, 5,0,1,3);


           
            // Easy
            
            QString strEasy = tr("Facile");
            easy = new ShadowButt("\uf443", strEasy);
            easy -> setToolTip(tr("Adversaire débutant"));
            connect(easy, SIGNAL(clicked()), this, SLOT(emitEasy()));

            box -> addWidget(easy, 3,0,1,3);

            

            // Text

            intro = new QLabel;
            intro -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
            QString strIntro = tr("Choix de la difficulté :");
            intro -> setText(strIntro);
            intro -> setWordWrap(true);
            intro -> setContentsMargins(30,0,30,0);
            box -> addWidget(intro,1,1,1,1);
           


            box -> setRowStretch(0,10);
            box -> setRowStretch(2,10);
            box -> setRowStretch(4,1);
            box -> setRowStretch(6,25);
            box -> setRowStretch(8,1);


        introBox -> setLayout(box);
        layout -> addWidget(introBox, 2, 1, 1, 1);


    setLayout(layout);
}

    
SoloChoice::~SoloChoice (){

    delete intro;
    delete easy;
    delete hard;
    delete choice;

    delete effect;

    delete box;
    delete introBox;

    delete iffect;
    delete info;
    delete infoLayout;
    delete infoBox;

    delete layout;
}


void SoloChoice::init (){
//    local -> setFocus();
}



void SoloChoice::emitBack (){
    emit choiceStack();
}


void SoloChoice::emitEasy (){
    emit gameStack(11);
}


void SoloChoice::emitHard (){
    emit gameStack(12);
}
