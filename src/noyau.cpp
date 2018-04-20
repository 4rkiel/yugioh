#include "../inc/noyau.h"
#include "../inc/parser.h"
#include <chrono>
#include <thread>
#include <QMutex>

QMutex * mut = new QMutex();
Noyau::Noyau()
{
    terrain = new std::vector<Carte *>();
    cimetiere1 = new std::vector<Carte *>();
    cimetiere2 = new std::vector<Carte *>();
    d1=NULL;
    d2=NULL;
    extradeck1 = NULL;
    extradeck2 = NULL;
    alreadyAtk = new std::vector<int>();
    alreadyMoved = new std::vector<int>();
    alreadyActivate = new std::vector<int>();
    alreadyActivateAdv = new std::vector<int>();
    alreadyPosed = false;
    choix = new std::vector<Carte *>();
    allExodia = new std::vector<int>();
    allExodia->push_back(93610171);
    allExodia->push_back(42755639);
    allExodia->push_back(36825740);
    allExodia->push_back(47831829);
    allExodia->push_back(94836377);
    allExodiaAdv = new std::vector<int>();
    allExodiaAdv->push_back(93610171);
    allExodiaAdv->push_back(42755639);
    allExodiaAdv->push_back(36825740);
    allExodiaAdv->push_back(47831829);
    allExodiaAdv->push_back(94836377);
    tour = 1;

}

void Noyau::init()
{
    QSettings settings;
    foeLife = settings.value("lifePoints","8000").toInt();
    selfLife = foeLife;

    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,100); // distribution in range [1, 6]
    srand(dist6(rng));
     aleatoire = std::rand();
    std::cout << "aleatoire" << aleatoire << std::endl;
    std::srand(aleatoire);
    phase = 0;
    tour = 1;
    //chargerDeck(0);
    //deckAdverse(0);
    //std::stringstream ss1;
    //ss1 << "alea:" << aleatoire << std::endl;
    //emit tiens(QString::fromStdString(ss1.str()));
    //std::cout << "la taille de mon deck est : " << d1->size() << std::endl;
    //int i;
    //for(i=0;i<(signed)d1->size();i++)
      //  std::cout << "carte :" << d1->at(i)->id << std::endl;
    //piocher(1);
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //piocher(1);
}

void Noyau::comptageTick()
{
    if(lockTick)
    {
        nbrTick = (nbrTick+1) % 200;
        if(nbrTick==0)
            phase_suivante();
    }
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
//d1 = yolo->rechercher_set(0,NULL);
d1 = yolo->deck("deck/Test1.deck");
extradeck1 = yolo->extradeck("deck/Test1.deck");
std::random_shuffle(d1->begin(),d1->end());
std::cout << "je shuffle d1" << std::endl;
QString message = "";
message.append("adeck:");
int i;
for(i=0;i<(signed)d1->size();i++)
{
    std::stringstream ss1;
    ss1 << "/" << d1->at(i)->id;
    message.append(QString::fromStdString(ss1.str()));
}
if(extradeck1!=NULL)
{
    message.append("/extra:");
    for(i=0;i<(signed)extradeck1->size();i++)
    {
        std::stringstream ss1;
        ss1 << "/" << extradeck1->at(i)->id;
        message.append(QString::fromStdString(ss1.str()));
    }
}
emit tiens(message);
/*int i;
    for(i=0;i<(signed)d1->size();i++)
    {
        std::stringstream ss1;
        ss1 << "begin:"<< d1->at(i)->id;
        emit tiens(QString::fromStdString(ss1.str()));
        ss1.flush();

    }*/
}

//charge le deck de l'adversaire
//pour l'instant x est un int parce que les deck (situés dans le dossier deck) respectent le regex [0-9]*.deck
//cela changera dans l'avenir certainement 
void Noyau::deckAdverse(int x)
{
    //std::srand(ran);
Parser * yolo = new Parser();
d2 = yolo->rechercher_set(x,NULL);
std::random_shuffle(d2->begin(),d2->end());
int i;
for(i=0;i<(signed)d2->size();i++)
    std::cout << "carte :" << d2->at(i)->id << std::endl;
//std::this_thread::sleep_for(std::chrono::milliseconds(rand()%100));
//piocher(1);

    /*message.append("/mdeck:");
    for(i=0;i<(signed)d2->size();i++)
    {
        std::stringstream ss1;
        ss1 << "/" << d2->at(i)->id;
        message.append(QString::fromStdString(ss1.str()));
    }
    std::stringstream ss2;
    ss2 << "/life:" << selfLife;
    message.append(QString::fromStdString(ss2.str()));*/

}

