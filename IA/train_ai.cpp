#include <iostream>
#include "../inc/ai.h"

int main()
{
    cout << "init" << endl;
    Ai * easy_ai = new Ai(1); //easy
    cout << "delete" << endl;
    delete easy_ai;
    cout << "quit" << endl;
}
