#include "../inc/deckselector.h"
#include "../inc/buildtab.h"

DeckSelector::DeckSelector(QObject* parent){

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
        tabRadio[i] -> setObjectName("selectRad");
        tabRadio[i] -> setToolTip(tr("Utiliser ce deck en duel"));

        tabDeckButton.push_back(new DeckPreview(str, image));
        tabDeckButton[i] -> setObjectName("selectButt");
        
        mainLayout->addWidget(tabDeckButton[i],i*2,0,1,1);
        mainLayout->addWidget(tabRadio[i],i*2,1,1,1);
       
        if (i != last-1){
            
            tabSep.push_back(new QFrame);
            tabSep[i]->setFixedHeight(1);
            tabSep[i]->setObjectName("selectSep");
        
            mainLayout->addWidget(tabSep[i], (i*2)+1,0,1,2);
        }

        connect(tabDeckButton[i], SIGNAL(isClick(QString)), this, SLOT(openDeck(QString)));

        i++;
    }

    BuildTab* par= static_cast<BuildTab*>(parent);
    QSpacerItem * spacerButt = new QSpacerItem(2,1,
            QSizePolicy::Preferred,QSizePolicy::Expanding);
    mainLayout -> addItem(spacerButt, last*2, 0);
    connect(par,SIGNAL(nousFocus()),this,SLOT(getsFocus()));
    connect(par,SIGNAL(focusDeck()),this,SLOT(abandonFocus()));

    setLayout(mainLayout);
}


DeckSelector::~DeckSelector(){
    
    int last = deckList.size() - 1;
    int i = last;

    foreach (QString str, deckList){
 
        if (i != last){
            delete tabSep[i];
        }

        delete tabRadio[i];
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

    emit popDeck(nomDeck);
}

/* Focus */
void DeckSelector::abandonFocus(){
    QRadioButton* temp;
    DeckPreview* temp2;
    int i=0;
    foreach (QString str, deckList){
        temp=tabRadio[i];
        temp2=tabDeckButton[i];
        temp->setFocusPolicy(Qt::NoFocus);
        temp2->setFocusPolicy(Qt::NoFocus);
        i++;
    }
}

void DeckSelector::getsFocus(){
    QRadioButton* temp;
    DeckPreview* temp2;
    int i=0;
    foreach (QString str, deckList){
        temp=tabRadio[i];
        temp2=tabDeckButton[i];
        temp->setFocusPolicy(Qt::StrongFocus);
        temp2->setFocusPolicy(Qt::StrongFocus);
        i++;
    }
}
