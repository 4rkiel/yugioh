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
        infoLayout -> setContentsMargins(0,0,0,0);
        infoLayout -> setSpacing(0);
        infoLayout -> setMargin(0);
        
            info = new QLabel (tr("Partie Privée : Rejoindre"));
            infoLayout -> addWidget(info);
       
            infoLayout -> addStretch(1);

            choice = new FlatButt("\uf060", "");
            choice -> setToolTip(tr("Retour au Menu"));
            connect(choice, SIGNAL(clicked()), this, SLOT(emitChoice()));
            infoLayout -> addWidget(choice);
        
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

            // Validation butt
			
            valid = new ShadowButt("","Valider");
            valid -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
            box -> addWidget(valid, 2,1,1,1);
			connect(valid, SIGNAL(clicked()), this, SLOT(connectIP()));


            // IP 

            input = new QLineEdit;
            input -> setContentsMargins(30,0,30,0);
            input -> setAlignment(Qt::AlignCenter);
            input -> setPlaceholderText("0:0:0:0:0:0:0:0");
            input -> setStyleSheet("padding: 5px");

            box -> addWidget(input, 1, 0, 1, 3);
            connect(input, SIGNAL(returnPressed()), this, SLOT(connectIP()));


            box -> setRowStretch(0,20);
            box -> setRowStretch(3,20);


        shortcut = new QShortcut(QKeySequence("Escape"), this);
        connect(shortcut, SIGNAL(activated()), this, SLOT(emitChoice()));


        introBox -> setLayout(box);
        layout -> addWidget(introBox, 2, 1, 1, 1);


    setLayout(layout);
}

    
JoinChoice::~JoinChoice (){

    delete shortcut;

    delete input;
    delete valid;

    delete effect;

    delete box;
    delete introBox;

    delete iffect;
    delete choice;
    delete info;
    delete infoLayout;
    delete infoBox;

    delete layout;
}


void JoinChoice::init (){
    choice -> setFocus();
}


void JoinChoice::emitChoice (){
    emit choiceStack();
}

void JoinChoice::connectIP(){

	emit sendIP(input->text());
}
