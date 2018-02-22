#ifndef CARTE_H
#define CARTE_H

enum attribut
{
    TENEBRE,
    LUMIERE
};

enum type_
{
    NORMAL,
    FUSION,
    RITUEL,
    SYNCHRO,
    XYZ,
    LINK,
    EFFET
};

enum categorie
{
    MONSTRE,
    MAGIE,
    PIEGE
};

class carte
{
    public:
        carte(string carte_nom);
        carte();

        string carte_nom;
        string carte_description;

        attribut carte_attribut;
};

#endif // CARTE_H
