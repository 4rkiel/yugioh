#include "../inc/deckedit.h"

#include <inc/deckedit.h>


deckEdit::deckEdit(std::vector<Carte *> *allCard)
{
    allCards = allCard;

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

//    cardPreviewList = new std::vector<QHBoxLayout*>;

    for(int i=0; i<NBR_BUTTON_DECK_EDIT; i++)
    {
        tabBut[i] = new FlatButt("", buttonName.at(i));
        tabBut[i]->setDefault(true);
        //tabBut[i]->setText(buttonName.at(i));
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

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *mainL1 = new QHBoxLayout;
    QHBoxLayout *mainL2 = new QHBoxLayout;


        // ... selecteur / creation de Deck ....................................
        //TODO refactorer le code

        QFrame *editCreate = new QFrame;
        editCreate->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
        editCreate->setStyleSheet("border: 1px solid blue");
        mainL1->addWidget(editCreate);
        editCreate->setStyleSheet("background-color: #ECEFF1");
        QVBoxLayout *editCreateLayout = new QVBoxLayout;
        editCreate->setLayout(editCreateLayout);


            // ... selecteur de Deck ...........................................

            QStringList deckList = QDir(deckRep).entryList({"*.deck"});


            /* on tronc l'extension ".deck" avant de placer dans la Combo */
            foreach (QString str, deckList)
            {
                str.chop(5);
                selectDeck->addItem(str);
            }

            QHBoxLayout *part1 = new QHBoxLayout;
            QVBoxLayout *part2 = new QVBoxLayout;

            part1->addLayout(part2);

            QFormLayout *formulaire = new QFormLayout;
            part2->addLayout(formulaire);


                formulaire->addRow(tr("Deck: "), selectDeck);


                // ... name a deck .............................................


                formulaire->addRow(tabBut[CREER], newDeck);


                //TODO signal qui crée le deck

            // ... boutons verticaux ...........................................

                QVBoxLayout *buttonV = new QVBoxLayout;
                part1->addLayout(buttonV);


                    buttonV->addWidget(tabBut[SAUVER]);
                    buttonV->addWidget(tabBut[SUPPRIMER]);

                //TODO signaux

                editCreateLayout->addLayout(part1);

            // ... boutons horizontaux .........................................

            QHBoxLayout *buttonH = new QHBoxLayout;
            editCreateLayout->addLayout(buttonH);

                buttonH->addWidget(tabBut[MELANGER]);
                buttonH->addWidget(tabBut[TRIER]);
                buttonH->addWidget(tabBut[EFFACER]);

                //TODO signaux




        // ... Compteur de cartes / visualisateur de Deck ......................

        QVBoxLayout *deckVisuLayout = new QVBoxLayout;
        mainL2->addLayout(deckVisuLayout);


            // ... compteur de cartes ..........................................

            QFrame *cardInfo = new QFrame;
            cardInfo->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
            cardInfo->setObjectName("frameVisu");
            cardInfo->setStyleSheet("#frameVisu{border: 1px solid green}");

            QHBoxLayout *layoutInfo = new QHBoxLayout;
            cardInfo->setLayout(layoutInfo);

                deckLabel = new QLabel();
                deckLabel->setText(tr("Deck vide"));

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

            QFrame *deckVisu = new QFrame;
            deckVisu->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            deckVisu->setObjectName("frameVisu");
            deckVisu->setStyleSheet("#frameVisu{border: 1px solid green}");

            QGridLayout *layoutCard = new QGridLayout;
            deckVisu->setLayout(layoutCard);
            int limit = NBR_CARTE_DECK_VISU/10;
            for(int i=0; i<limit; i++)
            {
                for(int y=0; y<10; y++)
                {
                    layoutCard->addWidget(tabCardVisu[i*10+y], i, y, 1, 1);
                }
            }

            //TODO signaux


            // ... visualiseur d'extra Deck ....................................

//            QFrame *extraDeckVisu = new QFrame;
//            extraDeckVisu->setSizePolicy(QSizePolicy::Minimum,
//                                         QSizePolicy::Maximum);
//            extraDeckVisu->setObjectName("extraDeckVisu");
//            extraDeckVisu->setStyleSheet("#extraDeckVisu"
//                                         "{border: 1px solid green}");

//            QHBoxLayout *layoutExtraCard = new QHBoxLayout;
//            extraDeckVisu->setLayout(layoutExtraCard);

//            for(int i=0; i<NBR_CARTE_EXTRA_DECK; i++)
//            {
//                    layoutExtraCard->addWidget(tabExtraDeck[i]);
//            }

            for(int i=0; i<NBR_CARTE_EXTRA_DECK; i++)
            {
                    layoutCard->addWidget(tabExtraDeck[i], limit, i, 1, 1);
            }


        deckVisuLayout->addWidget(cardInfo);
        deckVisuLayout->addWidget(deckVisu);
//        deckVisuLayout->addWidget(extraDeckVisu);


        // ... recherche de cartes .............................................

        QFrame *cardFilter = new QFrame;
        cardFilter->setSizePolicy(QSizePolicy::Minimum,
                                  QSizePolicy::Maximum);
        cardFilter->setStyleSheet("border: 1px solid blue");
        mainL1->addWidget(cardFilter);
        cardFilter->setStyleSheet("background-color: #ECEFF1");
        QHBoxLayout *colonne = new QHBoxLayout;        


            // ... recherche par propriétés ....................................

            QFrame *propFilter = new QFrame;
            propFilter->setSizePolicy(QSizePolicy::Minimum,
                                      QSizePolicy::Maximum);
            propFilter->setObjectName("propFilter");
            propFilter->setStyleSheet("#propFilter"
                                         "{border: 1px solid green}");

            QFormLayout *propForm = new QFormLayout;
            propFilter->setLayout(propForm);


                // ... Genre / Sous-genre ......................................

                QHBoxLayout *genreColonne = new QHBoxLayout;
                genreColonne->addWidget(choixGenre);
                genreColonne->addWidget(choixSousGenre);

//                QSizePolicy sp_retain = choixSousGenre->sizePolicy();
//                sp_retain.setRetainSizeWhenHidden(true);
//                sp_retain.setHorizontalPolicy(QSizePolicy::Minimum);
//                sp_retain.setVerticalPolicy(QSizePolicy::Minimum);
//                choixSousGenre->setSizePolicy(sp_retain);
                choixSousGenre->setVisible(false);

                propForm->addRow(tr("Genre: "), genreColonne);



                    // ... Attribut ............................................

                    propForm->addRow(tr("Attribut: "), choixAttribut);



                    // ... Type ................................................

                    //propForm->addRow(tr("Type: "), choixType);



                    // ... Niveau ..............................................

//                    spinNiveau->setAccelerated(true);
//                    spinNiveau->setSingleStep(1);
//                    spinNiveau->setMinimum(1);
//                    spinNiveau->setMaximum(12);


 //               propForm->addRow(tr("Niveau"), spinNiveau);



                // ... recherche approfondis + bouttons ........................

                QVBoxLayout *prop2Vmain = new QVBoxLayout;

                    QHBoxLayout *prop2H = new QHBoxLayout;



                        // ... Atk / Def .......................................

//                        QVBoxLayout *propAtkDef = new QVBoxLayout;


//                            QFormLayout *atkDefForm = new QFormLayout;

//                            atkDefForm->addRow(tr("Attaque: "), spinAtk);
//                            atkDefForm->addRow(tr("Défense: "), spinDef);


//                        propAtkDef->addLayout(atkDefForm);



                        // ... Effect Box ......................................

//                        effectBoxBut = new FlatButt;
//                        effectBoxBut->setDefault(true);
//                        effectBoxBut->setText(tr("Effets"));
//                        effectBoxBut->setSizePolicy(QSizePolicy::Minimum,
//                                                    QSizePolicy::Minimum);


     //               prop2H->addLayout(propAtkDef);
         //           prop2H->addWidget(effectBoxBut);



                    // ... Annuler recherche / filrer ..........................

                    QVBoxLayout *deleteSearch = new QVBoxLayout;

                    QHBoxLayout *annSearch = new QHBoxLayout;
                        annSearch->addWidget(tabBut[ANNULER_RECHERCHE]);
                        annSearch->addWidget(textSearch);
                    deleteSearch->addLayout(annSearch);

                    //TODO: connect

                    deleteSearch->addWidget(tabBut[FILTRER]);

                    //TODO: connect



                prop2Vmain->addLayout(prop2H);
                prop2Vmain->addLayout(deleteSearch);


            colonne->addWidget(propFilter);
            colonne->addLayout(prop2Vmain);


        cardFilter->setLayout(colonne);

        // ... scroll la liste des cartes recherchées ..........................

        QScrollArea *deckScroll = new QScrollArea;
        deckScroll -> setFrameShape(QFrame::NoFrame);
        deckScroll -> setWidgetResizable(true);
        deckScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        deckScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        deckScroll -> setFocusPolicy(Qt::NoFocus);
        deckScroll->setBackgroundRole(QPalette::Light);
        deckScroll->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

            //Parser *parser = new Parser;

            cardList = new CardListPreview(allCard);
            cardList->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

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

    connect(tabBut[SAUVER], SIGNAL(clicked()), this, SLOT(sauvegarder()));
    connect(tabBut[CREER], SIGNAL(clicked()), this, SLOT(creer()));
    connect(tabBut[EFFACER], SIGNAL(clicked()), this, SLOT(effacerDeck()));
    connect(tabBut[MELANGER], SIGNAL(clicked()), this, SLOT(melangerDeck()));
    connect(tabBut[TRIER], SIGNAL(clicked()), this, SLOT(trierDeck()));
    connect(tabBut[FILTRER], SIGNAL(clicked()), this, SLOT(updPreview()));

    connect(choixGenre, SIGNAL(currentIndexChanged(int)), this,SLOT(slotAttribut()));
    connect(tabBut[ANNULER_RECHERCHE], SIGNAL(clicked()), this, SLOT(clearSearch()));
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
}

void deckEdit::rmvCard2Deck()
{
    size_t pos;
    FlatButt* cardButton2Rmv = qobject_cast<FlatButt*>(sender());
    std::vector<QPushButton *>::iterator it = std::find(tabCardVisu.begin(),
                                         tabCardVisu.end(), cardButton2Rmv);
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
}

void deckEdit::sauvegarder()
{
    if(deck.size() != 40)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("M-Masaka !"), tr("Deck invalide: Souhaitez "
                                    "vous tout de même sauvegarder ? Vous "
                                    "pourrez éditer votre deck ultérieurement."),
                                    QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No)
          return;
    }

    QString file = deckRep + selectDeck->currentText() + QString(".deck");
    qDebug() << "SAVE: URL FICHIER ECRITURE DECK: "+file;




    QFile *myfile = new QFile(file);

    if(!myfile->open(QFile::WriteOnly | QFile::Text))
    {// chemin  corrompue
        QMessageBox::information(this, tr("echec de la sauvegarde"), tr("Le deck ") +
                                 selectDeck->currentText() + tr(" n'a pas pu être sauvegardé."),
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
        in << QString::number(carte->id);
    }

    myfile->close();

    QMessageBox::information(this, tr("youpi !"), tr("Le deck ") +
                             selectDeck->currentText() + tr(" à était enregistré."),
                             QMessageBox::Ok);
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
        QMessageBox::information(this, tr("M-Masaka !"), tr("Impossible de créer le deck \"")
                                + newDeck->text() +tr("\": le deck existe déjà."),
                                    QMessageBox::Ok);
          return;
    }

    QFile myfile(deckRep + newDeck->text() + QString(".deck"));
    if(!myfile.open(QIODevice::WriteOnly | QIODevice::Append))
    {// chemin  corrompue
        QMessageBox::information(this, tr("echec de la sauvegarde"), tr("echec de la création du deck"),
                                     QMessageBox::Ok);
    }

    selectDeck->addItem(newDeck->text());
    selectDeck->setCurrentIndex(selectDeck->findText(newDeck->text()));
}

