#include "../inc/cardpreview.h"

CardPreview::CardPreview(Carte *carte)
{
    mainLayout = new QHBoxLayout;

    maCarte = carte;

    const QStringList genreList = {tr("Monstre"), tr("Magie"), tr("Piège")};
    const QStringList sousGenreList = {tr("Effet"), tr("Normal"), tr("Fusion"),
                                       tr("Toon"), tr("Rituel")};
    const QStringList attrList = {tr("Normal"), tr("Continue"), tr("Equipement"),
                                       tr("Jeu-Rapide"), tr("Rituel"), tr("Terrain")};
    const QStringList infoList = {carte->nom, genreList.at(carte->genre),
                                 tr("Niveau: ") + QString::number(carte->niveau),
                                 tr("Attaque: ") + QString::number(carte->atk),
                                 tr("Défense: ") + QString::number(carte->def)};

    QVBoxLayout *info = new QVBoxLayout;
    QPixmap *image = new QPixmap(carte->image);
    *image = image->scaled (QSize(200, 180), Qt::KeepAspectRatio);
    qDebug() << carte->image;
    QLabel *imageLabel = new QLabel;
    imageLabel->setPixmap(*image);
    imageLabel->setSizeIncrement(QSizePolicy::Maximum, QSizePolicy::Maximum);

    for(int i=0; i<INFOLABEL_MAX; i++)
    {
        tabInfoLabel[i] = new QLabel(infoList.at(i));
        tabInfoLabel[i]->setWordWrap(true);
        info->addWidget(tabInfoLabel[i]);

        if((i == GENRE && tabInfoLabel[GENRE]->text() == genreList.at(0)))
            // si c'est un monstre
            tabInfoLabel[i]->setText(tabInfoLabel[i]->text() + " / " + sousGenreList.at(carte->sous_type));

        else if(i == GENRE)
        {
            tabInfoLabel[i]->setText(tabInfoLabel[i]->text() + " / " + attrList.at(carte->attribut));
            break; // si la carte n'est pas un monstre, on affiche pas ses stats
        }
    }

    if(tabInfoLabel[GENRE]->text() == genreList.at(0))
    {
       // setStyleSheet("background: red");
        setObjectName("Monstre");
    }
    else if(tabInfoLabel[GENRE]->text() == genreList.at(1))
        setObjectName("Magie");
    else
        setObjectName("Piege");

    mainLayout->addWidget(imageLabel);
    mainLayout->addLayout(info);

    setLayout(mainLayout);
}

void CardPreview::mousePressEvent (QMouseEvent * e)
{
    if (e->button() == Qt::LeftButton || e->button() == Qt::RightButton )
    {
        emit clicked(maCarte);
    }
}
