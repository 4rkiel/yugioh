#include "../inc/deckedit.h"

#include <inc/deckedit.h>
#include <inc/deckedit.h>


deckEdit::deckEdit(std::vector<Carte *> *allCard, QString nomDuDeck){

    allCards = allCard;
    deckName = nomDuDeck;

    setObjectName("deckEdit");
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    selectDeck = new Combo;
    choixGenre = new Combo;
    choixSousGenre  = new Combo;
    choixAttribut = new Combo;
    choixType = new Combo;

    newDeck = new QLineEdit;
    textSearch = new QLineEdit;

    spinAtk = new QSpinBox;
    spinDef = new QSpinBox;
    spinNiveau = new QSpinBox;

    deck.reserve(NBR_CARTE_DECK_VISU);
    tabCardVisu.reserve(NBR_CARTE_DECK_VISU);
    undoList.reserve(TAILLE_UNDO);
    redoList.reserve(TAILLE_UNDO);

    for( std::vector<Carte*> deckTmp : undoList)
    {
        deckTmp.reserve(TAILLE_UNDO);
    }

    for( std::vector<Carte*> deckTmp : redoList)
    {
        deckTmp.reserve(TAILLE_UNDO);
    }

    for(int i=0; i<NBR_CARTE_DECK_VISU; i++)
    {
        tabCardVisu.push_back(new QPushButton);
        tabCardVisu[i]->setDefault(true);

        QSizePolicy sp_retain = tabCardVisu[i]->sizePolicy();
        sp_retain.setRetainSizeWhenHidden(true);
        sp_retain.setHorizontalPolicy(QSizePolicy::Minimum);
        sp_retain.setVerticalPolicy(QSizePolicy::Minimum);
        tabCardVisu[i]->setSizePolicy(sp_retain);
        tabCardVisu[i]->setVisible(false);

        QObject::connect(tabCardVisu[i], SIGNAL(clicked()),
                         this, SLOT(rmvCard2Deck()));

    }

    for(int i=0; i<NBR_CARTE_EXTRA_DECK; i++)
    {
        tabExtraDeck.push_back(new QPushButton);
        tabExtraDeck[i]->setDefault(true);

        QSizePolicy sp_retain = tabCardVisu[i]->sizePolicy();
        sp_retain.setRetainSizeWhenHidden(true);
        sp_retain.setHorizontalPolicy(QSizePolicy::Minimum);
        sp_retain.setVerticalPolicy(QSizePolicy::Minimum);
        tabExtraDeck[i]->setSizePolicy(sp_retain);
        tabExtraDeck[i]->setVisible(false);

        QObject::connect(tabExtraDeck[i], SIGNAL(clicked()),
                         this, SLOT(rmvCard2Deck()));
    }

    choixGenre->addItems(genreList);
    slotAttribut();
    choixSousGenre->addItems(sousGenreList);

    mainLayout = new QHBoxLayout;
    mainL1 = new QVBoxLayout;
    mainL1->setSpacing(0);

    mainL1->setMargin(0);
    mainL2 = new QVBoxLayout;


        // ... selecteur / creation de Deck ....................................

        editCreate = new QFrame;
        editCreate->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        editCreate->setStyleSheet("border: 1px solid blue");
        mainL1->addWidget(editCreate);
        editCreate->setStyleSheet("background-color: #ECEFF1");
        editCreateLayout = new QVBoxLayout;
        editCreate->setLayout(editCreateLayout);


            // ... selecteur de Deck ...........................................

            QStringList deckList = QDir(deckRep).entryList({"*.deck"});


            if (deckName != "")
                foreach (QString str, deckList)
                {
                    if(str == deckName+".deck")
                    {
                        Parser parse;
                        std::vector<Carte*> *leDeckParse = parse.deck(deckRep + str);

                        for(Carte* laCarteCourante : *leDeckParse)
                        {
                            switch(laCarteCourante->genre)
                            {
                                case 0:
                                    if(laCarteCourante->sous_type == 2) // carte fusion
                                    {
                                        extraDeck.push_back(laCarteCourante);
                                        indiceCarteExtraDeck++;
                                    }
                                    else
                                    {
                                        deck.push_back(laCarteCourante);
                                        nbrCarteMonstre++;
                                        indiceCarteDeck++;
                                    }
                                break;

                                case 1:
                                    deck.push_back(laCarteCourante);
                                    nbrCarteMagie++;
                                    indiceCarteDeck++;
                                break;

                                case 2:
                                    deck.push_back(laCarteCourante);
                                    nbrCartePiege++;
                                    indiceCarteDeck++;
                            }
                        }
                    }
                }



            // ... Rename a deck ...............................................


            frameNomDeck = new QFrame;
            frameNomDeck->setObjectName("yolo");
            frameNomDeck->setSizePolicy(QSizePolicy::Maximum,
                                        QSizePolicy::Maximum);
            frameNomDeck->setStyleSheet("#yolo {border-radius: 3px;\
                                         background-color: blue}");



                nomLayout = new QGridLayout;

                nomDeck = new QLineEdit;

                if(deckName != "")
                    nomDeck->setText(deckName);
                else
                    nomDeck->setPlaceholderText(tr("Nom du Deck"));
                nomDeck->setSizePolicy(QSizePolicy::Minimum,
                                       QSizePolicy::Maximum);



                // ... Supprimer ...............................................


                    supprDeck = new DarkButt("\uf2ed", "");
                    supprDeck -> setToolTip(tr("Supprimer le deck"));
                    supprDeck->setSizePolicy(QSizePolicy::Maximum,
                                             QSizePolicy::Maximum);
                    nomLayout->addWidget(supprDeck, 0, 1, 1, 1);


                // ... "+" .....................................................


                    plusBut = new DarkButt("\uf105", "");
                    plusBut -> setToolTip(tr("Réorganiser les cartes"));
                    plusBut->setSizePolicy(QSizePolicy::Maximum,
                                             QSizePolicy::Maximum);
                    nomLayout->addWidget(plusBut, 0, 2, 1, 1);


                nomLayout->addWidget(nomDeck, 0, 0, 1, 1);

            frameNomDeck->setLayout(nomLayout);

            // ... boutton caché ...............................................


            stealBut = new QFrame;
            stealBut->setObjectName("cachay");
            stealBut->setSizePolicy(QSizePolicy::Minimum,
                                        QSizePolicy::Maximum);
            stealBut->setContentsMargins(0,0,0,0);
            stealBut->setVisible(false);
            stealBut->setStyleSheet("#cachay {border-radius: 3px;\
                                         background-color: red}");



                cachayLayout = new QGridLayout;
                cachayLayout->setMargin(0);



                // ... Melanger ................................................


                    shuffleDeck = new DarkButt("", tr("Mélanger"));
                    shuffleDeck->setToolTip(tr("Mélanger le Deck"));
                    shuffleDeck->setSizePolicy(QSizePolicy::Minimum,
                                             QSizePolicy::Minimum);
                    cachayLayout->addWidget(shuffleDeck, 0, 1, 1, 1);


                // ... Trier ...................................................


                    sortDeck = new DarkButt("", tr("Trier"));
                    sortDeck->setToolTip(tr("Trier le Deck"));
                    sortDeck->setSizePolicy(QSizePolicy::Minimum,
                                             QSizePolicy::Minimum);
                    cachayLayout->addWidget(sortDeck, 0, 2, 1, 1);


                // ... Effacer .................................................


                    eraseDeck = new DarkButt("", tr("Effacer"));
                    eraseDeck->setToolTip(tr("Effacer le contenu du Deck"));
                    eraseDeck->setSizePolicy(QSizePolicy::Minimum,
                                             QSizePolicy::Minimum);
                    cachayLayout->addWidget(eraseDeck, 0, 3, 1, 1);


                // ... Undo ....................................................


                    undo = new DarkButt("\uf0e2", "");
                    undo->setToolTip(tr("Annuler la dernière action"));

                    cachayLayout->addWidget(undo, 0, 4, 1, 1);



                // ... Redo ....................................................


                    redo = new DarkButt("\uf01e", "");
                    redo->setToolTip(tr("Refaire la dernière action annulée"));

                    cachayLayout->addWidget(redo, 0, 5, 1, 1);


            stealBut->setLayout(cachayLayout);

        nomLayout->addWidget(stealBut, 0, 3, 1, 1);
        editCreateLayout->addWidget(frameNomDeck);






        // ... Compteur de cartes / visualisateur de Deck ......................

        deckVisuLayout = new QVBoxLayout;
        mainL1->addLayout(deckVisuLayout);


            // ... compteur de cartes ..........................................

            cardInfo = new QFrame;
            cardInfo->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
            cardInfo->setObjectName("frameVisu");
            cardInfo->setStyleSheet("#frameVisu{border: 1px solid green}");

            layoutInfo = new QHBoxLayout;
            cardInfo->setLayout(layoutInfo);

                deckLabel = new QLabel();
                deckLabel->setText(tr("Main Deck vide"));

                infoMonstreLabel = new QLabel;
                infoMagieLabel = new QLabel;
                infoPiegeLabel = new QLabel;
                infoFusionLabel = new QLabel;
                infoMonstreLabel->setText(tr("Monstre: ") +
                                          QString::number(nbrCarteMonstre));
                infoMagieLabel->setText(tr("Magie: ") +
                                        QString::number(nbrCarteMagie));
                infoPiegeLabel->setText(tr("Piège: ") +
                                        QString::number(nbrCartePiege));
                infoFusionLabel->setText(tr("Extra Deck vide"));

                layoutInfo->addWidget(deckLabel);
                layoutInfo->addWidget(infoMonstreLabel);
                layoutInfo->addWidget(infoMagieLabel);
                layoutInfo->addWidget(infoPiegeLabel);
                layoutInfo->addWidget(infoFusionLabel);



            // ... visualiseur de Deck .........................................

            deckVisu = new QFrame;
            deckVisu->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            deckVisu->setObjectName("frameVisu");
            deckVisu->setStyleSheet("#frameVisu{border: 1px solid green}");

            layoutCard = new QGridLayout;
            deckVisu->setLayout(layoutCard);
            int limit = NBR_CARTE_DECK_VISU/10;
            for(int i=0; i<limit; i++)
            {
                for(int y=0; y<10; y++)
                {
                    layoutCard->addWidget(tabCardVisu[i*10+y], i, y, 1, 1);
                }
            }


            // ... visualiseur d'extra Deck ....................................


            for(int i=0; i<NBR_CARTE_EXTRA_DECK; i++)
            {
                    layoutCard->addWidget(tabExtraDeck[i], limit, i, 1, 1);
            }


        deckVisuLayout->addWidget(cardInfo);
        deckVisuLayout->addWidget(deckVisu);


        // ... recherche de cartes .............................................

        cardFilter = new QFrame;
        cardFilter->setSizePolicy(QSizePolicy::Minimum,
                                  QSizePolicy::Maximum);
        cardFilter->setObjectName("filtreur");
        cardFilter->setStyleSheet("#filtreur{background-color: green;}");
        mainL2->addWidget(cardFilter);
        layoutRechercheCarte = new QGridLayout;



            // ... Recherche pas Nom ...........................................

            textSearch->setPlaceholderText(tr("Nom recherché"));
            textSearch->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            layoutRechercheCarte->addWidget(textSearch, 0, 0, 1, 3);


            // ... Annuler recherche ...........................................

            butClearSearch = new DarkButt("", "clear");
            butClearSearch->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            butClearSearch->setToolTip(tr("Effacer la recherche"));

            layoutRechercheCarte->addWidget(butClearSearch, 0, 3, 1, 1);


            // ... "+" de filtre ...............................................

            plusFiltrBut = new DarkButt("\uf078", "");
            plusFiltrBut->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
            plusFiltrBut->setToolTip(tr("Tries avancés sur les Cartes"));

            layoutRechercheCarte->addWidget(plusFiltrBut, 0, 4, 1, 1);



            // ... recherche par propriétés ....................................

            cardFilterAdv = new QFrame;

            cardFilterAdv->setSizePolicy(QSizePolicy::Minimum,
                                      QSizePolicy::Maximum);
            sp_retain_cachay = choixSousGenre->sizePolicy();
            sp_retain_cachay.setRetainSizeWhenHidden(false);
            cardFilterAdv->setSizePolicy(sp_retain_cachay);
            cardFilterAdv->setVisible(false);
            cardFilterAdv->setObjectName("filtreurAdv");
            cardFilterAdv->setStyleSheet("#filtreurAdv{background-color: red;}");
            layoutRechercheCarte->addWidget(cardFilterAdv, 1, 0, 2, 5);
            layoutRechercheCarteAdv = new QVBoxLayout;
            cardFilterAdv->setLayout(layoutRechercheCarteAdv);

                // ... Genre / Sous-genre ......................................

                genreColonne = new QHBoxLayout;

                genreLabel = new QLabel(tr("Genre:   "));
                genreLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

                sp_retain_choixGenre = choixSousGenre->sizePolicy();
                sp_retain_choixGenre.setRetainSizeWhenHidden(false);
                choixSousGenre->setSizePolicy(sp_retain_choixGenre);
                choixSousGenre->setVisible(false);

                genreColonne->addWidget(genreLabel);
                genreColonne->addWidget(choixGenre);
                genreColonne->addWidget(choixSousGenre);



                // ... Attribut ................................................

                attrLayout = new QHBoxLayout;

                attrLabel = new QLabel(tr("Attribut: "));
                attrLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

                attrLayout->addWidget(attrLabel);
                attrLayout->addWidget(choixAttribut);




            layoutRechercheCarteAdv->addLayout(genreColonne);
            layoutRechercheCarteAdv->addLayout(attrLayout);


        cardFilter->setLayout(layoutRechercheCarte);

        // ... scroll la liste des cartes recherchées ..........................

        deckScroll = new QScrollArea;
        deckScroll -> setFrameShape(QFrame::NoFrame);
        deckScroll -> setWidgetResizable(true);
        deckScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        deckScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        deckScroll -> setFocusPolicy(Qt::NoFocus);
        deckScroll->setBackgroundRole(QPalette::Light);
        deckScroll->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

            //Parser *parser = new Parser;

            cardList = new CardListPreview(allCard);
            cardList->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

            for(CardPreview *cardPreviewCourante : (*cardList->cardPreviewList))
            {
                QObject::connect(cardPreviewCourante, SIGNAL(clicked(Carte*)),
                                 this, SLOT(addCard2Deck(Carte*)));
            }

            deckScroll->setWidget(cardList);

        mainL2->addWidget(deckScroll);


    mainLayout->addLayout(mainL1);
    mainLayout->addLayout(mainL2);
    setLayout(mainLayout);

    connect(choixGenre, SIGNAL(currentIndexChanged(int)),
            this,SLOT(slotAttribut()));
    connect(butClearSearch, SIGNAL(clicked()), this, SLOT(clearSearch()));

    connect(nomDeck, SIGNAL(returnPressed()),
            this, SLOT(sauvegarderDiscretionMax()));
    connect(plusBut, SIGNAL(clicked()), this, SLOT(plus2But()));
    connect(eraseDeck, SIGNAL(clicked()), this, SLOT(effacerDeck()));
    connect(shuffleDeck, SIGNAL(clicked()), this, SLOT(melangerDeck()));
    connect(sortDeck, SIGNAL(clicked()), this, SLOT(trierDeck()));
    connect(supprDeck, SIGNAL(clicked()), this, SLOT(obliterationDuDeck()));

    shortcut = new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_Z),this);
    shortcutRedo = new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_Shift+Qt::Key_Z),
                                 this);
    shortcutRedo2 = new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_R),this);
    connect(shortcut,SIGNAL(activated()),this,SLOT(slotUndo()));
    // TODO redo avec shift ne marche pas

    connect(shortcutRedo,SIGNAL(activated()),this,SLOT(slotRedo()));
    connect(shortcutRedo2,SIGNAL(activated()),this,SLOT(slotRedo()));
    connect(undo, SIGNAL(clicked()), this, SLOT(slotUndo()));
    connect(redo, SIGNAL(clicked()), this, SLOT(slotRedo()));

    connect(textSearch, SIGNAL(textEdited(QString)),
            this, SLOT(updPreview()));
    connect(choixGenre, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updPreview()));
    connect(choixSousGenre, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updPreview()));
    connect(choixAttribut, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updPreview()));
    connect(plusFiltrBut, SIGNAL(clicked()),
            this, SLOT(toujoursPlus2But()));

    updateDeckVisu();
    updateExtraDeckVisu();
}

