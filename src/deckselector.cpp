#include "../inc/deckselector.h"

DeckSelector::DeckSelector(){

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setObjectName("DeckSelector");

    mainLayout = new QGridLayout;
    mainLayout -> setContentsMargins(0,0,0,0);
    mainLayout -> setSpacing(0);
    mainLayout -> setMargin(0);

    
    tabDeckButton.reserve(NBR_DECK);
    tabSep.reserve(NBR_DECK-1);


    Parser parserAllMighty;
    int i = 0;
    int last = deckList.size();

    foreach (QString str, deckList){

        std::vector<Carte*> * deckCourant = parserAllMighty.deck(deckRep + str);

        // deck button

        QString image = imgPreviewDeck(deckCourant);

        tabRadio.push_back(new QRadioButton);

        tabDeckButton.push_back(new DeckPreview(str, image));
        
        mainLayout->addWidget(tabDeckButton[i],i*2,0,1,1);
        mainLayout->addWidget(tabRadio[i],i*2,1,1,1);
       
        if (i != last){
            
            tabSep.push_back(new QFrame);
            tabSep[i]->setFixedHeight(1);
        
            mainLayout->addWidget(tabSep[i], (i*2)+1,0,1,2);
        }

        connect(tabDeckButton[i], SIGNAL(isClick(QString)), this, SLOT(openDeck(QString)));

        i++;
    }

    setLayout(mainLayout);
}


DeckSelector::~DeckSelector(){
    
    int i = deckList.size() - 1;
    foreach (QString str, deckList){
  
        delete tabRadio[i];
        delete tabSep[i];
        delete tabDeckButton[i];

        i --;
    }
        
    delete mainLayout;
}



// TODO probleme si vecteur vide: appli crash

QString DeckSelector::imgPreviewDeck(std::vector<Carte*> *deck){

    return deck->at(0)->image;
}

void DeckSelector::openDeck(QString nomDeck){

    deckEdit *edit = new deckEdit(leParser.all_cards);
    
    edit->show();
}

