#include "../inc/deckedit.h"


deckEdit::deckEdit()
{
    selectDeck = new QComboBox;
    newDeck = new QLineEdit;

    for(int i=0; i<NBR_BUTTON_DECK_EDIT; i++)
    {
        tabBut[i] = new QPushButton;
        tabBut[i]->setStyleSheet("background: red");
        tabBut[i]->setText(buttonName.at(i));
        tabBut[i]->setMinimumWidth(10);
    }

    for(int i=0; i<NBR_CARTE_DECK_VISU; i++)
    {
        tabCardVisu[i] = new QPushButton;
        tabCardVisu[i]->setStyleSheet("background: purple");
        tabCardVisu[i]->setText("card");
        tabCardVisu[i]->setMinimumWidth(10);
    }

    for(int i=0; i<NBR_CARTE_EXTRA_DECK; i++)
    {
        tabExtraDeck[i] = new QPushButton;
        tabExtraDeck[i]->setStyleSheet("background: cyan");
        tabExtraDeck[i]->setText("card");
        tabExtraDeck[i]->setMinimumWidth(10);
    }

    QGridLayout *mainLayout = new QGridLayout;


        // ... selecteur / creation de Deck ....................................
        //TODO refactorer le code

        QFrame *editCreate = new QFrame;
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


            // ... visualiteur de Deck ............

            QFrame *deckVisu = new QFrame;
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


            // ... visualiteur d'extra Deck ............

            QFrame *extraDeckVisu = new QFrame;
            extraDeckVisu->setObjectName("extraDeckVisu");
            extraDeckVisu->setStyleSheet("#extraDeckVisu{border: 1px solid green}");

            QGridLayout *layoutExtraCard = new QGridLayout;
            deckVisu->setLayout(layoutExtraCard);

            for(int i=0; i<NBR_CARTE_EXTRA_DECK; i++)
            {
                    layoutExtraCard->addWidget(tabExtraDeck[i], 0, i, 1, 1);
            }





            deckVisuLayout->addWidget(cardInfo);
            deckVisuLayout->addWidget(deckVisu);
            deckVisuLayout->addWidget(extraDeckVisu);




    setLayout(mainLayout);
}
