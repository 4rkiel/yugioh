#include "../inc/chat.h"

/******************************************************************************

	Widget permettant d'afficher le contenu du chat

******************************************************************************/

Chat::Chat(){

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSizePolicy sp = sizePolicy();
    sp.setRetainSizeWhenHidden(true);
    setSizePolicy(sp);

    layout = new QGridLayout;
    layout -> setContentsMargins(10,10,10,10);


        title = new QLabel;
        title -> setText(tr("Chat"));

    layout -> addWidget(title, 0, 0, 1, 4);

        label = new QLabel;


    layout -> addWidget(label, 1, 0, 3, 4);


        input = new QLineEdit;

    layout -> addWidget(input, 4, 0, 1, 3);

        
        send = new FlatButt("\uf1d8","");

    layout -> addWidget(send, 4, 3, 1, 1);



    setLayout(layout);
}


Chat::~Chat(){

    delete title;
    delete label;
    delete input;
    delete send;
    delete layout;
}


void Chat::addText(QString str){

    QString time = QTime::currentTime().toString("hh:mm");
    QString tmp = label -> text();
    tmp.append(time + " : " + str + "\n\n");
    label -> setText(tmp);

}