void deckEdit::updateDeckVisu()
{
    int i=0;
    for(; i<indiceCarteDeck; i++)
    {
        tabCardVisu[i]->setStyleSheet("border-image: url("
                                      + deck.at(i)->image + ");"
                                      "margin: 1px ;border: 1px solid black");
        tabCardVisu[i]->setVisible(true);
    }
    for(; i<NBR_CARTE_DECK_VISU; i++)
    {
        tabCardVisu[i]->setVisible(false);
    }

    if(!indiceCarteDeck)
        deckLabel->setText(tr("Main Deck vide"));
    else
    deckLabel->setText(tr("Main Deck: ") +
                       QString::number(indiceCarteDeck));

    infoMonstreLabel->setText(tr("Monstre: ") +
                              QString::number(nbrCarteMonstre));
    infoMagieLabel->setText(tr("Magie: ") + QString::number(nbrCarteMagie));
    infoPiegeLabel->setText(tr("Piège: ") + QString::number(nbrCartePiege));
}

void deckEdit::updateDeckVisuLastCard()
{
    tabCardVisu[indiceCarteDeck]->setStyleSheet("border-image: url(" +
                                                deck.at(indiceCarteDeck)->image
                                                + ");margin: 1px ;"
                                                  "border: 1px solid black");
    tabCardVisu[indiceCarteDeck]->setVisible(true);

    deckLabel->setText(tr("Main Deck: ") +
                       QString::number(indiceCarteDeck+1));

    infoMonstreLabel->setText(tr("Monstre: ")
                              + QString::number(nbrCarteMonstre));
    infoMagieLabel->setText(tr("Magie: ") + QString::number(nbrCarteMagie));
    infoPiegeLabel->setText(tr("Piège: ") + QString::number(nbrCartePiege));
}

