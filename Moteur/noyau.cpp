#include "noyau.h"
#include "essai.h"
Noyau::Noyau()
{
    terrain = new std::vector<Carte *>();
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
   std::cout << "size deck " << d1->size() << std::endl;
    std::cout << d1->front()->atk << std::endl;

/*
    attaquer(1,2);*/
        std::cout << foeLife << std::endl;
     //  std::cout << "normalement j'affiche ça" << terrain_adv->at(2)->atk  << std::endl;

}


// initialise le réseau
void Noyau::setReseau(bool b)
{
    if(b)
    {
        std::cout << "je crée le reseau" << std::endl;
        online=true;
        res=new Reseau();
        connect(this,SIGNAL(emit_go()),res,SLOT(go()));
        connect(this,SIGNAL(emit_mondieu()),res,SLOT(mondieu()));
        connect(this,SIGNAL(emit_send()),res,SLOT(send()));
        connect(this,SIGNAL(emit_attaque()),res,SLOT(attaque()));
        connect(this,SIGNAL(je_pioche()),res,SLOT(piocher()));
        connect(res,SIGNAL(a_parser(QString)),this,SLOT(traiter(QString)));
        connect(this,SIGNAL(je_pose(int,int,bool)),res,SLOT(poser(int,int,bool)));
    }
}

void Noyau::piocher(int x)
{
    int position = Carte::correspondant(x);
    if(position>75)
    {
        std::cout << "le traitement du piochage allié en cours " << std::endl;
        d1->front()->position_terrain = perfect_position(0);
        terrain->push_back(d1->front());
        enlever_i(&d1,0);
        //prevenir le voisin
        emit je_pioche();
    }
    else
    {
        std::cout << "le traitement du piochage adverse en cours " << std::endl;
        d2->front()->position_terrain = perfect_position(1);
        terrain->push_back(d2->front());
        enlever_i(&d2,0);
    }
}

//poser la carte
void Noyau::poser(int main_x, int terrain_x, bool def)
{
    Carte * la_carte;
    if(main_x < 75)
    {
        std::cout << "je traite mon posage" << std::endl;
        la_carte = trouver(main_x);
        la_carte->position_terrain=terrain_x;
        la_carte->def = def;
        emit je_pose(main_x,terrain_x,def);
    }
    else
    {
        std::cout << "je traite le posage adverse" << std::endl;
        la_carte = trouver(main_x);
        la_carte->position_terrain=terrain_x;
         la_carte->def = def;

    }
}

//trouve la carte qui a la position x
Carte * Noyau::trouver(int x)
{
    if(terrain->size()==0)
        return NULL;
    int i;
    for(i=0;i<terrain->size();i++)
    {
        if(terrain->at(i)->position_terrain == x)
            return terrain->at(i);
    }
    return NULL;
}

//permet de trouver la position parfaite dans la main
int Noyau::perfect_position(int zone)
{

    int begin_position,i,min=151,current_position;
    if(zone==0)
   {
        begin_position=14;
        if(terrain->size()==0)
               return begin_position;
        for(i=0;i<terrain->size();i++)
        {
             current_position = terrain->at(i)->position_terrain;
             if((current_position > 13) && (current_position < 75))
             {
                 if(min>current_position)
                        min = current_position;
              }
        }

    }
    else
    {
        begin_position=89;
        if(terrain->size()==0)
               return begin_position;
        for(i=0;i<terrain->size();i++)
        {
             current_position = terrain->at(i)->position_terrain;
             if((current_position > 88) && (current_position < 150))
             {
                 if(min>current_position)
                        min = current_position;
              }
        }
    }
    return min;
}

void Noyau::attaquer(int attaquant_x, int adversaire_x)
{
    //c'est moi qui attaque
    if(attaquant_x < 75)
    {
        Carte * atk = trouver(attaquant_x);
        if(adversaire_x == -1)
        {
            foeLife = foeLife - atk->atk;
        }
        else
        {
                 Carte * def = trouver(adversaire_x);
                 //le monstre est en position de défense
                if(def->pos)
                {
                    if(atk->atk > def->def)
                    {
                        detruire(adversaire_x);
                    }
                    else if(atk->atk < def->def)
                    {
                        selfLife = selfLife - (def->def - atk->atk);
                    }
                }
                else
                {
                    if(atk->atk > def->atk)
                    {
                        detruire(adversaire_x);
                        foeLife = foeLife - (atk->atk - def->atk);
                    }
                    else if(atk->atk < def->def)
                    {
                        detruire(attaquant_x);
                        selfLife = selfLife - (def->atk - atk->atk);
                    }
                    else
                    {
                        detruire(adversaire_x);
                        detruire(attaquant_x);
                    }
                }
        }
        emit j_attaque(attaquant_x,adversaire_x);
    }
    //c'est l'autre qui attaque
    else
    {
        Carte * atk = trouver(attaquant_x);
        if(adversaire_x == -1)
        {
           selfLife = selfLife - atk->atk;
        }
        else
        {
                 Carte * def = trouver(adversaire_x);
                 //le monstre est en position de défense
                if(def->pos)
                {
                    if(atk->atk > def->def)
                    {
                        detruire(adversaire_x);
                    }
                    else if(atk->atk < def->def)
                    {
                        foeLife = foeLife - (def->def - atk->atk);
                    }
                }
                else
                {
                    if(atk->atk > def->atk)
                    {
                        detruire(adversaire_x);
                        selfLife = selfLife - (atk->atk - def->atk);
                    }
                    else if(atk->atk < def->def)
                    {
                        detruire(attaquant_x);
                        foeLife = foeLife - (def->atk - atk->atk);
                    }
                    else
                    {
                       detruire(attaquant_x);
                       detruire(adversaire_x);
                    }
                }
        }
    }
}


