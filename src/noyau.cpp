#include "../inc/noyau.h"
#include "../inc/parser.h"
#include <chrono>
#include <thread>
Noyau::Noyau()
{
    terrain = new std::vector<Carte *>();
    cimetiere1 = new std::vector<Carte *>();
    cimetiere2 = new std::vector<Carte *>();

}

void Noyau::init()
{
    QSettings settings;
    foeLife = settings.value("lifePoints","8000").toInt();
    selfLife = foeLife;
    chargerDeck(0);
    deckAdverse(0);
    std::cout << "la taille de mon deck est : " << d1->size() << std::endl;
    //piocher(1);
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    piocher(1);
}


// initialise le réseau
// OBSOLETE depuis l'ajout du reseau dans un master
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
//pour l'instant x est un int parce que les decks (situés dans le dossier deck) respectent le regex [0-9]*.deck
//cela changera dans l'avenir certainement 
void Noyau::chargerDeck(int x)
{
Parser * yolo = new Parser();
d1 = yolo->rechercher_set(x,NULL);
emit e_deck(x);
}

//charge le deck de l'adversaire
//pour l'instant x est un int parce que les deck (situés dans le dossier deck) respectent le regex [0-9]*.deck
//cela changera dans l'avenir certainement 
void Noyau::deckAdverse(int x)
{
Parser * yolo = new Parser();
d2 = yolo->rechercher_set(x,NULL);
}

//gère le piochage
// x vaut 1 si c'est moi qui pioche sinon x vaut 76
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
    int dans_main = perfect_position(0);
    d1->front()->position_terrain = dans_main;
    terrain->push_back(d1->front());

    enlever_i(&d1,0);

    //prevenir le voisin
    emit visible(trouver(dans_main)->image,dans_main);
    std::cout << "faut piocher " << trouver(dans_main)->image.toStdString() << " là " << dans_main << std::endl;
    if(online)
    {
        emit tiens("apioche");
    }
    emit je_pioche();
    }
    else
    {
    std::cout << "le traitement du piochage adverse en cours " << std::endl;
    int dans_main = perfect_position(1);
    std::cout << "l'adversaire pose en " << dans_main << std::endl;
    d2->front()->position_terrain = dans_main;
    terrain->push_back(d2->front());
    enlever_i(&d2,0);
    emit nonvis(dans_main);
    }
}

bool Noyau::isAdv(int x){
    return (x >= 75);
}

bool Noyau::isMonst(int x){
    return ((x >= 1 && x <= 5)||(x >= 76 && x <= 80));
}

bool Noyau::isMagic(int x){
    return ((x >= 8 && x <= 12)||(x >= 83 && x <= 87));
}

bool Noyau::isHand(int x){
    return ((x >= 14 && x <= 74)||(x >= 89 && x <= 149));
}

bool Noyau::isDeck(int x){
    return ((x == 13) || (x == 82));
}

bool Noyau::isField(int x){
    return ((x == 0) || (x == 81));
}

bool Noyau::isGrave(int x){
    return ((x == 6) || (x == 75));
}

bool Noyau::isFuse(int x){
    return ((x == 7) || (x == 88));
}

void Noyau::poserAtk()
{
    //remplacer le 1 par la bonne position stp
    if(registre_0 > 6)
    poser(registre_0,perfect_terrain(0),false,true);
}

void Noyau::poserDef()
{
     if(registre_0 > 6)
    poser(registre_0,perfect_terrain(0),true,false);
}

//determine la position où poser la carte sur le terrain, zone = 0 si c'est moi qui pose sinon c'est 1
int Noyau::perfect_terrain(int zone)
{
     int begin_position;
     if(zone==0)
       {
            begin_position=1;
            if(terrain->size()==0)
                   return begin_position;
            while(trouver(begin_position)!=NULL)
                begin_position++;

        }
        else
        {
            begin_position=76;
            if(terrain->size()==0)
                   return begin_position;
            while(trouver(begin_position)!=NULL)
                begin_position++;

        }
        return begin_position;
}

void Noyau::poser_test(int x)
{
    //le if doit être mieux géré negrion
    if(!isAdv(x) && isHand(x) && trouver(x)!=NULL )
    {
        registre_0 = x;
        emit dialogue();
    }
    else if(!isAdv(x) && isMonst(x) && trouver(x)!=NULL )
    {
        switch_position(x);
        emit tiens("swap/"+x);
    }
}

//poser la carte
//prends en argument la position de la carte dans la main, la position où on veut la poser, def est vrai si on veut la poser en mode defense , vis est vrai si on veut la mettre en mode face recto
void Noyau::poser(int main_x, int terrain_x, bool def, bool vis)
{
    Carte * la_carte;
    if(main_x < 75)
    {
        std::cout << "je traite mon posage" << std::endl;
        la_carte = trouver(main_x);
        la_carte->position_terrain=terrain_x;
        la_carte->def = def;
        if(vis)
            la_carte->etat = RECTO;
        else
            la_carte->etat=VERSO;
        if(!def)
        {
            if(vis)
            {
                emit visible(la_carte->image,terrain_x);
            }
            else
            {
                emit nonvis(terrain_x);
            }
        }
        else
        {
            if(!vis)
            {
                emit defens(terrain_x);
            }
        }
        emit destruction(main_x);
        //emit je_pose(la_carte->image,main_x,terrain_x,def,vis);
        if(online)
        {
            QString message = "p/";
            std::stringstream s1;
            s1 << Carte::correspondant(main_x) << "/" << Carte::correspondant(terrain_x) << "/" << (def? 1 : 0) << "/" << (vis? 1 : 0) ;
            message.append(QString::fromStdString(s1.str()));
            emit tiens(message);

        }
    }
    else
    {
        std::cout << "je traite le posage adverse" << std::endl;
        la_carte = trouver(main_x);
        la_carte->position_terrain=terrain_x;
         la_carte->def = def;
         if(vis)
             la_carte->etat = RECTO;
         else
             la_carte->etat=VERSO;
         if(!def)
         {
             if(vis)
             {
                 emit visible(la_carte->image,terrain_x);
             }
             else
             {
                 emit nonvis(terrain_x);
             }
         }
         else
         {
             if(!vis)
             {
                 emit defens(terrain_x);
             }
         }
         emit destruction(main_x);
    }
}

