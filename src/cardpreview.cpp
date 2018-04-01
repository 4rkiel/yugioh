#include "../inc/cardpreview.h"

CardPreview::CardPreview(const Carte *carte)
{
    mainLayout = new QHBoxLayout;

    const QStringList genreList = {tr("Monstre"), tr("Magie"), tr("Piège")};
    const QStringList infoList = {carte->nom, genreList.at(carte->genre),
                                 tr("Niveau: ") + QString::number(carte->niveau),
                                 tr("Attaque: ") + QString::number(carte->atk),
                                 tr("Défense: ") + QString::number(carte->def)};

    QVBoxLayout *info = new QVBoxLayout;
    QPixmap *image = new QPixmap(carte->image);
    qDebug() << carte->image;
    QLabel *imageLabel = new QLabel;
    imageLabel->setPixmap(*image);
    imageLabel->setSizeIncrement(QSizePolicy::Maximum, QSizePolicy::Maximum);

    for(int i=0; i<INFOLABEL_MAX; i++)
    {
        tabInfoLabel[i] = new QLabel(infoList.at(i));
        info->addWidget(tabInfoLabel[i]);
        if((i == GENRE && tabInfoLabel[GENRE]->text() != genreList.at(0)))
            break; // si la carte n'est pas un monstre, on affiche pas ses stats
    }

    mainLayout->addWidget(imageLabel);
    mainLayout->addLayout(info);

    setLayout(mainLayout);
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