void Noyau::enlever_i(std::vector<Carte *>**vect,int i)
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


void Noyau::detruire(int x)
{
    enlever_x(&terrain,x);
}

/*
void Noyau::poser(int sac1_x, int sac2_x, int main_x, int terrain_x, bool def)
{
  detruire_moi(sac1_x);
   detruire_moi(sac2_x);
   terrain_moi->at(terrain_x) = main1->at(main_x);
   main1->erase(main1->begin()+main_x-1);

}

void Noyau::switch_position(int terrain_x)
{
    terrain_moi->at(terrain_x)->pos = !(terrain_moi->at(terrain_x)->pos);
}

void Noyau::switch_position_adv(int terrain_x)
{
    terrain_adv->at(terrain_x)->pos = !(terrain_adv->at(terrain_x)->pos);
}

void Noyau::detruire_moi(int x)
{
       terrain_moi->at(x) = new Carte(-1,-1);
}

void Noyau::detruire_adversaire(int x)
{
    terrain_adv->at(x) = new Carte(-1,-1);
}
*/
void Noyau::enlever_x(std::vector<Carte *> **vect, int x)
{

    std::vector<Carte *> * resultat = new std::vector<Carte *>();
    if((*vect)->size()==1)
    {
       * vect = resultat;
        return;
    }
    int i;
    for(i=0;i<(*vect)->size();i++)
    {
        if((*vect)->at(i)->position_terrain != x)
            resultat->push_back((*vect)->at(i));
        else
        {
            (*vect)->at(i)->position_terrain = -1;
            cimetiere.push_back((*vect)->at(i));
        }
    }
    *vect = resultat;

}

void Noyau::phase_suivante()
{
    if(phase==5)
        phase=1;
    else
        phase++;
}


void Noyau::go()
{
    emit Noyau::emit_go();
}

void Noyau::mondieu()
{
emit Noyau::emit_mondieu();
}

void Noyau::send()
{
    emit Noyau::emit_send();
}

void Noyau::attaque()
{
    emit Noyau::emit_attaque();
}

void Noyau::traiter(QString s)
{
    std::cout << "S:" << s.toStdString() << std::endl;
    if(s.compare(QString("apioche"))==0)
    {
        std::cout << "oui l'adversaire pioche" << std::endl;
        piocher(100);
    }
    else if(s.compare(QString("jpioche"))==0)
    {
        std::cout << "oui je pioche" << std::endl;
        piocher(1);
    }
    else if(s[0]=='p' && s[1]=='/')
    {
        int valeur;
        std::vector<int> * les_valeurs = new std::vector<int>();
        char * arg = new char[s.length()+1];
           std::strcpy(arg,s.toStdString().c_str());
         char * parcourir = std::strtok(arg,"/");
         std::string vrai;
         if(parcourir!=NULL)
          vrai = parcourir;
         while(parcourir!=NULL)
         {
             std::cout << "parc" << parcourir << " vrai:"<< vrai << std::endl;
             if(std::strcmp(parcourir,"p")!=0)
             {
                std::cout << "je traite l'int" << std::endl;
                valeur = atoi(parcourir);
                std::cout << "la valeur:" << valeur << std::endl;
                les_valeurs->push_back(valeur);
             }
             parcourir = std::strtok(NULL,"/");


             if(parcourir!=NULL)
            vrai = parcourir;
          }
         std::cout << "size :" << les_valeurs->size() << std::endl;
         bool le_bool = (les_valeurs->at(2)==1);
         poser(les_valeurs->at(0),les_valeurs->at(1),le_bool);

            delete(arg);
         std::cout << "j'ai fini de parser" << std::endl;
    }
    else if(s.compare(QString("etat"))==0)
    {
           std::cout << "terrain_size:" << terrain->size() << std::endl;
            int i;
            for(i=0;i<terrain->size();i++)
            {
                std::cout << "atk:" << terrain->at(i)->atk << " terrain_position" << terrain->at(i)->position_terrain << std::endl;
            }
            std::cout << "ma vie :" << selfLife << " vie adverse :" << foeLife << std::endl;
    }

}


