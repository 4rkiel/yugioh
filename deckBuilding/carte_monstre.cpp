#include "carte_monstre.h"

carte_Monstre::carte_Monstre(QString carte_nom, QString carte_image,
                             monstre_atribut carte_attribut, monstre_type carte_type)
{
    super(nom, image);
    monstre_attribut = carte_attribut;
    monstre_type = carte_attribut;
}

