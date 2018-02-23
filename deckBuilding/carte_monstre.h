#ifndef CARTE_MONSTRE_H
#define CARTE_MONSTRE_H

enum attribut
{
    LUMIERE,
    TENEBRE
};

enum type
{
    GUERRIER,
    MAGICIEN,
    DRAGON,
    DEMON
};

class carte_monstre : carte
{
    public:
        carte_monstre(QString carte_nom, QString carte_image,
            attribut carte_attribut, type carte_type);
        ~carte_monstre();

        attribut monstre_attribut;
        type monstre_type;
};

#endif // CARTE_MONSTRE_H
