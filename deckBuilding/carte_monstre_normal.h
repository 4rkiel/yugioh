#ifndef CARTE_MONSTRE_NORMAL_H
#define CARTE_MONSTRE_NORMAL_H


class carte_monstre_normal : carte_monstre
{
    public:
        carte_monstre_normal(QString carte_nom, QString carte_image,
                             monstre_atribut attribut, monstre_type type,
                             QString description);

        QString monstre_description;
};

#endif // CARTE_MONSTRE_NORMAL_H
