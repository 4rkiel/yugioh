#include "../inc/chat.h"

/******************************************************************************

	Widget permettant d'afficher le contenu du chat

******************************************************************************/

Chat::Chat(){

    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
    QSizePolicy sp = sizePolicy();
    sp.setRetainSizeWhenHidden(true);
    setSizePolicy(sp);

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

