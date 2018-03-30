#include "../inc/cardpreview.h"

CardPreview::CardPreview(const Carte *carte)
{
    mainLayout = new QHBoxLayout;

    const QStringList genreList = {tr("Monstre"), tr("Magie"), tr("Piège")};
    const QStringList infoList = {carte->nom, genreList.at(carte->genre),
                                 tr("Niveau ") + carte->niveau,
                                 tr("Attaque: ") + carte->atk,
                                 tr("Défense") + carte->def};

    QVBoxLayout *info = new QVBoxLayout;
    QPixmap *image = new QPixmap(carte->image);
    QLabel *imageLabel = new QLabel;
    imageLabel->setPixmap(*image);

    for(int i=0; i<INFOLABEL_MAX; i++)
    {
        tabInfoLabel[i] = new QLabel(infoList.at(i));
        info->addWidget(tabInfoLabel[i]);
    }

    mainLayout->addWidget(imageLabel);
    mainLayout->addLayout(info);
}

void CardPreview::mousePressEvent (QMouseEvent * e)
{
    if (e->button() == Qt::RightButton)
    {
        emit rightClicked();
    }
    else if (e->button() == Qt::LeftButton)
    {
        emit clicked();
    }
}
