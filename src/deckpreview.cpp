#include "../inc/deckpreview.h"

DeckPreview::DeckPreview(QString deck, QString img){

    nomDeck = deck;

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    setFlat(true);

    layout = new QGridLayout;
    layout -> setSizeConstraint(QLayout::SetMinimumSize);

        pic = new QLabel;
        pic -> setMinimumWidth(50);
        pic -> setMaximumWidth(50);
        pic -> setMinimumHeight(50);
        pic -> setMaximumHeight(50);

        pic -> setStyleSheet("border-image: url("+img+")");
        layout -> addWidget(pic, 0,0,1,1);


        deck.chop(5);
        name = new QLabel;
        name -> setText(deck);


        layout -> setColumnStretch(1,1);
        layout -> addWidget(name, 0,2,1,1);
        layout -> setColumnStretch(3,1);


        shortcut = new QShortcut(QKeySequence("Return"), this);
        shortcut->setContext(Qt::WidgetWithChildrenShortcut);
        connect(shortcut,SIGNAL(activated()),this,SLOT(doClick()));


    setLayout(layout);

    setToolTip(tr("Editer le deck ")+deck);

    connect(this, SIGNAL(clicked()), this, SLOT(doClick()));
}

DeckPreview::~DeckPreview(){

    delete name;
    delete pic;

    delete layout;
    delete shortcut;
}



void DeckPreview::doClick(){
    
    emit isClick(name->text());    
}
