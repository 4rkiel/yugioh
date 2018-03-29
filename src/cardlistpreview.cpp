#include "../inc/cardlistpreview.h"

CardListPreview::CardListPreview(std::vector<Carte *> Card) : allCard(Card)
{
    mainLayout = new QVBoxLayout;
    cardPreviewList =  new std::vector<QHBoxLayout *>;
}
