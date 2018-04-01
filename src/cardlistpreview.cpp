#include "../inc/cardlistpreview.h"



CardListPreview::CardListPreview(Parser *parser)
{
    mainLayout = new QVBoxLayout;
    cardPreviewList =  new std::vector<CardPreview *>;

    updateSearch(parser->all_cards);
    setLayout(mainLayout);
}

/* remplit le widget de CardPreview à partir d'un vecteur de carte */
void CardListPreview::updateSearch(std::vector<Carte *> *cardList)
{
    cardPreviewList->clear();

    for(unsigned int i=0; i<cardList->size(); i++)
    {
        cardPreviewList->push_back(new CardPreview(cardList->at(i)));
        mainLayout->addWidget(cardPreviewList->at(i));
    }

    mainLayout->addWidget(new QLabel("yolo"));
}
