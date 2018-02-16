#include "generique.h"


Generique::Generique () {

    layout = new QGridLayout;
 
    layout -> setSpacing(0);
    layout -> setMargin(0);

   
    geneBox = new QWidget;
    box = new QVBoxLayout;

    box -> setSpacing(0);
    box -> setMargin(0);


    // State label

    state = new QLabel;

    QString str = QString::fromUtf8("Initialisation...");
    state -> setText(str);
    state -> setWordWrap(true);

    box -> addWidget(state);


    // Loading Progress Bar
    
    progress = new GenProgress;

    connect( progress, SIGNAL(endProgress()), this, SLOT(goToStack()) );

    box -> addWidget(progress);



    labelCount = 0;

    connect (progress, SIGNAL(newProgress()), this, SLOT(newLabel()) );


    layout -> addWidget(geneBox, 0, 0, 1, 1, Qt::AlignBottom);

    geneBox -> setLayout(box);
    this -> setLayout(layout);
}

    
Generique::~Generique (){

    delete progress;
    delete state;

    delete box;
    delete geneBox;
    delete layout;
}


void Generique::goToStack (){
    emit introStack();
}

void Generique::newLabel (){

    labelCount ++ ;
    
    QString str;

    switch (labelCount){
        case 1:
            str = QString::fromUtf8("Chargement de l'amitié");
            break;
        case 2:
            str = QString::fromUtf8("Synchro de l'heure du D-D-D-D-D-Duel");
            break;
        case 3:
            str = QString::fromUtf8("Configuration de l'âme des cartes");
            break;
        default:
            break;
    }
    
    state -> setText(str);
}


