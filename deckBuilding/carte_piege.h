#ifndef CARTE_PIEGE_H
#define CARTE_PIEGE_H

#include "carte.h"

enum type
{
    CONTINUE,
    CONTRE,
    DEFAULT
};

class carte_piege : Carte
{
    public:
        carte_piege();
        type carte_type = DEFAULT;
        QString carte_effet;
};

#endif // CARTE_PIEGE_H
