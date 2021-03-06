#include "../inc/stats.h"

#include <iostream>

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
    layout -> setContentsMargins(0,0,0,0);

        title = new QLabel;
		title -> setObjectName("sideTitle");
        title -> setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        title -> setText(tr("Informations"));

    layout -> addWidget(title, 0, 0, 1, 4);

        tour = new QLabel;

    layout -> addWidget(tour, 1, 0, 1, 4);

        phase = new QLabel;
        phase -> setText(tr("Phase : "));

        ph1 = tr("Phase de Pioche");
        ph2 = tr("Phase Principale");
        ph3 = tr("Phase de Combat");
        ph4 = tr("Phase de Fin");


    layout -> addWidget(phase, 2, 0, 1, 4);

        txtPhase = new QLabel;

    layout -> addWidget(txtPhase, 3, 0, 1, 4);
    
    
        progress = new QProgressBar;
        progress -> setMinimum(0);
        progress -> setMaximum(200);
        progress -> setOrientation(Qt::Horizontal);
        progress -> setTextVisible(false);

    layout -> addWidget(progress, 4, 0, 1, 4);




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
    progress -> repaint();
}
