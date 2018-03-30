#include "../inc/flatButt.h"

/******************************************************************************

    Réimplémentation des QPushButton

	Permet d'avoir un bouton avec ombre et icone/texte

******************************************************************************/

FlatButt::FlatButt (QString icoStr, QString textStr){
 
    // Button content

    layout = new QHBoxLayout;

    ico = nullptr;
    txt = nullptr;

    if (icoStr != ""){
        ico = new QLabel;
        ico -> setMargin(10);
        ico -> setFont(QFont("Font Awesome 5 Free", 12));
        ico -> setText(icoStr);
   
        if (textStr == ""){
            setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

            layout -> addStretch();
            layout -> addWidget(ico, 0, Qt::AlignCenter);
            layout -> addStretch();
        } else {
            layout -> addWidget(ico, 0, Qt::AlignLeft);
        }
    }

    if (textStr != ""){
        txt = new QLabel;
        txt -> setText(textStr);

        layout -> addStretch(1);
            
        layout -> addWidget(txt, 0, Qt::AlignRight);
        
        if (icoStr != ""){
            layout -> addStretch(2);
        } else {
            layout -> addStretch(1);
        }
    }

	setLayout(layout);
}



FlatButt::~FlatButt (){

    if (ico != nullptr){
        delete ico;
    }

    if (txt != nullptr){
        delete txt;
    }

    delete layout;
}

