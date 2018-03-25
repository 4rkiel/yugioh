#include "../inc/history.h"

/******************************************************************************

	Widget permettant d'afficher le contenu du chat

******************************************************************************/

History::History(){
 
    layout = new QGridLayout;
    layout -> setContentsMargins(10,10,10,10);


    label = new QLabel("yu");

    layout -> addWidget(label);

    setLayout(layout);
}


History::~History(){

    delete label;
    delete layout;
}

