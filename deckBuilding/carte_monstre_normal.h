#ifndef CARTE_MONSTRE_NORMAL_H
#define CARTE_MONSTRE_NORMAL_H

#include "carte_monstre.h"

class carte_monstre_normal : carte_monstre
{
    public:
        carte_monstre_normal(QString carte_nom, QString carte_image,
                             attribut carte_attribut, type carte_monstre,
                             QString description);

        QString monstre_description;
};

#endif // CARTE_MONSTRE_NORMAL_H
