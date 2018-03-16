#include "essai.h"

Essai::Essai(QWidget *parent)
    : QMainWindow(parent)
{

    terrain_moi = new std::vector<Carte*>();
    terrain_adv = new std::vector<Carte*>();

    int i;
    for(i=0;i<5;i++)
    {
        terrain_moi->push_back(new Carte(-1,-1));
        terrain_adv->push_back(new Carte(-1,-1));
    }
    std::cout << "size :" << terrain_moi->size() << std::endl;
    d1 = new std::vector<Carte*>();
    d2 = new std::vector<Carte*>();

    d1->push_back(new Carte(1000,100));
    d1->push_back(new Carte(200,100));
    d1->push_back(new Carte(300,100));
    d1->push_back(new Carte(400,100));
    d1->push_back(new Carte(500,100));


    d2->push_back(new Carte(200,100));
    d2->push_back(new Carte(400,100));
    d2->push_back(new Carte(600,100));
    d2->push_back(new Carte(800,100));
    d2->push_back(new Carte(1000,100));

    main1= new std::vector<Carte *>();
    main2= new std::vector<Carte *>();

    piocher(2);
   std::cout << "size deck " << d1->size() << std::endl;
    std::cout << main1->at(0)->atk << std::endl;
    std::cout << main1->at(1)->atk << std::endl;
    std::cout << d1->front()->atk << std::endl;

   poser(0,1,false);

    // std::cout << "what" << main1->at(0)->atk << std::endl;
    poser(0,2,false);
 //std::cout << "euh2 ?" << std::endl;
    //std::cout << "yolo" << terrain_moi->at(1)->atk << std::endl;
adversaire_piocher(2);
adversaire_poser(0,1,false);
std::cout << "MAIN:" << main2->size() << std::endl;
adversaire_poser(0,2,false);
std::cout << "MAIN:" << main2->size() << std::endl;
    attaquer(1,2);
        std::cout << foeLife << std::endl;
       std::cout << "normalement j'affiche ça" << terrain_adv->at(2)->atk  << std::endl;

}

void Essai::piocher(int n)
{
    int i;
    for(i=0;i<n;i++)
    {
            Carte* debut = d1->front();
            main1->push_back(debut);
            enlever_i(&d1,0);
    }
    return;
}

void Essai::poser(int main_x, int terrain_x, bool def)
{
       terrain_moi->at(terrain_x)=main1->at(main_x);
       terrain_moi->at(terrain_x)->pos=def;
       enlever_i(&main1,main_x);
}

void Essai::adversaire_poser(int main_x,int terrain_x, bool def)
{
    terrain_adv->at(terrain_x)=main2->at(main_x);
    terrain_adv->at(terrain_x)->pos=def;

    enlever_i(&main2,main_x);
}

void Essai::poser(int sac1_x, int sac2_x, int main_x, int terrain_x, bool def)
{
  detruire_moi(sac1_x);
   detruire_moi(sac2_x);
   terrain_moi->at(terrain_x) = main1->at(main_x);
   main1->erase(main1->begin()+main_x-1);

}

void Essai::adversaire_piocher(int n)
{
    int i;
    for(i=0;i<n;i++)
    {
            Carte* debut = d2->front();
            main2->push_back(debut);
            enlever_i(&d2,0);
    }
    return;
}


void Essai::attaquer(int moi_x, int adversaire_x)
{
    if(adversaire_x==-1)
        std::cout << "You're already dead." << std::endl;
    else
    {
           if(terrain_moi->at(moi_x)->atk > terrain_adv->at(adversaire_x)->def)
           {

                foeLife = foeLife - (terrain_moi->at(moi_x)->atk - terrain_adv->at(adversaire_x)->def);
                detruire_adversaire(adversaire_x);

           }
           else
                  return;
    }
}

void Essai::se_faire_attaquer(int adversaire_x,int moi_x)
{
    if(moi_x==-1)
        std::cout << "You're already dead." << std::endl;
    else
    {
           if(terrain_adv->at(adversaire_x)->atk > terrain_moi->at(moi_x)->def)
           {

                selfLife = selfLife - (terrain_adv->at(adversaire_x)->atk - terrain_moi->at(moi_x)->def);
                detruire_adversaire(adversaire_x);

           }
           else
                  return;
    }
}
void Essai::switch_position(int terrain_x)
{
    terrain_moi->at(terrain_x)->pos = !(terrain_moi->at(terrain_x)->pos);
}

void Essai::switch_position_adv(int terrain_x)
{
    terrain_adv->at(terrain_x)->pos = !(terrain_adv->at(terrain_x)->pos);
}

void Essai::detruire_moi(int x)
{
       terrain_moi->at(x) = new Carte(-1,-1);
}

void Essai::detruire_adversaire(int x)
{
    terrain_adv->at(x) = new Carte(-1,-1);
}

void Essai::enlever_i(std::vector<Carte *> **vect, int i)
{
    std::vector<Carte *>* res = new std::vector<Carte *>();
    if((*vect)->size()==1)
    {
        *vect = res;
        return;
    }
   int j;
   for(j=0;j<i;j++)
   {
      res->push_back((*vect)->at(j));
   }
   for(j=i+1;j<(*vect)->size();j++)
   {
        res->push_back((*vect)->at(j));
   }
    *vect = res;
}

void Essai::phase_suivante()
{
    if(phase==5)
        phase=1;
    else
        phase++;
}


Carte::Carte(int a,int d)
{
    atk=a;
    def=d;
}

Essai::~Essai()
{
    delete(Essai::terrain_adv);
    delete(Essai::terrain_moi);
    delete(Essai::main1);
    delete(Essai::main2);
    delete(Essai::d1);
    delete(Essai::d2);
}