#include "../inc/carte.h"
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
    position_deck=-1;
    position_terrain=-1;
}

int Carte::correspondant(int position)
{
    if(position>=0)
        return (position+75)%150;
    else
        return position;
}

void Carte::afficher_infos()
{
    std::cout << "id:" << id << std::endl;
    std::cout << "atk:" << atk << std::endl;
    std::cout << "default_atk:" << default_atk << std::endl;
    std::cout << "def:" << def << std::endl;
    std::cout << "default_def:" << default_def << std::endl;
    std::cout << "pos:" << pos << std::endl;
    std::cout << "nom:" << nom.toStdString() << std::endl;
    std::cout << "image:"<< image.toStdString() << std::endl;
    std::cout << "etat:" <<  etat << std::endl;
    std::cout << "genre:" << genre << std::endl;
    std::cout << "type:" << type << std::endl;
    std::cout << "sous_type:" << sous_type << std::endl;
    std::cout << "attribut:"<< attribut << std::endl;
    std::cout << "description:" << description.toStdString() << std::endl;
    std::cout << "niveau:" << niveau << std::endl;
    std::cout << "set:"<< set << std::endl;
    std::cout << "position_deck:"<< position_deck<< std::endl;
    std::cout << "position_terrain:" << position_terrain << std::endl;
}

Carte::Carte(int a,int d)
{
    atk=a;
    def=d;
}

