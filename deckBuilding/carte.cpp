#include "carte.h"

// constructeur

Carte::Carte(QString nom, QString image)
{
    setImage("./image/default");
    setCarte_nom(nom);
    setImage(image);
}

Carte::Carte(string nom)
{
    setImage("./image/default");
    setCarte_nom(nom);
}

Carte::Carte()
{
    setImage("./image/default");
}
