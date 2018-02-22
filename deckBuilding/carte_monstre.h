#ifndef CARTE_MONSTRE_H
#define CARTE_MONSTRE_H

enum monstre_attribut
{
    LUMIERE,
    TENEBRE
};

enum monstre_type
{
    GUERRIER,
    MAGICIEN,
    DRAGON,
    DEMON
};

class carte_monstre : carte
{
    public:
        carte_monstre();
        ~carte_monstre();
};

#endif // CARTE_MONSTRE_H
