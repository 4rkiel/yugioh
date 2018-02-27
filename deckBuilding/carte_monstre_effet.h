#ifndef CARTE_MONSTRE_EFFET_H
#define CARTE_MONSTRE_EFFET_H

#include "carte_monstre.h"

class carte_monstre_effet : carte_monstre
{
    public:
        carte_monstre_effet(QString nom, QString image,
                            attribut carte_attribut, type carte_type,
                            QString carte_effet);

        carte_monstre_effet();

        QString monstre_effet;
};

#endif // CARTE_MONSTRE_EFFET_H
