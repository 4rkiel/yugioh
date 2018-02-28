#include "../inc/generique.h"


Generique::Generique () {

    layout = new QGridLayout;
 
    layout -> setSpacing(0);
    layout -> setMargin(0);


    // Logo

    logoBox = new QWidget;
    logoBox -> setObjectName("logoBox");
    logoBox -> setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    logoLayout = new QGridLayout;
    logoLayout -> setAlignment(Qt::AlignCenter);
    
        img = new QLabel;
        img -> setObjectName("logo");
        logoLayout -> addWidget(img);

        title = new QLabel;
        title -> setObjectName("title");
        title -> setText("Yu-Gi-Oh");
        logoLayout -> addWidget(title);

        subTitle = new QLabel;
        subTitle -> setText("Gotta catch 'em all");
        logoLayout -> addWidget(subTitle);

    logoBox -> setLayout(logoLayout);
    
    layout -> addWidget(logoBox, 0, 0, 5, 5);



    // Progress
   
    geneBox = new QWidget;
    geneBox -> setObjectName("geneBox");
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



    geneBox -> setLayout(box);
    
    layout -> addWidget(geneBox, 5, 0, 1, 5);
    
    setLayout(layout);
}

    
Generique::~Generique (){

    delete title;
    delete subTitle;
    delete img;
    delete logoLayout;
    delete logoBox;

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
            str = QString::fromUtf8("Synchronisation de l'heure du D-D-D-D-D-Duel");
            break;
        case 3:
            str = QString::fromUtf8("Configuration de l'âme des cartes");
            break;
        default:
            break;
    }
    
    state -> setText(str);
}


