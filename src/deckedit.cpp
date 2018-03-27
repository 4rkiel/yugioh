#include "../inc/deckedit.h"


deckEdit::deckEdit()
{
    selectDeck = new QComboBox;
    newDeck = new QLineEdit;

    for(int i=0; i<NBR_BUTTON_DECK_EDIT; i++)
    {
        tabBut[i] = new QPushButton;
        tabBut[i]->setText(buttonName.at(i));
        tabBut[i]->setMinimumWidth(10);
    }

    QGridLayout *mainLayout = new QGridLayout;


        // ... selecteur / creation de Deck ....................................

        QFrame *editCreate = new QFrame;
        editCreate->setFrameStyle(QFrame::Box);
        mainLayout->addWidget(editCreate, 0, 0, 1, 4);
        editCreate->setStyleSheet("background-color: blue);");
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
            editCreateLayout->addLayout(formulaire, 0, 0);

                formulaire->addRow("Deck: ", selectDeck);


                // ... name a deck .............................................

                tabBut[QUITTER]->setText(tr("Quitter"));
                formulaire->addRow(tabBut[QUITTER], newDeck);


                //TODO signal qui crée le deck


            // ... boutons horizontaux .........................................

            QHBoxLayout *buttonH = new QHBoxLayout;
            editCreateLayout->addLayout(buttonH, 1, 0, 1, 3);

                buttonH->addWidget(tabBut[MELANGER]);
                buttonH->addWidget(tabBut[TRIER]);
                buttonH->addWidget(tabBut[EFFACER]);


            // ... boutons verticaux ...........................................

            QVBoxLayout *buttonV = new QVBoxLayout;
            editCreateLayout->addLayout(buttonV, 2, 1, 3, 1);

                buttonV->addWidget(tabBut[SAUVER]);
                buttonV->addWidget(tabBut[CREER]);
                buttonV->addWidget(tabBut[SUPPRIMER]);


        // ... Compteur de cartes / visualisateur de Deck ......................

        QVBoxLayout *deckVisuLayout = new QVBoxLayout;
        mainLayout->addLayout(deckVisuLayout, 1, 0, 4, 3);


            // ... compteur de cartes ..........................................





    setLayout(mainLayout);
}
