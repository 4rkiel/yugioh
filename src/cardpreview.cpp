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
    
    imageLabel = new QLabel;
    imageLabel -> setMinimumWidth(200);
    imageLabel -> setMaximumWidth(200);
    imageLabel -> setMinimumHeight(180);
    imageLabel -> setMaximumHeight(180);
    imageLabel->setStyleSheet("border-image: url("+carte->image+")");

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

    if((maCarte->genre  == 0) && (maCarte->sous_type != 2)){
        setStyleSheet("background: #FFF9C4;");
    } else if(maCarte->genre == 1) {
        setStyleSheet("background: #B2DFDB");
    } else if(maCarte->genre == 2){
        setStyleSheet("background: #E1BEE7;");
    } else {
        setStyleSheet("background: #9575CD;");
    }

    mainLayout->addWidget(imageLabel);
    mainLayout->addLayout(info);

    setLayout(mainLayout);
}

CardPreview::~CardPreview()
{
    delete imageLabel;
    delete info;
    delete mainLayout;
}

void CardPreview::mousePressEvent (QMouseEvent * e)
{
    if (e->button() == Qt::LeftButton || e->button() == Qt::RightButton )
    {
        emit clicked(maCarte);
    }
}
