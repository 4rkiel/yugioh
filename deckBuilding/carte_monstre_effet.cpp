#include "carte_monstre_effet.h"

carte_monstre_effet::carte_monstre_effet(QString nom, QString image, attribut carte_attribut, type carte_type, QString carte_effet)
{
    carte_monstre(nom,  image,  carte_attribut, carte_type);
    monstre_effet = carte_effet;
}

carte_monstre_effet::carte_monstre_effet()
{
    carte_monstre();
}

