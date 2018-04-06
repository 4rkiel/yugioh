#include <iostream>
#include "../inc/ai.h"

int main()
{
    cout << "init" << endl;
    //difficulty: 1 = easy, 2 = medium, 3 = hard, 4 = learning
    Ai * ai = new Ai(1); 
    cout << "delete" << endl;
    delete ai;
    cout << "quit" << endl;
}
