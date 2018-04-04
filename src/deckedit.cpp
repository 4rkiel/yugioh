#include "../inc/deckedit.h"


deckEdit::deckEdit(/*std::vector<Carte *> *allCard*/)
{
    selectDeck = new QComboBox;
    choixGenre = new QComboBox;
    choixSousGenre  = new QComboBox;
    choixAttribut = new QComboBox;
    choixType = new QComboBox;

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
        tabBut[i] = new QPushButton;
        tabBut[i]->setDefault(true);
        tabBut[i]->setText(buttonName.at(i));
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
//        tabCardVisu[i]->setSizePolicy(QSizePolicy::Minimum,
//                                      QSizePolicy::Minimum);

        QObject::connect(tabCardVisu[i], SIGNAL(clicked()), this, SLOT(rmvCard2Deck()));

    }

    for(int i=0; i<NBR_CARTE_EXTRA_DECK; i++)
    {
        tabExtraDeck[i] = new QPushButton;
        tabExtraDeck[i]->setDefault(true);
//        tabExtraDeck[i]->setStyleSheet("border-image: url(" + defaultImage +
//                                      ");margin: 1px ;border: 1px solid black");
        tabCardVisu[i]->setSizePolicy(QSizePolicy::Minimum,
                                      QSizePolicy::Minimum);
    }

    choixGenre->addItems(genreList);
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
        QGridLayout *editCreateLayout = new QGridLayout;
        editCreate->setLayout(editCreateLayout);


            // ... selecteur de Deck ...........................................

            QStringList deckList = QDir(deckRep).entryList({"*.deck"});


            /* on tronc l'extension ".deck" avant de placer dans la QComboBox */
            foreach (QString str, deckList)
            {
                str.chop(5);
                selectDeck->addItem(str);
            }

            QFormLayout *formulaire = new QFormLayout;
            editCreateLayout->addLayout(formulaire, 0, 0, 1, 1);

                formulaire->addRow("Deck: ", selectDeck);


                // ... name a deck .............................................

                tabBut[QUITTER]->setText(tr("Quitter"));
                formulaire->addRow(tabBut[QUITTER], newDeck);


                //TODO signal qui crée le deck


            // ... boutons horizontaux .........................................

            QHBoxLayout *buttonH = new QHBoxLayout;
            editCreateLayout->addLayout(buttonH, 1, 0, 1, 1);

                buttonH->addWidget(tabBut[MELANGER]);
                buttonH->addWidget(tabBut[TRIER]);
                buttonH->addWidget(tabBut[EFFACER]);
                buttonH->addStretch();

                //TODO signaux


            // ... boutons verticaux ...........................................

            QVBoxLayout *buttonV = new QVBoxLayout;
            editCreateLayout->addLayout(buttonV, 0, 1, 2, 1);

                buttonV->addStretch();
                buttonV->addWidget(tabBut[SAUVER]);
                buttonV->addWidget(tabBut[CREER]);
                buttonV->addWidget(tabBut[SUPPRIMER]);

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
                deckLabel->setText(tr("Nombre de carte: ") + QString::number(nbrCarteMonstre
                                   + nbrCarteMagie + nbrCartePiege));

                infoMonstreLabel = new QLabel();
                infoMagieLabel = new QLabel();
                infoPiegeLabel = new QLabel();
                infoMonstreLabel->setText(tr("Monstre: ") + QString::number(nbrCarteMonstre));
                infoMagieLabel->setText(tr("\tMagie: ") + QString::number(nbrCarteMagie));
                infoPiegeLabel->setText(tr("\tPiège: ") + QString::number(nbrCartePiege));

                layoutInfo->addWidget(deckLabel);
                layoutInfo->addWidget(infoMonstreLabel);
                layoutInfo->addWidget(infoMagieLabel);
                layoutInfo->addWidget(infoPiegeLabel);



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

            QFrame *extraDeckVisu = new QFrame;
            extraDeckVisu->setSizePolicy(QSizePolicy::Minimum,
                                         QSizePolicy::Maximum);
            extraDeckVisu->setObjectName("extraDeckVisu");
            extraDeckVisu->setStyleSheet("#extraDeckVisu"
                                         "{border: 1px solid green}");

            QHBoxLayout *layoutExtraCard = new QHBoxLayout;
            extraDeckVisu->setLayout(layoutExtraCard);

            for(int i=0; i<NBR_CARTE_EXTRA_DECK; i++)
            {
                    layoutExtraCard->addWidget(tabExtraDeck[i]);
            }


        deckVisuLayout->addWidget(cardInfo);
        deckVisuLayout->addWidget(deckVisu);
        deckVisuLayout->addWidget(extraDeckVisu);


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

                propForm->addRow("Genre: ", genreColonne);



                    // ... Attribut ............................................

                    propForm->addRow("Attribut: ", choixAttribut);



                    // ... Type ................................................

                    propForm->addRow(tr("Type: "), choixType);



                    // ... Niveau ..............................................

                    spinNiveau->setAccelerated(true);
                    spinNiveau->setSingleStep(1);
                    spinNiveau->setMinimum(1);
                    spinNiveau->setMaximum(12);


                propForm->addRow(tr("Niveau"), spinNiveau);



                // ... recherche approfondis + bouttons ........................

                QVBoxLayout *prop2Vmain = new QVBoxLayout;

                    QHBoxLayout *prop2H = new QHBoxLayout;



                        // ... Atk / Def .......................................

                        QVBoxLayout *propAtkDef = new QVBoxLayout;


                            QFormLayout *atkDefForm = new QFormLayout;

                            atkDefForm->addRow(tr("Attaque: "), spinAtk);
                            atkDefForm->addRow(tr("Défense: "), spinDef);


                        propAtkDef->addLayout(atkDefForm);



                        // ... Effect Box ......................................

                        effectBoxBut = new QPushButton;
                        effectBoxBut->setDefault(true);
                        effectBoxBut->setText("Effets");
                        effectBoxBut->setSizePolicy(QSizePolicy::Minimum,
                                                    QSizePolicy::Minimum);


                    prop2H->addLayout(propAtkDef);
                    prop2H->addWidget(effectBoxBut);



                    // ... Annuler recherche / filrer ..........................

                    QVBoxLayout *deleteSearch = new QVBoxLayout;


                    deleteSearch->addWidget(tabBut[ANNULER_RECHERCHE]);

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

            Parser *parser = new Parser;

            cardList = new CardListPreview(parser);
            cardList->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

            for(CardPreview *cardPreviewCourante : (*cardList->cardPreviewList))
            {
                QObject::connect(cardPreviewCourante, SIGNAL(clicked(Carte*)), this, SLOT(addCard2Deck(Carte*)));
            }

            deckScroll->setWidget(cardList);

        mainL2->addWidget(deckScroll);


    mainLayout->addLayout(mainL1);
    mainLayout->addLayout(mainL2);
    setLayout(mainLayout);
}