void deckEdit::updateExtraDeckVisu()
{
    int i=0;
    for(; i<indiceCarteExtraDeck; i++)
    {
        tabExtraDeck[i]->setStyleSheet("border-image: url("
                                       + extraDeck.at(i)->image + ");"
                                       "margin: 1px ;border: 1px solid black");
        tabExtraDeck[i]->setVisible(true);
    }
    for(; i<NBR_CARTE_EXTRA_DECK; i++)
    {
        tabExtraDeck[i]->setVisible(false);
    }

    if(!indiceCarteExtraDeck)
        infoFusionLabel->setText(tr("Extra Deck vide"));
    else
    infoFusionLabel->setText(tr("Extra Deck: ") +
                       QString::number(indiceCarteExtraDeck));
}

void deckEdit::updateExtraDeckVisuLastCard()
{
    tabExtraDeck[indiceCarteExtraDeck]->setStyleSheet("border-image: url("
                              + extraDeck.at(indiceCarteExtraDeck)->image + ");"
                              "margin: 1px ;border: 1px solid black");
    tabExtraDeck[indiceCarteExtraDeck]->setVisible(true);

    infoFusionLabel->setText(tr("Extra Deck: ") +
                             QString::number(indiceCarteExtraDeck+1));
}


void deckEdit::addCard2Deck(Carte* carte)
{
    if(indiceCarteDeck == NBR_CARTE_DECK_VISU &&
            indiceCarteExtraDeck == NBR_CARTE_EXTRA_DECK)
        return;

    int nbrPresence = 0;
    for(Carte* c : deck)
    {
        if(carte->id == c->id)
        {
            nbrPresence++;
        }
    }
    for(Carte* c : extraDeck)
    {
        if(carte->id == c->id)
        {
            nbrPresence++;
        }
    }

    if(nbrPresence >= 3)
        return;


    redoList.clear();
    undoList.push_back(deck);
    undoList.back().insert( undoList.back().end(), extraDeck.begin(),
                            extraDeck.end());


    switch(carte->genre)
    {
        case 0:
            if(carte->sous_type == 2) // carte fusion
            {
                if(indiceCarteExtraDeck == NBR_CARTE_EXTRA_DECK)
                       return;

                extraDeck.push_back(carte);
                updateExtraDeckVisuLastCard();
                indiceCarteExtraDeck++;
                sauvegarderDiscretionMax();
                return;
            }
            if(indiceCarteDeck == NBR_CARTE_DECK_VISU)
                return;
            nbrCarteMonstre++;
        break;

        case 1:
            if(indiceCarteDeck == NBR_CARTE_DECK_VISU)
                return;
            nbrCarteMagie++;
        break;

        case 2:
            if(indiceCarteDeck == NBR_CARTE_DECK_VISU)
                return;
            nbrCartePiege++;
    }

    deck.push_back(carte);

    updateDeckVisuLastCard();

    indiceCarteDeck++;
    sauvegarderDiscretionMax();
}

