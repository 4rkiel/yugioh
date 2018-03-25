#include "../inc/stats.h"

/******************************************************************************

	Widget permettant d'afficher le contenu du chat

******************************************************************************/

Stats::Stats(){
 
    layout = new QGridLayout;
    layout -> setContentsMargins(10,10,10,10);


    label = new QLabel("yo");

    layout -> addWidget(label);

    setLayout(layout);
}


Stats::~Stats(){

    delete label;
    delete layout;
}

