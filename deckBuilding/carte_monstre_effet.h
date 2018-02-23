#ifndef CARTE_MONSTRE_EFFET_H
#define CARTE_MONSTRE_EFFET_H

class carte_monstre_effet : carte_monstre
{
    public:
        carte_monstre_effet(QString nom, QString image,
                            monstre_atribut carte_attribut, monstre_type carte_type,
                            QString carte_effet);

        QString monstre_effet;
};

#endif // CARTE_MONSTRE_EFFET_H