void Noyau::donner_infos(int x)
{
    Carte * actuelle = trouver(x);
    if(actuelle != NULL)
     {
        if((isAdv(x) && actuelle->etat !=VERSO) || !isAdv(x))
       {

                emit give_infos(actuelle);
             //emit give_infos(actuelle->nom,actuelle->attribut,actuelle->niveau,actuelle->image,actuelle->type,actuelle->description,actuelle->atk,actuelle->def);
        std::cout << "j'émit les infos : " << actuelle->nom.toStdString() << "GENRE:" << actuelle->genre << " " << actuelle->attribut << actuelle->niveau << actuelle->image.toStdString() << actuelle->type << actuelle->description.toStdString() << actuelle->atk << actuelle->def << std::endl;

        }
    }
}


//gère le piochage
// x vaut 1 si c'est moi qui pioche sinon x vaut 76
void Noyau::piocher(int x)
{
    mut->lock();
    int position = Carte::correspondant(x);
    //si c'est moi qui pioche
    if(position>75)
    {
        //on met la position de la carte qui est au sommet du deck là où il faut dans la main
        //on place la carte dans au bon endroit
        //on enleve la carte du deck
        //sendInfo(QString("Je pioche"));
        //std::cout << "le traitement du piochage allié en cours " << std::endl;

        int dans_main = perfect_position(0);
        // std::cout << "id:"<< d1->front()->id << " je pose en " << dans_main << std::endl;
        // std::cout << "adresse : " << d1->front() << " id:"<< d1->front()->id << " je pose en " << dans_main << std::endl;
        if((d1==NULL) || (d1->size()==0))
        {
            emit sendInfo(QString(tr("Je ne peux plus piocher")));
                emit je_perds();
                return;
        }

        d1->front()->position_terrain = dans_main;
        if(contient(allExodia,d1->front()->id))
        {
            nbrExodia++;
            enlever_e(&allExodia,d1->front()->id);
        }
        terrain->push_back(d1->front());

        enlever_i(&d1,0);

        //prevenir le voisin
        emit visible(trouver(dans_main)->image,dans_main);
        std::cout << "faut piocher " << trouver(dans_main)->image.toStdString() << " là " << dans_main << std::endl;
        /*if(online)
        {
            emit tiens("apioche");
        }*/
        if(tour!=1)
            emit sendInfo(tr("J'ai pioché"));
        if(nbrExodia==5)
            emit je_gagne();
    }
    else
    {
        if((d2==NULL) || (d2->size()==0))
        {
                emit sendInfo(QString(tr("L'adversaire ne peut plus piocher")));
                emit je_gagne();
                return;
        }
        if(tour!=1)
        emit sendInfo(tr("L'adversaire a pioché"));
        std::cout << "le traitement du piochage adverse en cours " << std::endl;
        int dans_main = perfect_position(1);
        //std::cout << "adresse : " << d2->front() << " id:"<< d2->front()->id << " l'adversaire pose en " << dans_main << std::endl;
        d2->front()->position_terrain = dans_main;
        if(contient(allExodiaAdv,d2->front()->id))
        {
            nbrExodiaAdv++;
            enlever_e(&allExodiaAdv,d2->front()->id);
        }
        terrain->push_back(d2->front());
        enlever_i(&d2,0);
        emit nonvis(dans_main);
        if(nbrExodiaAdv==5)
        {
            emit tiens("Exodia");
            emit je_perds();
        }
    }
    mut->unlock();
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
    if(isHand(registre_0))
    {
        int position = perfect_terrain(0);
        if(position!=-1)
            poser(registre_0,position,false,true);
    }
}

void Noyau::poserDef()
{
     if(isHand(registre_0))
      {
         int position = perfect_terrain(0);
         if(position!=-1)
          poser(registre_0,position,true,false);
     }
}

void Noyau::poserMagH()
{
    if(isHand(registre_0))
    {
        int position = perfect_magie(0);
        if(position!=-1)
            poser(registre_0,position,false,false);
    }
}

void Noyau::poserMagV()
{
    if(isHand(registre_0))
    {
        int position = perfect_magie(0);
        if(position!=-1)
            poser(registre_0,position,false,true);
    }
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
            if(begin_position>5)
                return -1;

        }
        else
        {
            begin_position=76;
            if(terrain->size()==0)
                   return begin_position;
            while(trouver(begin_position)!=NULL)
                begin_position++;
            if(begin_position>81)
                return -1;

        }
        return begin_position;
}

void Noyau::enlever_m(std::vector<int>**vect,int m)
{
    std::vector<int>* res = new std::vector<int>();
    if((*vect)->size()==1)
    {
        *vect = res;
        return;
    }
   int j;
   for(j=0;j<m;j++)
   {
      res->push_back((*vect)->at(j));
   }
   for(j=m+1;j<(signed)(*vect)->size();j++)
   {
        res->push_back((*vect)->at(j));
   }
    *vect = res;
}

void Noyau::enlever_e(std::vector<int> **vect, int e)
{

    std::vector<int> * resultat = new std::vector<int>();
    if((*vect)->size()==1)
    {
       * vect = resultat;
        return;
    }
    int i;
    for(i=0;i<(signed)(*vect)->size();i++)
    {
        if((*vect)->at(i)!=e)
            resultat->push_back((*vect)->at(i));
    }
    *vect = resultat;
}

