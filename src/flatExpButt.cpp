#include "../inc/flatExpButt.h"

/******************************************************************************

	Réimplémentation des QPushButton

	Permet d'avoir un bouton avec ombre et icone/texte

******************************************************************************/

FlatExpButt::FlatExpButt (QString icoStr, QString textStr){
 
    // Button content
	
	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
	vlay = new QVBoxLayout;
	vlay -> setSizeConstraint(QLayout::SetMinimumSize);

	wid = new QWidget;
	wid -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    layout = new QHBoxLayout;
	layout -> setSizeConstraint(QLayout::SetMinimumSize);

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

    wid -> setLayout(layout);
	
	vlay -> addStretch();
	vlay -> addWidget(wid);
	vlay -> addStretch();

	setLayout(vlay);
}



FlatExpButt::~FlatExpButt (){

    if (ico != nullptr){
        delete ico;
    }

    if (txt != nullptr){
        delete txt;
    }

    delete layout;
	delete wid;
	delete vlay;
}

