#include "../inc/deckedit.h"


deckEdit::deckEdit()
{
    selectDeck = new QComboBox;
    choixGenre = new QComboBox;
    choixSousGenre  = new QComboBox;

    newDeck = new QLineEdit;

    for(int i=0; i<NBR_BUTTON_DECK_EDIT; i++)
    {
        tabBut[i] = new QPushButton;
        tabBut[i]->setStyleSheet("background: red");
        tabBut[i]->setText(buttonName.at(i));
    }

    for(int i=0; i<NBR_CARTE_DECK_VISU; i++)
    {
        tabCardVisu[i] = new QPushButton;
        tabCardVisu[i]->setStyleSheet("border-image: url(" + defaultImage + ");"
                            "margin: 1px ;border: 1px solid black");
        tabCardVisu[i]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    }

    for(int i=0; i<NBR_CARTE_EXTRA_DECK; i++)
    {
        tabExtraDeck[i] = new QPushButton;
        tabExtraDeck[i]->setStyleSheet("border-image: url(" + defaultImage + ");"
                             "margin: 1px ;border: 1px solid black");
        tabCardVisu[i]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    }

    choixGenre->addItems(genreList);
    choixSousGenre->addItems(sousGenreList);

    QGridLayout *mainLayout = new QGridLayout;


        // ... selecteur / creation de Deck ....................................
        //TODO refactorer le code

        QFrame *editCreate = new QFrame;
        editCreate->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        editCreate->setStyleSheet("border: 1px solid blue");
        mainLayout->addWidget(editCreate, 0, 0, 1, 4);
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


            // ... boutons verticaux ...........................................

            QVBoxLayout *buttonV = new QVBoxLayout;
            editCreateLayout->addLayout(buttonV, 0, 1, 2, 1);

                buttonV->addStretch();
                buttonV->addWidget(tabBut[SAUVER]);
                buttonV->addWidget(tabBut[CREER]);
                buttonV->addWidget(tabBut[SUPPRIMER]);



        // ... Compteur de cartes / visualisateur de Deck ......................

        QVBoxLayout *deckVisuLayout = new QVBoxLayout;
        mainLayout->addLayout(deckVisuLayout, 1, 0, 4, 4);


            // ... compteur de cartes ..........................................

            QFrame *cardInfo = new QFrame;
            cardInfo->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
            cardInfo->setObjectName("frameVisu");
            cardInfo->setStyleSheet("#frameVisu{border: 1px solid green}");

            QHBoxLayout *layoutInfo = new QHBoxLayout;
            cardInfo->setLayout(layoutInfo);

                QLabel *deckLabel = new QLabel();
                deckLabel->setText(tr("Nombre de carte: "));

                QLabel *infoLabel = new QLabel();
                infoLabel->setText(tr("Monstre: \tMagie:  \tPiège: "));

                layoutInfo->addWidget(deckLabel);
                layoutInfo->addWidget(infoLabel);


            // ... visualiteur de Deck .........................................

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


            // ... visualiteur d'extra Deck ....................................

            QFrame *extraDeckVisu = new QFrame;
            extraDeckVisu->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
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
        cardFilter->setStyleSheet("border: 1px solid blue");
        mainLayout->addWidget(cardFilter, 0, 4, 1, 7);
        cardFilter->setStyleSheet("background-color: #ECEFF1");
        QHBoxLayout *colonne = new QHBoxLayout;
        cardFilter->setLayout(colonne);


            // ... recherche par propriétés ....................................

            QFrame *propFilter = new QFrame;
            propFilter->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
            propFilter->setObjectName("propFilter");
            propFilter->setStyleSheet("#propFilter"
                                         "{border: 1px solid green}");

            QFormLayout *propForm = new QFormLayout;
            propFilter->setLayout(propForm);


                // ... Genre ...................................................

                QHBoxLayout *genreColonne = new QHBoxLayout;
                genreColonne->addWidget(choixGenre);
                genreColonne->addWidget(choixSousGenre);

                propForm->addRow("Genre: ", genreColonne);


                // ... Sous-genre ..............................................


                // ... Attribut ................................................


                // ... Type ....................................................


                // ... Niveau ..................................................

            colonne->addWidget(propFilter);


            // ... recherche approfondis + bouttons ............................





    setLayout(mainLayout);
}
