#include "../inc/flatExpButt.h"

/******************************************************************************

	Réimplémentation des QPushButton

	Permet d'avoir un bouton avec ombre et icone/texte

******************************************************************************/

FlatExpButt::FlatExpButt (QString icoStr, QString textStr){
 
    // Button content
 
    layout = new QGridLayout;
	layout -> setSizeConstraint(QLayout::SetMinimumSize);
    
    ico = nullptr;
    txt = nullptr;

    if (icoStr != ""){
        ico = new QLabel;
        ico -> setMargin(10);
        ico -> setFont(QFont("Font Awesome 5 Free", 12));
        ico -> setText(icoStr);

        if (textStr == ""){

            layout -> setColumnStretch(0,1);
            layout -> addWidget(ico, 1,1,1,1);
            layout -> setColumnStretch(2,1);
        } else {
            layout -> addWidget(ico, 1,0,1,1 );
        }
    }

    if (textStr != ""){
        txt = new QLabel;
        txt -> setText(textStr);
            
        
        if (icoStr != ""){
            layout -> setColumnStretch(1,1);
            layout -> addWidget(txt, 1, 2, 1,1);
            layout -> setColumnStretch(3,2);
        } else {
            layout -> setColumnStretch(0,1);
            layout -> addWidget(txt, 1,2,1,1);
            layout -> setColumnStretch(2,1);
        }
    }


    layout -> setRowStretch(0,1);
    layout -> setRowStretch(2,1);
	setLayout(layout);
}



FlatExpButt::~FlatExpButt (){

    if (ico != nullptr){
        delete ico;
    }

    if (txt != nullptr){
        delete txt;
    }

    delete layout;
//	delete wid;
//	delete vlay;
}
