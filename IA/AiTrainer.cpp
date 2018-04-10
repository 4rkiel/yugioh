#include "AiTrainer.h"
#include "../inc/ai.h"

void AiTrainer::train_ai()
{
    cout << "init" << endl;
    //difficulty: 1 = easy, 2 = medium, 3 = hard, 4 = learning
    Ai * ai = new Ai(2); 
    cout << "delete" << endl;
    delete ai;
    cout << "quit" << endl;
}