void deckEdit::rmvCard2Deck()
{
    size_t pos;
    QPushButton* cardButton2Rmv = qobject_cast<QPushButton*>(sender());
    std::vector<QPushButton *>::iterator it = std::find(tabCardVisu.begin(),
                                         tabCardVisu.end(), cardButton2Rmv);

    redoList.clear();

    undoList.push_back(deck);
    undoList.back().insert( undoList.back().end(), extraDeck.begin(),
                            extraDeck.end());

    if(it != tabCardVisu.end())
    {
        pos = it - tabCardVisu.begin();

        switch(deck.at(pos)->genre)
        {
            case 0:
                nbrCarteMonstre--;
            break;

            case 1:
                nbrCarteMagie--;
            break;

            case 2:
                nbrCartePiege--;
        }

        deck.erase(deck.begin()+pos);

        indiceCarteDeck--;

        updateDeckVisu();
    }
    else
    {
        pos = std::find(tabExtraDeck.begin(), tabExtraDeck.end(),
                        cardButton2Rmv) - tabExtraDeck.begin();

        extraDeck.erase((extraDeck.begin()+pos));

        indiceCarteExtraDeck--;

        updateExtraDeckVisu();
    }
    sauvegarderDiscretionMax();
}

void deckEdit::sauvegarder()
{
    if(deck.size() != 40)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("M-Masaka !"),
                                      tr("Deck invalide: Souhaitez "
                                    "vous tout de même sauvegarder ? Vous "
                                    "pourrez éditer votre deck ultérieurement."),
                                    QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No)
          return;
    }

    if(!nomDeck->text().isEmpty())
    { // le deck à était renommé
        newDeckName = nomDeck->text();
        QFile ripFile (deckRep + deckName + QString(".deck"));
            ripFile.remove();
    }
    else
        newDeckName = deckName;

    QString file = deckRep + newDeckName + QString(".deck");
    qDebug() << "SAVE: URL FICHIER ECRITURE DECK: "+file;




    QFile *myfile = new QFile(file);

    if(!myfile->open(QFile::WriteOnly | QFile::Text))
    {// chemin  corrompue
        QMessageBox::information(this, tr("echec de la sauvegarde"),
                                 tr("Le deck ") +
                                 selectDeck->currentText()
                                 + tr(" n'a pas pu être sauvegardé."),
                                     QMessageBox::Ok);
    }

    QTextStream in(myfile);



    in << QString("#main_deck\n");

    for(Carte* carte : deck)
    {
        in << QString::number(carte->id) + QString("\n");
    }

    in << QString("#extra_deck\n");
    for(Carte* carte : extraDeck)
    {
        in << QString::number(carte->id)+ QString("\n");
    }

    myfile->close();

    QMessageBox::information(this, tr("youpi !"), tr("Le deck ") +
                             selectDeck->currentText()
                             + tr(" à était enregistré."),
                             QMessageBox::Ok);
}

