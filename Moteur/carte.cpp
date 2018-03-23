#include "carte.h"

Carte::Carte()
{
    id = 0;
    atk=0;
    default_atk=0;
    def= 0;
    default_def=0;
    pos = false;
    nom="";
    image="";
    etat=VERSO;
    genre=-1; // (magie 1 ,piege 2,monstre 0)
    type=ROCHER; // (rocher,démon,..)
    sous_type=0; // (fusion,continue,...)
    attribut=LUMIERE; // (lumière,feu,...)
    description="";
    niveau=0;
    set=-1;
    position_deck=0;
    position_terrain=0;
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
