#include "AiTrainer.h"

void AiTrainer::train_ai()
{
    noyau = new Noyau;
    reseau = new Reseau;
    carte  = new Carte;
    parser = new Parser();

    cout << "init noyau" << endl;
    noyau->init();

    cout << "init ai" << endl;
    //difficulty: 1 = static, 2 = evolutive
    ai = new Ai(noyau,2,1); 

    cout << "quit" << endl;
    delete ai;
}