void deckEdit::sauvegarderDiscretionMax()
{
    if(!nomDeck->text().isEmpty())
    { // le deck à était renommé
        newDeckName = nomDeck->text();
        QFile ripFile (deckRep + deckName + QString(".deck"));
            ripFile.remove();
    }
    else if(deck.empty() && extraDeck.empty())
    { // deck sans nom ni carte, on ne sauvegarde pas
        return;
    }
    else
    { // le deck ne porte pas de nom mais comporte des cartes
        QMessageBox::information(this, tr("echec de la sauvegarde"),
                                 tr("Veuillez donner un nom au deck"),
                                     QMessageBox::Ok);
        return;
    }

    QString file = deckRep + newDeckName + QString(".deck");
    qDebug() << "SAVE: URL FICHIER ECRITURE DECK: "+file;




    QFile *myfile = new QFile(file);

    if(!myfile->open(QFile::WriteOnly | QFile::Text))
    {// chemin  corrompue
        QMessageBox::information(this, tr("echec de la sauvegarde"),
                                 tr("Le deck ") +
                                 selectDeck->currentText()
                                 + tr(" n'a pas pu être sauvegardé."),
                                     QMessageBox::Ok);
    }

    QTextStream in(myfile);



    in << QString("#main_deck\n");

    for(Carte* carte : deck)
    {
        in << QString::number(carte->id) + QString("\n");
    }

    in << QString("#extra_deck\n");
    for(Carte* carte : extraDeck)
    {
        in << QString::number(carte->id) + QString("\n");
    }

    myfile->close();
    deckName = newDeckName;
}

