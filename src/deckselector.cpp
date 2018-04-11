#include "../inc/deckselector.h"

DeckSelector::DeckSelector()
{
    // POUQUOI PAS D IMAGE ?

    mainLayout = new QVBoxLayout;
    mainLayout -> setContentsMargins(0,0,0,0);
    mainLayout -> setSpacing(0);
    mainLayout -> setMargin(0);

    tabDeckButton.reserve(NBR_DECK);
    tabSep.reserve(NBR_DECK-1);


    Parser parserAllMighty;
    int i = 0;

    foreach (QString str, deckList)
    {
        qDebug() << "traitement du deck: "+str;

        std::vector<Carte*> *deckCourant = parserAllMighty.deck(deckRep + str);


        // deck button

        QString image = imgPreviewDeck(deckCourant);

        tabDeckButton.push_back(new DeckPreview(str, image));
        tabSep.push_back(new QFrame);
        tabSep[i]->setFixedHeight(1);
        tabSep[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        //connect(choice, SIGNAL(clicked()), this, SLOT(emitMaster()));
        qDebug() << "success";
        mainLayout->addWidget(tabDeckButton[i]);
        mainLayout->addWidget(tabSep[i]);

        connect(tabDeckButton[i], SIGNAL(clicked(QString)), this, SLOT(openDeck(QString)));

        i++;
    }

    mainLayout->addStretch();

    setLayout(mainLayout);
}


// TODO probleme si vecteur vide: appli crash
QString DeckSelector::imgPreviewDeck(std::vector<Carte*> *deck)
{
    qDebug() << deck->at(0)->image;
    return deck->at(0)->image;
}

void DeckSelector::openDeck(QString nomDeck)
{
    deckEdit *edit = new deckEdit(leParser.all_cards);
    edit->show();
}