#include "../inc/stats.h"

/******************************************************************************

	Widget permettant d'afficher le contenu du chat

******************************************************************************/

Stats::Stats(){
 
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
    QSizePolicy sp = sizePolicy();
    sp.setRetainSizeWhenHidden(true);
    setSizePolicy(sp);
    
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