void deckEdit::creer()
{
    std::vector<QString> list;
    for(auto i=0; i<selectDeck->count(); i++)
    {
        list.push_back(selectDeck->itemText(i));
    }

    if(std::find(list.begin(), list.end(), newDeck->text()) != list.end())
    { // deck already exist
        QMessageBox::information(this, tr("M-Masaka !"),
                                 tr("Impossible de créer le deck \"")
                                + newDeck->text()
                                 +tr("\": le deck existe déjà."),
                                    QMessageBox::Ok);
          return;
    }

    QFile myfile(deckRep + newDeck->text() + QString(".deck"));
    if(!myfile.open(QIODevice::WriteOnly | QIODevice::Append))
    {// chemin  corrompue
        QMessageBox::information(this, tr("echec de la sauvegarde"),
                                 tr("echec de la création du deck"),
                                     QMessageBox::Ok);
    }

    selectDeck->addItem(newDeck->text());
    selectDeck->setCurrentIndex(selectDeck->findText(newDeck->text()));
}

void deckEdit::effacerDeck()
{
    redoList.clear();

    undoList.push_back(deck);
    undoList.back().insert( undoList.back().end(), extraDeck.begin(),
                            extraDeck.end());

    deck.clear();
    extraDeck.clear();

    indiceCarteDeck = 0;
    indiceCarteExtraDeck = 0;
    nbrCarteMonstre = 0;
    nbrCarteMagie = 0;
    nbrCartePiege = 0;

    updateDeckVisu();
    updateExtraDeckVisu();
    sauvegarderDiscretionMax();
}

void deckEdit::melangerDeck()
{
    redoList.clear();

    undoList.push_back(deck);
    undoList.back().insert( undoList.back().end(), extraDeck.begin(),
                            extraDeck.end());

    std::random_shuffle(deck.begin(), deck.end());
    std::random_shuffle(extraDeck.begin(), extraDeck.end());

    updateDeckVisu();
    updateExtraDeckVisu();
    sauvegarderDiscretionMax();
}