void deckEdit::updateDeckVisu()
{
    int i=0;
    for(; i<indiceCarteDeck; i++)
    {
        tabCardVisu[i]->setStyleSheet("border-image: url(" + deck.at(i)->image + ");"
                                                "margin: 1px ;border: 1px solid black");
        tabCardVisu[i]->setVisible(true);
    }
    for(; i<NBR_CARTE_DECK_VISU; i++)
    {
        tabCardVisu[i]->setVisible(false);
    }

    deckLabel->setText(tr("Nombre de carte: ") +
                       QString::number(nbrCarteMonstre
                                       + nbrCarteMagie + nbrCartePiege));

    infoMonstreLabel->setText(tr("Monstre: ") + QString::number(nbrCarteMonstre));
    infoMagieLabel->setText(tr("\tMagie: ") + QString::number(nbrCarteMagie));
    infoPiegeLabel->setText(tr("\tPiège: ") + QString::number(nbrCartePiege));
}

void deckEdit::updateDeckVisuLastCard()
{
    tabCardVisu[indiceCarteDeck]->setStyleSheet("border-image: url(" + deck.at(indiceCarteDeck)->image + ");"
                                            "margin: 1px ;border: 1px solid black");
    tabCardVisu[indiceCarteDeck]->setVisible(true);

    deckLabel->setText(tr("Nombre de carte: ") +
                       QString::number(nbrCarteMonstre
                                       + nbrCarteMagie + nbrCartePiege));

    infoMonstreLabel->setText(tr("Monstre: ") + QString::number(nbrCarteMonstre));
    infoMagieLabel->setText(tr("\tMagie: ") + QString::number(nbrCarteMagie));
    infoPiegeLabel->setText(tr("\tPiège: ") + QString::number(nbrCartePiege));
}



