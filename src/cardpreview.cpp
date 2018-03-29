#include "../inc/cardpreview.h"

CardPreview::CardPreview(const Carte carte)
{
    mainLayout = new QHBoxLayout;


     // (magie 1 ,piege 2,monstre 0)
    const QStringList genreList = {tr("Monstre"), tr("Magie"), tr("Piège")};
    const QStringList infoList = {carte.nom, genreList.at(carte.genre),
                                 tr("Niveau ") + carte.niveau,
                                 tr("Attaque: ") + carte.atk,
                                 tr("Défense") + carte.def};

    for(int i=0; i<INFOLABEL_MAX; i++)
    {
        tabInfoLabel[i] = new QLabel(infoList.at(i));
    }

  //  QVBoxLayout *info = new QVBoxLayout;
    QPixmap *image = new QPixmap(carte.image);
    QLabel *imageLabel = new QLabel;
    imageLabel->setPixmap(*image);

  //  info->addWidget();



    mainLayout->addWidget(imageLabel);








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
