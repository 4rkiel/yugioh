#include "../inc/joinChoice.h"

/******************************************************************************

    Widget recréant un QTabWidget personnalisé

	Permet d'implémenter le sous-menu de choix de parties

******************************************************************************/

JoinChoice::JoinChoice () {

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

        info = new QLabel ("Partie Privée : Rejoindre");

        infoLayout -> addWidget(info);
        infoBox -> setLayout(infoLayout);

        layout -> addWidget(infoBox, 0,0,1,3);
        
        
        
        // Intro Menu 

        introBox = new QWidget;
        introBox -> setObjectName("introBox");
        introBox -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        effect = new QGraphicsDropShadowEffect(this);
        effect -> setBlurRadius(5);
        effect -> setXOffset(0);
        effect -> setYOffset(5);
        effect -> setColor(QColor(0,0,0,150));

        introBox -> setGraphicsEffect(effect);

        box = new QGridLayout;

            // Back Button

            QString strIntro = QString::fromUtf8("Retour");
            choice = new ShadowButt("\uf060", strIntro);
            choice -> setToolTip("Retour au Menu");
            connect(choice, SIGNAL(clicked()), this, SLOT(emitChoice()));
            
            box -> addWidget(choice, 3, 0, 1, 3);



// http://www.qtcentre.org/threads/42456-How-to-connect-QLineEdit-to-quot-ENTER-quot-key-press-form-keyboard


            // IP 

            input = new QLineEdit;
            input -> setContentsMargins(30,0,30,0);
            input -> setAlignment(Qt::AlignCenter);
            input -> setPlaceholderText("192.168.0.1:7777");
            input -> setStyleSheet("padding: 5px");

            box -> addWidget(input, 1, 1, 1, 1);


            box -> setRowStretch(0,20);
            box -> setRowStretch(2,20);
            box -> setRowStretch(4,1);




        introBox -> setLayout(box);
        layout -> addWidget(introBox, 2, 1, 1, 1);


    setLayout(layout);
}

    
JoinChoice::~JoinChoice (){

    delete choice;
    delete input;

    delete effect;

    delete box;
    delete introBox;

    delete iffect;
    delete info;
    delete infoLayout;
    delete infoBox;

    delete layout;
}


void JoinChoice::init (){
   // local -> setFocus();
}


void JoinChoice::emitChoice (){
    emit choiceStack();
}