//trouve la carte qui a la position x
//SERT DE MANIERE INTERNE (peut être utile dans de nombreux cas)
Carte * Noyau::trouver(int x)
{
    if(terrain->size()==0)
        return NULL;
    int i;
    for(i=0;i<(signed) terrain->size();i++)
    {
        if(terrain->at(i)->position_terrain == x)
            return terrain->at(i);
    }
    return NULL;
}

//permet de trouver la position parfaite dans la main
//SERT DE MANIERE INTERNE
int Noyau::perfect_position(int zone)
{

    int begin_position;//,min=151,current_position;
    if(zone==0)
   {
        begin_position=14;
        if(trouver(begin_position)==NULL)
               return begin_position;
        else
        {
            while(trouver(begin_position)!=NULL)
            {
                begin_position++;
            }
        }
       /* for(i=0;i<(signed)terrain->size();i++)
        {
             current_position = terrain->at(i)->position_terrain;
             if((current_position > 13) && (current_position < 75))
             {
                 if(min>current_position)
                        min = current_position;
              }
        }*/

    }
    else
    {
        begin_position=89;
        if(trouver(begin_position)==NULL)
               return begin_position;
        else
        {
            while(trouver(begin_position)!=NULL)
            {
                begin_position++;
            }
        }
        /*
        if(terrain->size()==0)
               return begin_position;
        for(i=0;i<(signed)terrain->size();i++)
        {
             current_position = terrain->at(i)->position_terrain;
             if((current_position > 88) && (current_position < 150))
             {
                 if(min>current_position)
                        min = current_position;
              }
        }*/
    }
   /* if(min==151)
        min = begin_position;*/
    return begin_position;
}

//permet d'attaquer
//prends en parametre la position de l'attaquant  et la position de l'attaqué, si le deuxieme argument n'est pas donné ou vaut -1 alors cela attaque l'adversaire directement (càd ses points de vie)
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

//enleve la carte à la position i du point de vue vecteur
//SERT DE MANIERE INTERNE
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
   for(j=i+1;j<(signed)(*vect)->size();j++)
   {
        res->push_back((*vect)->at(j));
   }
    *vect = res;
}

//detruit la carte à la position x et la place au cimetière
//prends en paramètre la position de la carte à detruire
void Noyau::detruire(int x)
{
    enlever_x(&terrain,x);
}

//change la position (atk/def) d'une carte
//prends en paramètre la position de la carte
void Noyau::switch_position(int terrain_x)
{
    int i;
    for(i=0;i<(signed)terrain->size();i++)
    {
        if(terrain->at(i)->position_terrain == terrain_x)
        {
            terrain->at(i)->pos = !(terrain->at(i)->pos);
            if(terrain_x<75)
              {
                //pour reseau
                emit switch_pos(terrain_x);
            }
            emit change_position(terrain_x);
            if(trouver(terrain_x)->etat == VERSO)
            {
                trouver(terrain_x)->etat = RECTO;
                emit visible(trouver(terrain_x)->image,terrain_x);
            }
            return;
        }
    }
}

//enlever la carte ayant la position x sur le terrain dans le vector donné
//SERT DE MANIERE INTERNE NORMALEMENT
void Noyau::enlever_x(std::vector<Carte *> **vect, int x)
{

    std::vector<Carte *> * resultat = new std::vector<Carte *>();
    if((*vect)->size()==1)
    {
       * vect = resultat;
        return;
    }
    int i;
    for(i=0;i<(signed)(*vect)->size();i++)
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
    emit destruction(x);

}

//PAS ENCORE BIEN IMPLEMENTE 
void Noyau::phase_suivante()
{
    if(phase==5)
        phase=1;
    else
        phase++;
}

//OBSOLETE
void Noyau::go()
{
    emit Noyau::emit_go();
}
//OBSOLETE
void Noyau::mondieu()
{
emit Noyau::emit_mondieu();
}
//OBSOLETE
void Noyau::send()
{
    emit Noyau::emit_send();
}
//OBSOLETE
void Noyau::attaque()
{
    emit Noyau::emit_attaque();
}

/***************************************************************/
//FONCTION ULTIME
//ELLE GERE TOUS LES CAS D'ACTIONS
//PERMET DE FAIRE FONCTIONNER LE JEU A L'AIDE DE "MESSAGES"
//POUR PLUS D'AMPLES EXPLICATIONS, DEMANDER A L'OREILLE NOIRE
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
         bool face = (les_valeurs->at(3)==1);
         poser(les_valeurs->at(0),les_valeurs->at(1),le_bool,face);

            delete(arg);
         std::cout << "j'ai fini de parser" << std::endl;
    }
    else if(s.compare(QString("etat"))==0)
    {
           std::cout << "terrain_size:" << terrain->size() << std::endl;
            int i;
            for(i=0;i<(signed)terrain->size();i++)
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
    else if(s.startsWith("þ"))
    {
        QStringRef* cut = new QStringRef(&s,1,s.length()-1);
        emit chat(cut->toString());
    }

}
/******************************************/
