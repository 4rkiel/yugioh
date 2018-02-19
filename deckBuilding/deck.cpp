#include "deck.h"
#include <iostream>
#include <fstream>

using namespace std;

deck::deck(file fichier)
{
    ifstream iFile(fichier, ios::in);
    if(iFile)
    {

        iFile.close();
    }



}

deck::deck()
{

}