void deckEdit::effacerDeck()
{
    deck.clear();
    extraDeck.clear();

    indiceCarteDeck = 0;
    indiceCarteExtraDeck = 0;
    nbrCarteMonstre = 0;
    nbrCarteMagie = 0;
    nbrCartePiege = 0;

    updateDeckVisu();
    updateExtraDeckVisu();
}

void deckEdit::melangerDeck()
{
    std::random_shuffle(deck.begin(), deck.end());
    std::random_shuffle(extraDeck.begin(), extraDeck.end());

    updateDeckVisu();
    updateExtraDeckVisu();
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
    std::sort(deck.begin(), deck.end(), compCarte());
    std::sort(extraDeck.begin(), extraDeck.end(), compCarte());

    updateDeckVisu();
    updateExtraDeckVisu();
}

void deckEdit::updPreview()
{
    // TODO ajouter des "all" pour par exemple ne pas filtrer ...
    std::vector<Carte*> newList;
    std::vector<Carte*> tmpList;
    newList.clear();

    for(Carte* carte : *allCards)
    {
        // ... Filtre sur le Genre (Monstre, magie ... ) .......................

        std::string cardName = ((carte->nom).toStdString());
        std::transform(cardName.begin(), cardName.end(), cardName.begin(), ::tolower);

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
}

void deckEdit::clearSearch()
{
    choixGenre->setCurrentIndex(0);
    textSearch->clear();
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
