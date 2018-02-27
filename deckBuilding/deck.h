#ifndef DECK_H
#define DECK_H

#include "carte.h"
#include <vector>
#include <QFile>

class deck
{
    public:
        deck(QFile fichier);
        deck();
        ~deck();

        bool melanger();
        bool addCarte(Carte cardName);
        std::vector<Carte> bibliotheque;

};

#endif // DECK_H