struct compCarte
{
    bool operator()(Carte* c1, Carte* c2)
    {
        if (c1->genre != c2->genre)
            return c1->genre < c2->genre;

        // same genre

        if(c1->genre != 0) // pas un monstre
            return c1->nom < c2->nom;

        // monstre

        // sous genre diff
        if(c1->sous_type != c2->sous_type)
            return c1->sous_type > c2->sous_type;

        if(c1->niveau != c2->niveau) // si pas le meme niveau
            return c1->niveau > c2->niveau;

        if(c1->atk != c2->atk) // si pas la meme atk
            return c1->atk > c2->atk;

        return c1->nom < c2->nom; // si meme niveau

    }
};



void deckEdit::trierDeck()
{
    redoList.clear();

    undoList.push_back(deck);
    undoList.back().insert( undoList.back().end(), extraDeck.begin(),
                            extraDeck.end());

    std::sort(deck.begin(), deck.end(), compCarte());
    std::sort(extraDeck.begin(), extraDeck.end(), compCarte());

    updateDeckVisu();
    updateExtraDeckVisu();
    sauvegarderDiscretionMax();
}

void deckEdit::updPreview()
{
    std::vector<Carte*> newList;
    newList.clear();

    for(Carte* carte : *allCards)
    {
        // ... Filtre sur le Genre (Monstre, magie ... ) .......................

        std::string cardName = ((carte->nom).toStdString());
        std::transform(cardName.begin(), cardName.end(), cardName.begin(),
                       ::tolower);

        std::string search = (textSearch->text()).toStdString();
        std::transform(search.begin(), search.end(), search.begin(), ::tolower);

        if(((cardName).find(search) != std::string::npos )
                && (carte->genre == choixGenre->currentIndex()-1
                || choixGenre->currentIndex() == TOUS)
            && (carte->attribut == choixAttribut->currentIndex()-1
                || choixAttribut->currentIndex() == TOUS))
        {


            if(carte->genre == 0) // si monstre
            {
                if(choixSousGenre->currentIndex() == TOUS
                        || carte->sous_type == choixSousGenre->currentIndex()-1)
                {
                    newList.push_back(carte);
                }
            }

            else
                newList.push_back(carte);
        }
    }


    cardList->updateSearch(&newList);

    for(CardPreview *cardPreviewCourante : (*cardList->cardPreviewList))
    {
        QObject::connect(cardPreviewCourante, SIGNAL(clicked(Carte*)),
                         this, SLOT(addCard2Deck(Carte*)));
    }
}

void deckEdit::clearSearch()
{
    choixGenre->setCurrentIndex(0);
    textSearch->clear();
    updPreview();
}

void deckEdit::loadDeck()
{
    Parser leParser;


}

void deckEdit::obliterationDuDeck()
{
    QFile ripFile (deckRep + deckName + QString(".deck"));
        ripFile.remove();

    nomDeck->clear();
    nomDeck->setPlaceholderText(tr("Nom du Deck"));

    effacerDeck();
    clearSearch();
}

void deckEdit::plus2But()
{
    if(stealBut->isVisible()){

        plusBut->setIcon("\uf104");
        plusBut -> setToolTip(tr("Réorganiser les cartes"));
        stealBut->setVisible(false);
        
    } else {

        stealBut->setVisible(true);
        plusBut -> setToolTip(tr("Fermer les options de tri"));
        plusBut->setIcon("\uf105");
    }
}

void deckEdit::toujoursPlus2But()
{
    if(cardFilterAdv->isVisible()){

        plusFiltrBut->setIcon("\uf078");
        plusFiltrBut -> setToolTip(tr("Réorganiser la prévisualisation"
                                      "des cartes"));
        cardFilterAdv->setVisible(false);

    } else {

        cardFilterAdv->setVisible(true);
        plusFiltrBut -> setToolTip(tr("Fermer les options de tri"));
        plusFiltrBut->setIcon("\uf077");
    }
}

void deckEdit::slotUndo()
{
    if(undoList.empty())
        return;

    redoList.push_back(deck);
    redoList.back().insert( redoList.back().end(), extraDeck.begin(),
                            extraDeck.end());

    deck.clear();
    extraDeck.clear();
    indiceCarteDeck = 0;
    indiceCarteExtraDeck = 0;
    nbrCarteMonstre = 0;
    nbrCarteMagie = 0;
    nbrCartePiege = 0;

    for(Carte* laCarteCourante : undoList.back())
    {
        if(laCarteCourante->sous_type != 2)
        {
            deck.push_back(laCarteCourante);
            indiceCarteDeck++;
        }
        else
        {
            extraDeck.push_back(laCarteCourante);
            indiceCarteExtraDeck++;
        }
    }

    undoList.pop_back();
    updateDeckVisu();
    updateExtraDeckVisu();
    sauvegarderDiscretionMax();
}

