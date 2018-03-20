#include "carte_monstre.h"

carte_monstre::carte_monstre(QString carte_nom, QString carte_image,
                             attribut carte_attribut, type carte_type)
{
    Carte(carte_nom, carte_image);
    monstre_attribut = carte_attribut;
    monstre_type = carte_type;
}

carte_monstre::carte_monstre()
{

}

carte_monstre::~carte_monstre()
{

}

