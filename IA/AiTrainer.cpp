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
    //difficulty: 1 = static, 2 = evolutive1
    //joueur 1
    ai_main_1 = new Ai_main(noyau,2,1); 
    ai_battle_1 = new Ai_battle(noyau,2,1); 
    //joueur 2
    ai_main_2 = new Ai_main(noyau,2,2); 
    ai_battle_2 = new Ai_battle(noyau,2,2); 

    cout << "play ai_main_1" << endl;
    ai_main_1->play();
    cout << "ai_main_1 played" << endl;

    cout << "quit" << endl;
    delete ai_main_1;
    delete ai_battle_1;
    delete ai_main_2;
    delete ai_battle_2;
}