void deckEdit::slotRedo()
{
    if(redoList.empty())
        return;

    undoList.push_back(deck);
    undoList.back().insert( undoList.back().end(), extraDeck.begin(),
                            extraDeck.end());

    deck.clear();
    extraDeck.clear();
    indiceCarteDeck = 0;
    indiceCarteExtraDeck = 0;
    nbrCarteMonstre = 0;
    nbrCarteMagie = 0;
    nbrCartePiege = 0;

    for(Carte* laCarteCourante : redoList.back())
    {
        if(laCarteCourante->sous_type != 2)
        {
            deck.push_back(laCarteCourante);
            indiceCarteDeck++;
        }
        else
        {
            extraDeck.push_back(laCarteCourante);
            indiceCarteExtraDeck++;
        }

    }
    redoList.pop_back();
    updateDeckVisu();
    updateExtraDeckVisu();
    sauvegarderDiscretionMax();
}

void deckEdit::slotAttribut()
{
    choixAttribut->clear();
    switch(choixGenre->currentIndex())
    {
        case TOUS:
            choixAttribut->addItem(tr("Tous"), 0);
            choixSousGenre->setVisible(false);
        break;

        case MONSTRE:
            choixAttribut->addItem(tr("Tous"), 0);
            choixAttribut->addItem(tr("Lumière"), 1);
            choixAttribut->addItem(tr("Tenebre"), 2);
            choixAttribut->addItem(tr("Terre"), 3);
            choixAttribut->addItem(tr("Eau"), 4);
            choixAttribut->addItem(tr("Feu"), 5);
            choixAttribut->addItem(tr("Vent"), 6);
            choixAttribut->addItem(tr("Divin"), 7);

            choixAttribut->setItemIcon(1, QIcon(imgRep + "LUMIERE"));
            choixAttribut->setItemIcon(2, QIcon(imgRep + "TENEBRE"));
            choixAttribut->setItemIcon(3, QIcon(imgRep + "TERRE"));
            choixAttribut->setItemIcon(4, QIcon(imgRep + "EAU"));
            choixAttribut->setItemIcon(5, QIcon(imgRep + "FEU"));
            choixAttribut->setItemIcon(6, QIcon(imgRep + "VENT"));
            choixAttribut->setItemIcon(7, QIcon(imgRep + "DIVIN"));

            choixAttribut->setCurrentIndex(0);
            spinAtk->setDisabled(false);
            spinDef->setDisabled(false);
            //choixType->setDisabled(false);
            choixSousGenre->setCurrentIndex(TOUS);
            choixSousGenre->setDisabled(false);
            choixSousGenre->setVisible(true);
            //spinNiveau->setDisabled(false);
        break;

        case MAGIE:
            choixAttribut->addItem(tr("Tous"), 0);
            choixAttribut->addItem(tr("Normal"), 1);
            choixAttribut->addItem(tr("Continue"),2);
            choixAttribut->addItem(tr("Equipement"), 3);
            choixAttribut->addItem(tr("Jeu-Rapide"), 4);
            choixAttribut->addItem(tr("Rituelle"), 5);
            choixAttribut->addItem(tr("Terrain"), 6);

            choixAttribut->setItemIcon(1, QIcon(imgRep + "Normal-N"));
            choixAttribut->setItemIcon(2, QIcon(imgRep + "Continuous"));
            choixAttribut->setItemIcon(3, QIcon(imgRep + "Equip"));
            choixAttribut->setItemIcon(4, QIcon(imgRep + "Quick-Play"));
            choixAttribut->setItemIcon(5, QIcon(imgRep + "Ritual"));
            choixAttribut->setItemIcon(6, QIcon(imgRep + "Field"));

            choixAttribut->setCurrentIndex(0);

            spinAtk->setDisabled(true);
            spinDef->setDisabled(true);
            //choixType->setDisabled(true);
            choixSousGenre->setDisabled(true);
            choixSousGenre->setVisible(false);
            //spinNiveau->setDisabled(true);
        break;

        case PIEGE:
            choixAttribut->addItem(tr("Tous"), 0);
            choixAttribut->addItem(tr("Normal"), 1);
            choixAttribut->addItem(tr("Continue"), 2);
            choixAttribut->addItem(tr("Contre"), 3);

            choixAttribut->setItemIcon(1, QIcon(imgRep + "Normal-N"));
            choixAttribut->setItemIcon(2, QIcon(imgRep + "Continuous"));
            choixAttribut->setItemIcon(3, QIcon(imgRep + "Counter"));

            choixAttribut->setCurrentIndex(0);

            spinAtk->setDisabled(true);
            spinDef->setDisabled(true);
            //choixType->setDisabled(true);
            choixSousGenre->setDisabled(true);
            choixSousGenre->setVisible(false);
           // spinNiveau->setDisabled(true);
    }
}
