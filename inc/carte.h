#ifndef CARTE_H
#define CARTE_H

#include<QString>
#include <QWidget>
#include <iostream>
enum Etat
{
    RECTO,
    VERSO
};

enum Attribut
{
    LUMIERE,
    TENEBRE,
    TERRE,
    EAU,
    FEU,
    VENT,
    DIVIN
};

enum Type
{
    AQUA,
    BETE,
    BETE_AILEE,
    BETE_DIVINE,
    BETE_GUERRIER,
    DEMON,
    DINOSAURE,
    DRAGON,
    ELFE,
    GUERRIER,
    INSECTE,
    MACHINE,
    MAGICIEN,
    PLANTE,
    POISSON,
    PYRO,
    ROCHER,
    REPTILE,
    SERPENT_DE_MER,
    TONNERRE,
    WYRM,
    ZOMBIE
 };

//FORMULE DES POSITIONS : (x+75)%150


class Carte : public QWidget
{
public:
    int id;
    int atk;
    int default_atk;
    int def;
    int default_def;
    bool pos;
    QString nom;
    QString image;
    Etat etat;
    int genre; // (magie 1 ,piege 2,monstre 0)
    Type type; // (rocher,démon,..)
    int sous_type; // (fusion,continue,...)
    Attribut attribut; // (lumière,feu,...)
    QString description;
    int niveau;

    static int correspondant(int position);
    //Effet effet; comment implenter ça ??
    int effet;
    int set;
    int position_deck;
    int position_terrain;
    Carte(int a,int d);
    Carte();
    Carte(int id,int atk,int def,bool pos,QString nom,QString image,Etat etat,int genre,Type type,int sous_type,Attribut attribut,QString description,int niveau,int effet,int set,int position_deck,int position_terrain);
    Carte * copie();
    void afficher_infos();
};

#endif // CARTE_H
