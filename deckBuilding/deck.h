#ifndef DECK_H
#define DECK_H

#include <vector>

class deck
{
    public:
        deck(file fichier);
        deck();
        ~deck();

        melanger();

    protected:
        addCarte(carte cardName);

    private:
         vector<carte> bibliotheque;

};

#endif // DECK_H
