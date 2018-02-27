#ifndef CARTE_MAGIE_H
#define CARTE_MAGIE_H

#include "carte.h"

enum type
{
    CONTINUE,
    EQUIPEMENT,
    TERRAIN,
    DEFAULT
};

class carte_magie : Carte
{
    public:
        carte_magie();

        type carte_type = DEFAULT;
        QString carte_effet;
};

#endif // CARTE_MAGIE_H
