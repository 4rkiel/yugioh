#include "../inc/stats.h"

/******************************************************************************

	Widget permettant d'afficher le contenu du chat

******************************************************************************/

Stats::Stats(){

    state = 0;

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSizePolicy sp = sizePolicy();
    sp.setRetainSizeWhenHidden(true);
    setSizePolicy(sp);
    
    layout = new QGridLayout;
    layout -> setContentsMargins(10,10,10,10);

        title = new QLabel;
        title -> setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        title -> setText(tr("Informations"));

    layout -> addWidget(title, 0, 0, 1, 3);

        tour = new QLabel;

    layout -> addWidget(tour, 1, 0, 1, 3);

        phase = new QLabel;
        phase -> setText(tr("Phase : "));

        ph1 = tr("Phase de Pioche");
        ph2 = tr("Phase Principale");
        ph3 = tr("Phase de Combat");
        ph4 = tr("Phase de Fin");


    layout -> addWidget(phase, 2, 0, 1, 3);

        txtPhase = new QLabel;

    layout -> addWidget(txtPhase, 3, 0, 1, 3);
    
    
        progress = new QProgressBar;
        progress -> setRange(0,200);
        progress -> setOrientation(Qt::Horizontal);

    layout -> addWidget(progress, 4, 0, 1, 3);




    setLayout(layout);
}


Stats::~Stats(){

    delete progress;
    delete tour;
    delete phase;
    delete txtPhase;
    delete title;
    delete layout;
}


void Stats::setTour (int x){
    tour -> setText("Tour : " + QString::number(x));
}


void Stats::setPhase (int x){

    switch(x){
        
        case 1:
            txtPhase -> setText(ph1);
            break;

        case 2:

            txtPhase -> setText(ph2);
            break;

        case 3:

            txtPhase -> setText(ph3);
            break;

        case 4:

            txtPhase -> setText(ph4);
            break;
    }
}


void Stats::resetProgress (){

    state = 0;
    progress -> reset();
}


void Stats::incProgress (){

    state = (state + 1) % 200;
    progress -> setValue(state);
}
