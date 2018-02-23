#ifndef CARTE_H
#define CARTE_H

#include<QString>

enum Etat
{
    RECTO,
    VERSO
};

class Carte
{
    public:

        Carte(QString nom, QString image);
        Carte(QString nom);
        Carte();

        QString carte_nom;
        QString carte_image;

        Etat carte_etat; // recto / verso
};

#endif // CARTE_H