//determine la position où poser la carte MAGIE/PIEGE sur le terrain, zone = 0 si c'est moi qui pose sinon c'est 1
int Noyau::perfect_magie(int zone)
{
     int begin_position;
     if(zone==0)
       {
         if(!alreadyActivate->empty())
         {
            begin_position=alreadyActivate->at(0);
            enlever_m(&alreadyActivate,0);
            //trouver(begin_position)->position_terrain = -1;
            detruire(begin_position);
            return begin_position;
         }
            begin_position=8;
            if(terrain->size()==0)
                   return begin_position;
            while(trouver(begin_position)!=NULL)
                begin_position++;
            if(begin_position>12)
                return -1;

        }
        else
        {
            begin_position=83;
            if(terrain->size()==0)
                   return begin_position;
            while(trouver(begin_position)!=NULL)
                begin_position++;
            if(begin_position>88)
                return -1;

        }
        return begin_position;
}

void Noyau::poser_test(int x)
{
    //le if doit être mieux géré negrion
    std::cout << "t'as cliqué sur " << x << std::endl;
    Carte * la_carte = trouver(x);
    if(la_carte == NULL || isAdv(x))
        return;
    int i;
    if(can_poser() && !alreadyPosed && isHand(x) && (la_carte->genre==0) && (la_carte->niveau<5)   && (perfect_terrain(0)!=-1))
    {
        registre_0 = x;
        emit dialogue();
    }
    else if(can_poser() && !alreadyPosed && isHand(x) && (la_carte->genre==0) && (la_carte->niveau<7)   && (perfect_terrain(0)!=-1))
    {
        registre_0 = x;
        std::cout << "Il faut un sacrifice" << std::endl;
        for(i=0;i<(signed)terrain->size();i++)
        {
            if(!isAdv(terrain->at(i)->position_terrain) && isMonst(terrain->at(i)->position_terrain))
                    choix->push_back(terrain->at(i));
        }
        emit dialogueSac1(1,choix);

    }
    else if(can_poser() && !alreadyPosed && isHand(x) && (la_carte->genre==0)  && (perfect_terrain(0)!=-1))
    {
        registre_0 = x;
        std::cout << "Il faut deux sacrifices" << std::endl;
        emit dialogueSac2();
    }
    else if(can_poser() && isHand(x) && (la_carte->genre==1 || la_carte->genre==2) && (perfect_magie(0)!=-1))
    {
       registre_0 = x;
       emit dialogueMagi();
    }
    else if(can_switch() && isMonst(x)  && !contient(alreadyMoved,x) && !contient(alreadyAtk,x))
    {
        switch_position(x);
        std::stringstream s1;
        s1 << "swap/" << Carte::correspondant(x);
        emit tiens(QString::fromStdString(s1.str()));
    }
    else if(isMagic(x) && trouver(x)!=NULL && can_activate())
    {
        std::cout << "je vais activer " << x << std::endl;
        activer(x);
    }
}

