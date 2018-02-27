#ifndef CARTE_H
#define CARTE_H

#include<QString>

enum Etat
{
    RECTO,
    VERSO
};

// relation carte à carte
// ex: une carte qui specifie d'ajouter a sa main une carte d'archetype dragon blanc
enum Archetype
{
    DRAGON_BLANC,
    DRAGON_NOIR,
    MAGICIEN_SOMBRE,
    EXODIA,
    NONE // default
};

class Carte
{
    public:

        Carte(QString nom, QString image);
        Carte(QString nom);
        Carte();

        QString carte_nom;
        QString carte_image;

        Archetype carte_archetype = NONE;
        Etat carte_etat; // recto / verso
};

#endif // CARTE_H
