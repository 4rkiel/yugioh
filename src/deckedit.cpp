#include "../inc/deckedit.h"


deckEdit::deckEdit()
{
    selectDeck = new QComboBox;
    newDeck = new QLineEdit;

    for(int i=0; i<NBR_BUTTON_DECK_EDIT; i++)
    {
        tabBut[i] = new QPushButton;
    }

    QGridLayout *mainLayout = new QGridLayout;
    //{
        // ... selecteur / creation de Deck ....................................

        QFrame *editCreate = new QFrame;
        editCreate->setStyleSheet("background-color: #F44336);");
        QGridLayout *editCreateLayout = new QGridLayout;
        editCreate->setLayout(editCreateLayout);
        //{
            // ... selecteur de Deck ...........................................
            QStringList deckList = QDir(deckRep).entryList({"*.deck"});

            /* on tronc l'extension ".deck" avant de placer dans la QComboBox */
            foreach (QString str, deckList)
            {
                str.chop(5);
                selectDeck->addItem(str);
            }

            QFormLayout *formulaire = new QFormLayout;
            formulaire->addRow("Deck: ", selectDeck);

            editCreateLayout->addLayout(formulaire, 0, 0);

            // ... name a deck .................................................
            tabBut[QUITTER]->setText(tr("Quitter"));
            formulaire->addRow(tabBut[QUITTER], newDeck);

            //TODO signal qui crée le deck
        //}

        mainLayout->addWidget(editCreate);

    //}
    setLayout(mainLayout);
}
