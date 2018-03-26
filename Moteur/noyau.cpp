#include "noyau.h"
#include "parser.h"

Noyau::Noyau()
{
    terrain = new std::vector<Carte *>();
    cimetiere1 = new std::vector<Carte *>();
    cimetiere2 = new std::vector<Carte *>();
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
        connect(this,SIGNAL(j_attaque(int,int)),res,SLOT(attaquer(int,int)));
        connect(this,SIGNAL(je_gagne()),res,SLOT(gagne()));
        connect(this,SIGNAL(e_deck(int)),res,SLOT(env_deck(int)));
        connect(this,SIGNAL(switch_pos(int)),res,SLOT(change_pos(int)));
    }
}

//charge le deck qui te correspond
void Noyau::chargerDeck(int x)
{
    Parser * yolo = new Parser();
    d1 = yolo->rechercher_set(x);
    emit e_deck(x);
}

//charge le deck de l'adversaire
void Noyau::deckAdverse(int x)
{
    Parser * yolo = new Parser();
    d2 = yolo->rechercher_set(x);
}

//gère le piochage
void Noyau::piocher(int x)
{
    int position = Carte::correspondant(x);
    //si c'est moi qui pioche
    if(position>75)
    {
        //on met la position de la carte qui est au sommet du deck là où il faut dans la main
        //on place la carte dans au bon endroit
        //on enleve la carte du deck

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
    if(min==151)
        min = begin_position;
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
            if(foeLife <=0)
                emit je_gagne();
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
                        if(foeLife <=0)
                            emit je_gagne();
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
                        if(foeLife <=0)
                            emit je_gagne();
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
                        if(foeLife <=0)
                            emit je_gagne();
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

//detruit la carte à la position x et la place au cimetière
void Noyau::detruire(int x)
{
    enlever_x(&terrain,x);
}

//change la position (atk/def) d'une carte
void Noyau::switch_position(int terrain_x)
{
    int i;
    for(i=0;i<terrain->size();i++)
    {
        if(terrain->at(i)->position_terrain == terrain_x)
        {
            terrain->at(i)->pos = !(terrain->at(i)->pos);
            if(terrain_x<75)
                emit switch_pos(terrain_x);
            return;
        }
    }
}

//enlever la carte ayant la position x sur le terrain dans le vector donné
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
            if(x<75)
                cimetiere1->push_back((*vect)->at(i));
            else
                cimetiere2->push_back((*vect)->at(i));
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

/***************************************************************/
//FONCTION ULTIME
//ELLE GERE TOUS LES CAS D'ACTIONS
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
                std::cout << "atk:" << terrain->at(i)->atk << " terrain_position" << terrain->at(i)->position_terrain << " pos:" << (terrain->at(i)->pos ? 1 : 0) << std::endl;
            }
            std::cout << "ma vie :" << selfLife << " vie adverse :" << foeLife << std::endl;
    }
    else if(s.startsWith(QString("deck:")))
    {
        char * arg = new char[s.length()+1];
           std::strcpy(arg,s.toStdString().c_str());
         char * parcourir = std::strtok(arg,":");
         std::string vrai;
         if(parcourir!=NULL)
          vrai = parcourir;
         while(parcourir!=NULL)
         {
             std::cout << "parc" << parcourir << " vrai:"<< vrai << std::endl;
             parcourir = std::strtok(NULL,"/");
             if(parcourir!=NULL)
            vrai = parcourir;
          }
         delete(arg);
         chargerDeck(atoi(vrai.c_str()));
    }
    else if(s.startsWith("a/"))
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
             if(std::strcmp(parcourir,"a")!=0)
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
         attaquer(les_valeurs->at(0),les_valeurs->at(1));

            delete(arg);
         std::cout << "j'ai fini de parser" << std::endl;
    }
    else if(s.compare(QString::fromStdString("g"))==0)
    {
        std::cout << "j'ai perdu" << std::endl;
    }
    else if(s.startsWith("d/"))
    {
        int valeur;
        char * arg = new char[s.length()+1];
           std::strcpy(arg,s.toStdString().c_str());
         char * parcourir = std::strtok(arg,"/");
         std::string vrai;
         if(parcourir!=NULL)
          vrai = parcourir;
         while(parcourir!=NULL)
         {
             std::cout << "parc" << parcourir << " vrai:"<< vrai << std::endl;
             parcourir = std::strtok(NULL,"/");
             if(parcourir!=NULL)
            vrai = parcourir;
          }
         delete(arg);
         valeur = atoi(vrai.c_str());
         deckAdverse(valeur);
    }
    else if(s.startsWith("swap/"))
    {
        int valeur;
        char * arg = new char[s.length()+1];
           std::strcpy(arg,s.toStdString().c_str());
         char * parcourir = std::strtok(arg,"/");
         std::string vrai;
         if(parcourir!=NULL)
          vrai = parcourir;
         while(parcourir!=NULL)
         {
             std::cout << "parc" << parcourir << " vrai:"<< vrai << std::endl;
             parcourir = std::strtok(NULL,"/");
             if(parcourir!=NULL)
            vrai = parcourir;
          }
         delete(arg);
         valeur = atoi(vrai.c_str());
         switch_position(valeur);
    }

}
/******************************************/





