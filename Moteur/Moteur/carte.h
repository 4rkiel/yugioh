#ifndef CARTE_H
#define CARTE_H

#include<QString>
#include <QWidget>
enum Etat
{
    RECTO,
    VERSO
};

enum Archetype
{
    DRAGON_BLANC,
    DRAGON_NOIR,
    MAGICIEN_SOMBRE,
    EXODIA,
    NONE // default
};

enum Attribut
{
    LUMIERE,
    TENEBRE
};

enum Type
{
    GUERRIER,
    MAGICIEN,
    DRAGON,
    DEMON
};

//FORMULE DES POSITIONS : (x+75)%150


class Carte : public QWidget
{
public:
    int atk;
    int default_atk;
    int def;
    int default_def;
    bool pos;
    QString nom;
    QString image;
    Archetype carte_archetype = NONE;
    Etat etat;
    int genre; // (magie,piege,monstre..)
    Type type; // (rocher,démon,..)
    int sous_type; // (fusion,continue,...)
    Attribut attribut; // (lumière,feu,...)
    QString description;

    static int correspondant(int position);
    //Effet effet; comment implenter ça ??
    int set;
    int position_deck;
    int position_terrain;
    Carte(int a,int d);
    Carte();


};

#endif // CARTE_H
