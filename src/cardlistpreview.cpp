#include "../inc/cardlistpreview.h"

CardListPreview::CardListPreview(std::vector<Carte *> cardList)
{
    mainLayout = new QVBoxLayout;
    cardPreviewList =  new std::vector<CardPreview *>;

    for(unsigned int i=0; i<cardList.size(); i++)
    {
        cardPreviewList->push_back(new CardPreview(cardList[i]));
        mainLayout->addWidget(cardPreviewList->at(i));
    }
}
