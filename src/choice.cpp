#include "../inc/choice.h"

Choice::Choice () {

    layout = new QGridLayout;
    layout -> setAlignment(Qt::AlignCenter);
    layout -> setSpacing(0);
    layout -> setMargin(0);


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


            // New Game Button
          
            QString strButton = QString::fromUtf8("Local");
            local = new ShadowButt("\uf007", strButton);
            local -> setToolTip("Commencer une Partie Solo");
            connect(local, SIGNAL(clicked()), this, SLOT(emitLocal()));
            box -> addWidget(local);



            // Back Button

            QString strIntro = QString::fromUtf8("Retour");
            intro = new ShadowButt("\uf060", strIntro);
            intro -> setToolTip("Retour au Menu");
            connect(intro, SIGNAL(clicked()), this, SLOT(emitIntro()));
            box -> addWidget(intro);


        introBox -> setLayout(box);
        layout -> addWidget(introBox, 0, 0, 1, 1);


    setLayout(layout);
}

    
Choice::~Choice (){

    delete intro;
    delete local;

    delete effect;

    delete box;
    delete introBox;
    delete layout;
}


void Choice::init (){
    local -> setFocus();
}



void Choice::emitIntro (){
    emit introStack();
}

void Choice::emitLocal (){
    emit localStack();
}