void deckEdit::addCard2Deck(Carte* carte)
{
    if(indiceCarteDeck == 40)
        return;

    deck.push_back(carte);

    switch(carte->genre)
    {
        case 0:
            nbrCarteMonstre++;
        break;

        case 1:
            nbrCarteMagie++;
        break;

        case 2:
            nbrCartePiege++;
    }

    updateDeckVisuLastCard();

    indiceCarteDeck++;
}

void deckEdit::rmvCard2Deck()
{
    QPushButton* cardButton2Rmv = qobject_cast<QPushButton*>(sender());

    size_t pos = std::find(tabCardVisu.begin(), tabCardVisu.end(), cardButton2Rmv) - tabCardVisu.begin();

    deck.erase(deck.begin()+pos);

    indiceCarteDeck--;

    updateDeckVisu();
}

void deckEdit::slotAttribut()
{
    choixAttribut->clear();
    switch(choixType->currentIndex())
    {
        case MONSTRE:
            choixAttribut->addItem(tr("Lumière"), 0);
            choixAttribut->addItem(tr("Tenebre"), 1);
            choixAttribut->addItem(tr("Terre"), 2);
            choixAttribut->addItem(tr("Eau"), 3);
            choixAttribut->addItem(tr("Feu"), 4);
            choixAttribut->addItem(tr("Vent"), 5);
            choixAttribut->addItem(tr("Divin"), 6);

            choixAttribut->setItemIcon(0, QIcon(imgRep + "LUMIERE"));
            choixAttribut->setItemIcon(1, QIcon(imgRep + "TENEBRE"));
            choixAttribut->setItemIcon(2, QIcon(imgRep + "TERRE"));
            choixAttribut->setItemIcon(3, QIcon(imgRep + "EAU"));
            choixAttribut->setItemIcon(4, QIcon(imgRep + "FEU"));
            choixAttribut->setItemIcon(5, QIcon(imgRep + "VENT"));
            choixAttribut->setItemIcon(6, QIcon(imgRep + "DIVIN"));

            choixAttribut->setCurrentIndex(rand()%7);
            spinAtk->setDisabled(false);
            spinDef->setDisabled(false);
            choixGenre->setDisabled(false);
            choixSousGenre->setDisabled(false);
            spinNiveau->setDisabled(false);
        break;

        case MAGIE:
            choixAttribut->addItem(tr("Normal"), 0);
            choixAttribut->addItem(tr("Continue"), 1);
            choixAttribut->addItem(tr("Equipement"), 2);
            choixAttribut->addItem(tr("Jeu-Rapide"), 3);
            choixAttribut->addItem(tr("Rituelle"), 4);
            choixAttribut->addItem(tr("Terrain"), 5);

            choixAttribut->setItemIcon(0, QIcon(imgRep + "Normal-N"));
            choixAttribut->setItemIcon(1, QIcon(imgRep + "Continuous"));
            choixAttribut->setItemIcon(2, QIcon(imgRep + "Equip"));
            choixAttribut->setItemIcon(3, QIcon(imgRep + "Quick-Play"));
            choixAttribut->setItemIcon(4, QIcon(imgRep + "Ritual"));
            choixAttribut->setItemIcon(5, QIcon(imgRep + "Field"));

            choixAttribut->setCurrentIndex(rand()%6);

            spinAtk->setDisabled(true);
            spinDef->setDisabled(true);
            choixGenre->setDisabled(true);
            choixSousGenre->setDisabled(true);
            spinNiveau->setDisabled(true);
        break;

        case PIEGE:
            choixAttribut->addItem(tr("Normal"), 0);
            choixAttribut->addItem(tr("Continue"), 1);
            choixAttribut->addItem(tr("Contre"), 2);

            choixAttribut->setItemIcon(0, QIcon(imgRep + "Normal-N"));
            choixAttribut->setItemIcon(1, QIcon(imgRep + "Continuous"));
            choixAttribut->setItemIcon(2, QIcon(imgRep + "Counter"));

            choixAttribut->setCurrentIndex(rand()%3);

            spinAtk->setDisabled(true);
            spinDef->setDisabled(true);
            choixGenre->setDisabled(true);
            choixSousGenre->setDisabled(true);
            spinNiveau->setDisabled(true);
    }
}
