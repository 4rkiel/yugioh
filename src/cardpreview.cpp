#include "../inc/cardpreview.h"

CardPreview::CardPreview(Carte *carte){

    mainLayout = new QHBoxLayout;
    mainLayout -> setMargin(0);
    mainLayout -> setSpacing(0);
    mainLayout -> setContentsMargins(0,0,0,0);
 
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

    
    info = new QVBoxLayout;
    info -> setMargin(0);
    info -> setSpacing(0);
    info -> setContentsMargins(0,0,0,0);
    
    image = new QPixmap(carte->image);
    *image = image->scaled (QSize(200, 180), Qt::KeepAspectRatio);
    qDebug() << carte->image;
    imageLabel = new QLabel;
    imageLabel->setPixmap(*image);
    imageLabel->setSizeIncrement(QSizePolicy::Maximum, QSizePolicy::Maximum);

    for(int i=0; i<INFOLABEL_MAX; i++){

        tabInfoLabel[i] = new QLabel(infoList.at(i));
        tabInfoLabel[i]->setWordWrap(true);
        info->addWidget(tabInfoLabel[i]);

        // si c'est un monstre
        
        if((i == GENRE && tabInfoLabel[GENRE]->text() == genreList.at(0))){
            
            tabInfoLabel[i] -> setText(
                tabInfoLabel[i]->text() + " / " + sousGenreList.at(carte->sous_type)
            );

        } else if (i == GENRE){

            tabInfoLabel[i]->setText(
                tabInfoLabel[i]->text() + " / " + attrList.at(carte->attribut)
            );

            break; // si la carte n'est pas un monstre, on affiche pas ses stats
        }
    }

    if(tabInfoLabel[GENRE]->text() == genreList.at(0)){
        setStyleSheet("background: #FFC107;");
    } else if(tabInfoLabel[GENRE]->text() == genreList.at(1)) {
        setStyleSheet("background: #00BCD4;");
    } else {
        setStyleSheet("background: #B39DDB;");
    }

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
