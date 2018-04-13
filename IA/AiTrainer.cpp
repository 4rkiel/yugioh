#include "AiTrainer.h"

void AiTrainer::train_ai()
{
    noyau = new Noyau;
    reseau = new Reseau;
    carte  = new Carte;
    parser = new Parser();
    cout << "init" << endl;
    //difficulty: 1 = static, 2 = evolutive
    ai = new Ai(noyau,2); 
    cout << "delete" << endl;
    delete ai;
    cout << "quit" << endl;
}
