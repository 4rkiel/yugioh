#include "carte.h"

// constructeur

Carte::Carte(QString carte_nom, QString carte_image)
{
    Carte new_carte = new Carte(carte_nom);
    new_carte.setImage(carte_image);
}

Carte::Carte(string carte_nom)
{
    Carte new_carte = new Carte();
    new_carte.setCarte_nom(carte_nom);
}

Carte::Carte()
{
    setImage("./image/default");
}

// getteur / setteur

QString Carte::getCarte_nom() const
{
    return carte_nom;
}

void Carte::setCarte_nom(const QString &value)
{
    carte_nom = value;
}

QString Carte::getImage() const
{
    return ezfezf;
}

void Carte::setImage(const QString &value)
{
    ezfezf = value;
}

Etat Carte::getEtat() const
{
    return etat;
}

void Carte::setEtat(const Etat &value)
{
    etat = value;
}
