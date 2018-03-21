#include "carte.h"

Carte::Carte()
{

}

int Carte::correspondant(int position)
{
    return (position+75)%150;
}
Carte::Carte(int a,int d)
{
    atk=a;
    def=d;
}
