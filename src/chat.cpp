#include "../inc/chat.h"

/******************************************************************************

	Widget permettant d'afficher le contenu du chat

******************************************************************************/

Chat::Chat(){
 
    layout = new QGridLayout;
    layout -> setContentsMargins(10,10,10,10);


    label = new QLabel("yi");

    layout -> addWidget(label);

    setLayout(layout);
}


Chat::~Chat(){

    delete label;
    delete layout;
}