//poser la carte
//prends en argument la position de la carte dans la main, la position où on veut la poser, def est vrai si on veut la poser en mode defense , vis est vrai si on veut la mettre en mode face recto
void Noyau::poser(int main_x, int terrain_x, bool def, bool vis)
{
    int i;
    Carte * la_carte;
    if(main_x < 75)
    {
        if(can_poser() )
            {std::cout << "je traite mon posage" << std::endl;
            /*for(i=0;i<(signed)terrain->size();i++)
            {
                std::cout << terrain->at(i)->id << " at position:" << terrain->at(i)->position_terrain << std::endl;
            }*/

            emit sendInfo(QString(tr("Je pose")));
            la_carte = trouver(main_x);
            la_carte->position_terrain=terrain_x;
            la_carte->pos= def;
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
                std::cout << "je suis dans le online" << std::endl;
                QString message = "p/";
                std::stringstream s1;
                s1 << Carte::correspondant(main_x) << "/" << Carte::correspondant(terrain_x) << "/" << (def? 1 : 0) << "/" << (vis? 1 : 0) ;
                message.append(QString::fromStdString(s1.str()));
                std::cout << "j'envois message:" << message.toStdString() << std::endl;
                emit tiens(message);
            }
            if(la_carte->genre==0)
             {   alreadyPosed=true;
                alreadyMoved->push_back(terrain_x);
            }

        }
    }
    else
    {
         emit sendInfo(QString(tr("L'adversaire pose")));
        std::cout << "je traite le posage adverse" << std::endl;
        for(i=0;i<(signed)terrain->size();i++)
        {
            std::cout << terrain->at(i)->id << " at position:" << terrain->at(i)->position_terrain << std::endl;
        }
        la_carte = trouver(main_x);
        if(la_carte == NULL)
         {   std::cout << "WO NEGRO TU GERES PAS " << std::endl;


        }
        la_carte->position_terrain=terrain_x;
        std::cout << "la position final est " << la_carte->position_terrain << std::endl;
         la_carte->pos = def;
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

void Noyau::sacrifier_poser(int sacrifice_x, int main_x, int terrain_x,bool def, bool vis)
{
    int i;
    Carte * la_carte;
    if(main_x < 75)
    {
        if(can_poser() )
            {std::cout << "je traite mon posage" << std::endl;
            /*for(i=0;i<(signed)terrain->size();i++)
            {
                std::cout << terrain->at(i)->id << " at position:" << terrain->at(i)->position_terrain << std::endl;
            }*/
            emit sendInfo(QString(tr("Je pose de manière sacrificielle")));
            la_carte = trouver(main_x);
            la_carte->position_terrain=terrain_x;
            la_carte->pos= def;
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
            emit destruction(sacrifice_x);
            emit destruction(main_x);
            //emit je_pose(la_carte->image,main_x,terrain_x,def,vis);

            if(online)
            {
                std::cout << "je suis dans le online" << std::endl;
                QString message = "sac1/";
                std::stringstream s1;
                s1 <<Carte::correspondant(sacrifice_x) << "/" << Carte::correspondant(main_x) << "/" << Carte::correspondant(terrain_x) << "/" << (def? 1 : 0) << "/" << (vis? 1 : 0) ;
                message.append(QString::fromStdString(s1.str()));
                std::cout << "j'envois message:" << message.toStdString() << std::endl;
                emit tiens(message);
            }
            if(la_carte->genre==0)
                alreadyPosed=true;
        }
    }
    else
    {
         emit sendInfo(QString(tr("L'adversaire pose de manière sacrificielle")));
        std::cout << "je traite le posage adverse" << std::endl;
        for(i=0;i<(signed)terrain->size();i++)
        {
            std::cout << terrain->at(i)->id << " at position:" << terrain->at(i)->position_terrain << std::endl;
        }
        la_carte = trouver(main_x);
        if(la_carte == NULL)
         {   std::cout << "WO NEGRO TU GERES PAS " << std::endl;


        }
        la_carte->position_terrain=terrain_x;
        std::cout << "la position final est " << la_carte->position_terrain << std::endl;
         la_carte->pos = def;
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
         emit destruction(sacrifice_x);
    }
    choix->clear();
}

void Noyau::sacrifier_sacrifier_poser(int sacrifice_1_x, int sacrifice_2_x, int main_x, int terrain_x,bool def,bool vis)
{
    int i;
    Carte * la_carte;
    if(main_x < 75)
    {
        if(can_poser() )
            {std::cout << "je traite mon posage" << std::endl;
            /*for(i=0;i<(signed)terrain->size();i++)
            {
                std::cout << terrain->at(i)->id << " at position:" << terrain->at(i)->position_terrain << std::endl;
            }*/
            emit sendInfo(QString(tr("Je pose de manière sacrificielle")));
            la_carte = trouver(main_x);
            la_carte->position_terrain=terrain_x;
            la_carte->pos= def;
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
            emit destruction(sacrifice_1_x);
            emit destruction(sacrifice_2_x);
            emit destruction(main_x);
            //emit je_pose(la_carte->image,main_x,terrain_x,def,vis);

            if(online)
            {
                std::cout << "je suis dans le online" << std::endl;
                QString message = "sac2/";
                std::stringstream s1;
                s1 <<Carte::correspondant(sacrifice_1_x) << "/" <<Carte::correspondant(sacrifice_2_x) << "/" << Carte::correspondant(main_x) << "/" << Carte::correspondant(terrain_x) << "/" << (def? 1 : 0) << "/" << (vis? 1 : 0) ;
                message.append(QString::fromStdString(s1.str()));
                std::cout << "j'envois message:" << message.toStdString() << std::endl;
                emit tiens(message);
            }
            if(la_carte->genre==0)
                alreadyPosed=true;
        }
    }
    else
    {
         emit sendInfo(QString(tr("L'adversaire pose de manière sacrificielle")));
        std::cout << "je traite le posage adverse" << std::endl;
        for(i=0;i<(signed)terrain->size();i++)
        {
            std::cout << terrain->at(i)->id << " at position:" << terrain->at(i)->position_terrain << std::endl;
        }
        la_carte = trouver(main_x);
        if(la_carte == NULL)
         {   std::cout << "WO NEGRO TU GERES PAS " << std::endl;


        }
        la_carte->position_terrain=terrain_x;
        std::cout << "la position final est " << la_carte->position_terrain << std::endl;
         la_carte->pos = def;
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
         emit destruction(sacrifice_1_x);
         emit destruction(sacrifice_2_x);
    }
    choix->clear();
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
        /*int i;
        for(i=0;i<terrain->size();i++)
        {
            std::cout << "je cherche si je peux : adresse:" << terrain->at(i) << " at " << terrain->at(i)->position_terrain << std::endl;
        }*/
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

bool Noyau::no_monster(int zone)
{
    bool fin = true;
    int i;
    if(zone==0)
    {
        for(i=0;i<5;i++)
        {
            if(trouver(1+i)!=NULL)
                return false;
        }
    }
    else
    {
        for(i=0;i<5;i++)
        {
            if(trouver(76+i)!=NULL)
                return false;
        }
    }
    return fin;
}

void Noyau::attaquerSlot(int atk,int def)
{
    if(!contient(alreadyAtk,atk))
       attaquer(atk,def);
}

void Noyau::activer(int x)
{
    std::stringstream ss1;
    Carte* carte = trouver(x);
    if(carte == NULL)
    {
        std::cout << "t'es con la carte à la position " << x << " existe pas" << std::endl;
        return;
    }
    else
    {
        std::cout << "l'id est "<< carte->id << " et l'effet est " << carte->effet << std::endl;
    }
    if(x<75)
    {
         alreadyActivate->push_back(x);
        switch(carte->effet)
        {
        case 0:

           emit sendInfo(QString(tr("J'active Pot de Cupidité")));
            ss1 << "act/" << Carte::correspondant(x);
            emit tiens(QString::fromStdString(ss1.str()));
            piocher(1);
            piocher(1);
            break;
        case 10:
           emit sendInfo(QString(tr("J'active Trou Noir")));
            ss1 << "act/" << Carte::correspondant(x);
            emit tiens(QString::fromStdString(ss1.str()));
            destroy_all(1);
            destroy_all(0);
            break;
        case 11:
            emit sendInfo(QString(tr("J'active Raigeki")));
             ss1 << "act/" << Carte::correspondant(x);
             emit tiens(QString::fromStdString(ss1.str()));
             destroy_all(1);
            break;
        default:
            break;
        }
    }
    else
    {
        alreadyActivateAdv->push_back(x);
        switch(carte->effet)
        {
        case 0:
           emit sendInfo(QString(tr("L'adversaire active Pot de Cupidité")));
            piocher(76);
            piocher(76);
            break;
        case 10:
           emit sendInfo(QString(tr("L'adversaire active Trou Noir")));
            destroy_all(0);
            destroy_all(1);
            break;
        case 11:
            emit sendInfo(QString(tr("L'adversaire active Raigeki")));
             destroy_all(0);
            break;
        default:
            break;
        }
    }
}

//detruire toutes les monstres d'une zone, 0 = moi sinon adversaire
void Noyau::destroy_all(int zone)
{
    int i;
    if(zone==0)
    {
        for(i=0;i<(signed)terrain->size();i++)
        {
            if(!isAdv(terrain->at(i)->position_terrain) && isMonst(terrain->at(i)->position_terrain))
                detruire(terrain->at(i)->position_terrain);
        }
    }
    else
    {

        for(i=0;i<(signed)terrain->size();i++)
        {
            if(isAdv(terrain->at(i)->position_terrain)&& isMonst(terrain->at(i)->position_terrain))
                detruire(terrain->at(i)->position_terrain);
        }
    }
    return;
}


//permet d'attaquer
//prends en parametre la position de l'attaquant  et la position de l'attaqué, si le deuxieme argument n'est pas donné ou vaut -1 alors cela attaque l'adversaire directement (càd ses points de vie)
void Noyau::attaquer(int attaquant_x, int adversaire_x)
{
    //c'est moi qui attaque
    std::cout << "je vais attaquer avec " << attaquant_x << " et " << adversaire_x  << std::endl;
    Carte * atk = trouver(attaquant_x);
    if(atk==NULL)
    {
        std::cout << "attaquant existe pas " << std::endl;
        return;
    }
    if(attaquant_x < 75)
    {
        if(can_atak())
        {
            //Carte * atk = trouver(attaquant_x);
            if(adversaire_x == -1)
            {
                if(no_monster(1))
                {
                    std::cout << "l'adversaire perds de la vie " << std::endl;
                    foeLife = foeLife - atk->atk;
                    emit changeLife(foeLife,false);
                    if(foeLife <=0)
                        emit je_gagne();
                }
            }
            else
            {
                     Carte * def = trouver(adversaire_x);
                     //le monstre est en position de défense
                     if(def == NULL)
                     {
                         if(no_monster(1))
                         {
                             std::cout << "je vais attaquer l'adversaire directement" << std::endl;
                             attaquer(attaquant_x);
                             return;
                         }
                         std::cout << "attaque impossible" << std::endl;
                         return;
                     }
                    if(def->pos)
                    {
                        if(def->etat == VERSO)
                            emit montre(def->position_terrain);
                        if(atk->atk > def->def)
                        {
                            detruire(adversaire_x);
                        }
                        else if(atk->atk < def->def)
                        {
                            selfLife = selfLife - (def->def - atk->atk);

                            emit changeLife(selfLife,true);
                            if(selfLife <=0)
                                emit je_perds();
                        }
                    }
                    else
                    {
                        if(atk->atk > def->atk)
                        {
                            detruire(adversaire_x);
                            foeLife = foeLife - (atk->atk - def->atk);
                            emit changeLife(foeLife,false);
                            if(foeLife <=0)
                                emit je_gagne();
                        }
                        else if(atk->atk < def->atk)
                        {
                            detruire(attaquant_x);
                            selfLife = selfLife - (def->atk - atk->atk);
                            if(selfLife <=0)
                                emit je_perds();
                            emit changeLife(selfLife,true);
                        }
                        else
                        {
                            detruire(adversaire_x);
                            detruire(attaquant_x);
                        }
                    }
            }
            QString message = "a/";
            std::stringstream s1;
            s1 << Carte::correspondant(attaquant_x) << "/" << Carte::correspondant(adversaire_x);
            message.append(QString::fromStdString(s1.str()));
            emit tiens(message);
            alreadyAtk->push_back(attaquant_x);
        }

    }
    //c'est l'autre qui attaque
    else
    {
        //Carte * atk = trouver(attaquant_x);
        if(adversaire_x == -1)
        {
            if(no_monster(0))
            {
                selfLife = selfLife - atk->atk;

                emit changeLife(selfLife,true);
                if(selfLife <=0)
                    emit je_perds();
            }
        }
        else
        {
                 Carte * def = trouver(adversaire_x);
                 //le monstre est en position de défense
                 if(def == NULL)
                 {
                     if(no_monster(0))
                     {
                         attaquer(attaquant_x);
                         return;
                     }
                 }
                if(def->pos)
                {
                    if(def->etat == VERSO)
                        emit montre(def->position_terrain);
                    if(atk->atk > def->def)
                    {
                        detruire(adversaire_x);
                    }
                    else if(atk->atk < def->def)
                    {
                        foeLife = foeLife - (def->def - atk->atk);
                        emit changeLife(foeLife,false);
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
                        emit changeLife(selfLife,true);
                        if(selfLife <=0)
                            emit je_perds();
                    }
                    else if(atk->atk < def->atk)
                    {
                        detruire(attaquant_x);
                        foeLife = foeLife - (def->atk - atk->atk);
                        emit changeLife(foeLife,false);
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

bool Noyau::contient(std::vector<int> *vect, int x)
{
    return (std::find(vect->begin(), vect->end(), x) != vect->end());
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
            alreadyMoved->push_back(terrain_x);
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


//TODO: ajouter les signaux pour l'IA
//PAS ENCORE BIEN IMPLEMENTE 
void Noyau::phase_suivante()
{
    if(phase==2)
    {
        alreadyPosed=false;
        alreadyMoved->clear();
        alreadyAtk->clear();
        mon_tour = !mon_tour;
        phase=0;
        tour++;
        emit setTour(tour);
        if(mon_tour)
            piocher(1);
        else
            piocher(76);
    }
    else
        phase++;
    switch(phase)
    {
        case 0:
            emit sendInfo(tr("Main Phase 1"));
        break;
        case 1:
            if((no_monster(0) && mon_tour) || (no_monster(1) && !mon_tour))
               {
                phase = 2;
                phase_suivante();
            }
            else
                emit sendInfo(tr("Battle Phase"));
        break;
        case 2:
           emit sendInfo(tr("Main Phase 2"));
        break;
        default:
        break;

    }
    int i;
    for(i=0;i<(signed)alreadyActivate->size();i++)
    {
        detruire(alreadyActivate->at(i));
    }
    for(i=0;i<(signed)alreadyActivateAdv->size();i++)
    {
        detruire(alreadyActivateAdv->at(i));
    }
       alreadyActivate->clear();
       alreadyActivateAdv->clear();
}

bool Noyau::can_poser()
{
    return (mon_tour && (phase==0 || phase==2));
}

bool Noyau::can_atak()
{
    return (mon_tour && (phase==1));
}

bool Noyau::can_switch()
{
    return(mon_tour && (phase==0 || phase==2));
}

bool Noyau::can_activate()
{
    return (mon_tour);
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
    else if(s.startsWith("sac1/"))
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
         bool le_bool = (les_valeurs->at(3)==1);
         bool face = (les_valeurs->at(4)==1);
         sacrifier_poser(les_valeurs->at(0),les_valeurs->at(1),les_valeurs->at(2),le_bool,face);

            delete(arg);
         std::cout << "j'ai fini de parser" << std::endl;
    }
    else if(s.startsWith("sac2/"))
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
         bool le_bool = (les_valeurs->at(4)==1);
         bool face = (les_valeurs->at(5)==1);
         sacrifier_sacrifier_poser(les_valeurs->at(0),les_valeurs->at(1),les_valeurs->at(2),les_valeurs->at(3),le_bool,face);

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
    else if(s.startsWith("alea:"))
    {
        //int valeur;
        char * arg = new char[s.length()+1];
           std::strcpy(arg,s.toStdString().c_str());
         char * parcourir = std::strtok(arg,":");
         std::string vrai;
         if(parcourir!=NULL)
          vrai = parcourir;
         while(parcourir!=NULL)
         {
             std::cout << "parc" << parcourir << " vrai:"<< vrai << std::endl;
             parcourir = std::strtok(NULL,":");
             if(parcourir!=NULL)
            vrai = parcourir;
          }
         delete(arg);
         //valeur = atoi(vrai.c_str());
         deckAdverse(0);
    }
    else if(s.startsWith("þ"))
    {
        QStringRef* cut = new QStringRef(&s,1,s.length()-1);
        emit chat(cut->toString());
    }
    else if(s.startsWith("adeck:"))
    {
        bool extra = false;
        std::cout << "JE TRAITE LE MESSAGE DU SERVEUR" << std::endl;
        Parser * yolo = new Parser();
        d1 = new std::vector<Carte *>();
        d2 = new std::vector<Carte *>();
        extradeck2 = new std::vector<Carte *>();
        char * arg = new char[s.length()+1];
           std::strcpy(arg,s.toStdString().c_str());
         char * parcourir = std::strtok(arg,"/");
         QString vrai;
         if(parcourir!=NULL)
          vrai = QString(parcourir);
         int i;
         while(parcourir!=NULL)
         {
             //std::cout << "parc" << parcourir << " vrai:"<< vrai << std::endl;
             if(!vrai.startsWith(QString("adeck")))
             {
                 if(vrai.contains("extra"))
                 {
                     extra = true;
                 }
                 else if(!extra)
                 {
                     for(i=0;i<(signed)yolo->all_cards->size();i++)
                                {
                                    if(yolo->all_cards->at(i)->id == atoi(parcourir))
                                    {
                                          d2->push_back((yolo->all_cards->at(i))->copie());
                                          break;
                                    }
                                }
                 }
                else
                 {
                     for(i=0;i<(signed)yolo->all_cards->size();i++)
                                {
                                    if(yolo->all_cards->at(i)->id == atoi(parcourir))
                                    {
                                          extradeck2->push_back((yolo->all_cards->at(i))->copie());
                                          break;
                                    }
                                }
                 }
               }
             parcourir = std::strtok(NULL,"/");
             if(parcourir!=NULL)
            vrai = QString(parcourir);
          }
        if(extradeck2->size()==0)
        {
            delete(extradeck2);
            extradeck2=NULL;
        }

         delete(arg);
         //d1 = yolo->rechercher_set(0,NULL);
         d1 = yolo->deck("deck/Test1.deck");
         extradeck1 = yolo->extradeck("deck/Test1.deck");
         std::random_shuffle(d1->begin(),d1->end());
         std::cout << "je shuffle d1" << std::endl;
         QString message = "";
         message.append("sdeck:");
         for(i=0;i<(signed)d1->size();i++)
         {
             std::stringstream ss1;
             ss1 << "/" << d1->at(i)->id;
             message.append(QString::fromStdString(ss1.str()));
         }
         if(extradeck1!=NULL)
         {
             message.append("/extra:");
             for(i=0;i<(signed)extradeck1->size();i++)
             {
                 std::stringstream ss1;
                 ss1 << "/" << extradeck1->at(i)->id;
                 message.append(QString::fromStdString(ss1.str()));
             }
         }
         emit tiens(message);
         //piocher(1);
        // piocher(76);
         //deckAdverse(0);
    }
    else if(s.startsWith("sdeck:"))
    {
        bool extra = false;
        std::cout << "JE TRAITE LE MESSAGE DU CLIENT" << std::endl;
        Parser * yolo = new Parser();
        d2 = new std::vector<Carte *>();
        extradeck2 = new std::vector<Carte *>();
        char * arg = new char[s.length()+1];
           std::strcpy(arg,s.toStdString().c_str());
         char * parcourir = std::strtok(arg,"/");
         QString vrai;
         if(parcourir!=NULL)
          vrai = QString(parcourir);
         int i;
        /* while(parcourir!=NULL)
         {
             //std::cout << "parc" << parcourir << " vrai:"<< vrai << std::endl;
             if(!vrai.startsWith(QString("adeck")))
             {
             for(i=0;i<(signed)yolo->all_cards->size();i++)
                        {
                            if(yolo->all_cards->at(i)->id == atoi(parcourir))
                            {
                                  d2->push_back(yolo->all_cards->at(i)->copie());
                                  break;
                            }
                        }
               }
             parcourir = std::strtok(NULL,"/");
             if(parcourir!=NULL)
            vrai = QString(parcourir);
          }*/
         while(parcourir!=NULL)
         {
             //std::cout << "parc" << parcourir << " vrai:"<< vrai << std::endl;
             if(!vrai.startsWith(QString("adeck")))
             {
                 if(vrai.contains("extra"))
                 {
                     extra = true;
                 }
                 else if(!extra)
                 {
                     for(i=0;i<(signed)yolo->all_cards->size();i++)
                                {
                                    if(yolo->all_cards->at(i)->id == atoi(parcourir))
                                    {
                                          d2->push_back((yolo->all_cards->at(i))->copie());
                                          break;
                                    }
                                }
                 }
                else
                 {
                     for(i=0;i<(signed)yolo->all_cards->size();i++)
                                {
                                    if(yolo->all_cards->at(i)->id == atoi(parcourir))
                                    {
                                          extradeck2->push_back((yolo->all_cards->at(i))->copie());
                                          break;
                                    }
                                }
                 }
               }
             parcourir = std::strtok(NULL,"/");
             if(parcourir!=NULL)
            vrai = QString(parcourir);
          }
        if(extradeck2->size()==0)
        {
            delete(extradeck2);
            extradeck2=NULL;
        }


         delete(arg);
         QString message = "";
         message.append("life/");
         std::stringstream ss1;
         ss1 << selfLife;
          message.append(QString::fromStdString(ss1.str()));
         emit tiens(message);
         //piocher(1);
    }
    else if(s.startsWith("life/"))
    {
        char * arg = new char[s.length()+1];
           std::strcpy(arg,s.toStdString().c_str());
         char * parcourir = std::strtok(arg,"/");
         QString vrai;
         if(parcourir!=NULL)
          vrai = QString(parcourir);
         while(parcourir!=NULL)
         {
             //std::cout << "parc" << parcourir << " vrai:"<< vrai << std::endl;
             if(!vrai.startsWith(QString("life")))
             {
               //  std::cout << "la vie :" << parcourir << "la vraie vie:" << selfLife<< std::endl;
                   if(!(selfLife == atoi(parcourir)))
                   {
                       selfLife = 8000;
                       foeLife = selfLife;
                   }
             }
             parcourir = std::strtok(NULL,"/");
             if(parcourir!=NULL)
            vrai = QString(parcourir);
          }
         delete(arg);
         QString message = "";
         message.append("slife/");
         std::stringstream ss1;
         ss1 << selfLife;
          message.append(QString::fromStdString(ss1.str()));
          emit tiens(message);
          emit giveLife(selfLife);
          emit setTour(tour);
          emit beginTour();
          lockTick=true;
          mon_tour=false;

          piocher(1);
          piocher(1);
          piocher(1);
          piocher(1);
          piocher(1);
          piocher(76);
          piocher(76);
          piocher(76);
          piocher(76);
          piocher(76);
          piocher(76);
          emit sendInfo(tr("La partie commence !"));
          emit sendInfo(tr("Main Phase 1"));
    }
    else if(s.startsWith("slife/"))
    {
        char * arg = new char[s.length()+1];
           std::strcpy(arg,s.toStdString().c_str());
         char * parcourir = std::strtok(arg,"/");
         QString vrai;
         if(parcourir!=NULL)
          vrai = QString(parcourir);
         while(parcourir!=NULL)
         {
             //std::cout << "parc" << parcourir << " vrai:"<< vrai << std::endl;
             if(!vrai.startsWith(QString("slife")))
             {
                   if(!(selfLife == atoi(parcourir)))
                   {
                       selfLife = 8000;
                       foeLife = selfLife;
                   }
             }
             parcourir = std::strtok(NULL,"/");
             if(parcourir!=NULL)
            vrai = QString(parcourir);
          }
         delete(arg);
         emit giveLife(selfLife);
         piocher(1);
         piocher(1);
         piocher(1);
         piocher(1);
         piocher(1);
         piocher(76);
         piocher(76);
         piocher(76);
         piocher(76);
         piocher(76);
         piocher(1);
         emit setTour(tour);
         emit beginTour();
         lockTick=true;
         mon_tour=true;
         emit sendInfo(tr("La partie commence !"));
         emit sendInfo(tr("Main Phase 1"));
        // emit commence();
    }
    else if(s.compare(QString("init"))==0)
    {
        chargerDeck(0);
        //deckAdverse(0);
    }
    else if(s.startsWith("act/"))
    {


        int carte = -1;
        char * arg = new char[s.length()+1];
           std::strcpy(arg,s.toStdString().c_str());
         char * parcourir = std::strtok(arg,"/");
         char * vrai = parcourir;
         while(parcourir!=NULL)
         {
             std::cout << "parc" << parcourir << " vrai:"<< vrai << std::endl;
             if(!QString(vrai).startsWith(QString("act")))
             {
                    std::cout << "CARTE VA PRENDRE UNE VALEUR:" << atoi(parcourir) << std::endl;
                    carte = atoi(parcourir);
             }
            parcourir = std::strtok(NULL,"/");
            if(parcourir!=NULL)
                vrai = parcourir;
         }
         delete(arg);
         std::cout << "carte a la valeur final:" << carte << std::endl;
         activer(carte);

    }
    else if(s.compare("Exodia")==0)
    {
        emit je_gagne();
    }

}
/******************************************/
