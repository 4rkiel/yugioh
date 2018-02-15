#include "generique.h"


Generique::Generique () {

    layout = new QGridLayout;
    
    geneBox = new QWidget;
    box = new QVBoxLayout;


    // State label

    state = new QLabel;

    QString str = QString::fromUtf8("Initialisation...\n");
    state -> setText(str);

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
            str = QString::fromUtf8("Chargement de\n l'amitié");
            break;
        case 2:
            str = QString::fromUtf8("Synchronisation de l'heure\n du D-D-D-D-D-D-Duel");
            break;
        case 3:
            str = QString::fromUtf8("Configuration de\n l'âme des cartes");
            break;
        default:
            break;
    }
    
    state -> setText(str);
}


