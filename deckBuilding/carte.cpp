#include "carte.h"

// constructeur

Carte::Carte(QString nom, QString image)
{
    carte_image = image;
    carte_nom = nom;
}

Carte::Carte(QString nom)
{
    carte_image = "./image/default";
    carte_nom = nom;
}

Carte::Carte()
{
    carte_image = "./image/default";
}
