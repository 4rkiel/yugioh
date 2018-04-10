#include "../inc/cardlistpreview.h"



CardListPreview::CardListPreview(std::vector<Carte *> *cardList)
{
    mainLayout = new QVBoxLayout;
    cardPreviewList =  new std::vector<CardPreview *>;

    updateSearch(cardList);
    setLayout(mainLayout);
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

/* remplit le widget de CardPreview à partir d'un vecteur de carte */
void CardListPreview::updateSearch(std::vector<Carte *> *cardList2)
{
    for(unsigned int i=0; i<cardPreviewList->size(); i++)
    {
        mainLayout->removeWidget(cardPreviewList->at(i));
        cardPreviewList->at(i)->deleteLater();
    }
    cardPreviewList->clear();

    for(unsigned int i=0; i<cardList2->size(); i++)
    {
        cardPreviewList->push_back(new CardPreview(cardList2->at(i)));
        mainLayout->addWidget(cardPreviewList->at(i));
    }
}
