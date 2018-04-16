#include "../inc/parser.h"
#include "../inc/carte.h"
#include "QCoreApplication"

Parser::Parser(QWidget *parent)
    : QWidget(parent)
{
    courante = new Carte();
    all_cards = new std::vector<Carte*>();
   // QStringList list = QDir("/adhome/v/vc/vcostantino/Documents/IHM/PROJET/Version26/yugioh/sets/").entryList();
    QStringList list = QDir(QCoreApplication::applicationDirPath()+"/sets/").entryList();

    int i;
    //std::cout << "je suis ici" << std::endl;
    for(i=0;i<(signed)list.length();i++)
    {

        if((list.at(i).compare(QString("."))!=0) && (list.at(i).compare(QString(".."))!=0))
        {
           // std::cout << "je parcours la list" << list.at(i).toStdString() << std::endl;
 //           fichier_courant = "/adhome/v/vc/vcostantino/Documents/IHM/PROJET/Version26/yugioh/sets/"+list.at(i);
            fichier_courant = QCoreApplication::applicationDirPath()+"/sets/"+list.at(i);
        getAll();
        }
    }
    for(i=0;i<(signed)all_cards->size();i++)
    {
       // std::cout << "je parcours la list" << std::endl;
          // all_cards->at(i)->afficher_infos();
    }
       std::vector<Carte *> * search = rechercher_nom("Drag",NULL);
       //std::cout << "J'AI TROUVE" << std::endl;
       for(i=0;i<(signed)search->size();i++)
        {}   //search->at(i)->afficher_infos();
}

std::string Parser::getSet(std::string nom)
{
    char * arg = new char[nom.length()+1];
    std::strcpy(arg,nom.c_str());
    char * parcourir = std::strtok(arg,"/");
    std::string vrai;
    if(parcourir!=NULL)
         vrai = parcourir;
    while(parcourir!=NULL)
    {
       //std::cout << "parc" << parcourir << " vrai:"<< vrai << std::endl;
        parcourir = std::strtok(NULL,"/");
        if(parcourir!=NULL)
            vrai = parcourir;
    }
    delete(arg);
    arg = new char[vrai.length()+1];
    std::strcpy(arg,vrai.c_str());
    parcourir = std::strtok(arg,".");
    vrai = parcourir;
    delete(arg);
    return vrai;
}


void Parser::getAll()
{
    QFile file(fichier_courant);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
    QString line = in.readLine();
    while(!line.isNull())
    {
        Parser::parser(line.toStdString());
        if(etape==11)
        {
             all_cards->push_back(courante);
         }
        line = in.readLine();
     }
     file.close();
    return;
}

//PERMET DE RECUPERER LES EFFETS SOUS FORME DE STRING QUI DEVRONT ETRE EUX MEMES MODIFIES
int Parser::recup_effet(std::string effets)
{
    int valeur=-1;
    char * arg = new char[effets.length()+1];
    std::strcpy(arg,effets.c_str());
    char * parcourir = std::strtok(arg,"{{");
    std::string vrai;
    if(parcourir!=NULL)
     vrai = parcourir;
    while(parcourir!=NULL)
    {

               // std::cout << "parc" << parcourir << " vrai:"<< vrai << std::endl;
                //effet=effet+vrai;
                if(!QString::fromStdString(vrai).startsWith(QString("{{")))
                {
                    valeur = atoi(vrai.c_str());
                }
                parcourir = std::strtok(NULL,"{{");
                if(parcourir!=NULL)
                   vrai = parcourir;

    }

    delete(arg);
    return valeur;
}


//PARSE UNE LIGNE COMME IL FAUT
void Parser::parser(std::string ligne)
{
   // std::string image ="/media/victor/Test/Version25/yugioh/img/cards/";
    std::string image =QCoreApplication::applicationDirPath().toStdString()+"/img/cards/";
    std::stringstream ss2 ;
    if(etape==11)
     {
        etape=0;
        courante = new Carte();
    }

    if(ligne.empty() || ligne.find(" ")==0)
        return;

    if(ligne.find("##")==std::string::npos)
    {
        //std::cout << ligne << std::endl;
        switch(etape)
        {
            case 0:
                courante->id = atoi(ligne.c_str());
                //image ="/media/victor/Test/Version25/yugioh/img/cards/";
                image = QCoreApplication::applicationDirPath().toStdString()+"/img/cards/";
                image = image + getSet(fichier_courant.toStdString());
                image = image + "/"+ligne.c_str();
                courante->image = QString::fromStdString(image);
                courante->set = atoi(getSet(fichier_courant.toStdString()).c_str());
                 break;
            case 1:
                courante->genre=atoi(ligne.c_str());
                break;
            case 2:
                courante->sous_type=atoi(ligne.c_str());
                break;
            case 3:
                courante->nom=QString::fromStdString(ligne);
                break;
            case 4:
                courante->attribut=(Attribut) atoi(ligne.c_str());
                break;
            case 5:
                courante->niveau=atoi(ligne.c_str());
                break;
            case 6:
                courante->type=(Type) atoi(ligne.c_str());
                break;
            case 7:
                if(ligne.find("{{")==std::string::npos)
                {
                        courante->description = courante->description+QString::fromStdString(ligne);
                         etape--;
                }
                else
                {
                    courante->effet = recup_effet(ligne);
                    etape++;
                 }
                break;
            case 8:
                courante -> effet = recup_effet(ligne);
                std::cout << "JE METS L'EFFET" << courante->effet << std ::endl;
                break;
            case 9:
                courante->atk=atoi(ligne.c_str());
                courante->default_atk = courante->atk;
                break;
            case 10:
                courante->def=atoi(ligne.c_str());
                courante->default_def = courante->def;
                break;
            default:
                break;
         }

    etape++;
    }
}

//PERMET DE RECHERCHER DES CARTES DONT LE NOM EST NOM
std::vector<Carte *> * Parser::rechercher_nom(std::string nom,std::vector<Carte *> * arg)
{
    if(arg==NULL)
        arg=all_cards;
    std::vector<Carte *> *resultat = new std::vector<Carte *>();
    int i;
    for(i=0;i<(signed)arg->size();i++)
    {
        if(arg->at(i)->nom.contains(QString::fromStdString(nom)))
            resultat->push_back(arg->at(i));
    }
    return resultat;
}

std::vector<Carte *> * Parser::rechercher_type(int ty,std::vector<Carte *> * arg)
{
    if(arg==NULL)
        arg=all_cards;
    std::vector<Carte *> *resultat = new std::vector<Carte *>();
    int i;
    for(i=0;i<(signed)arg->size();i++)
    {
        if(arg->at(i)->type == ty)
            resultat->push_back(arg->at(i));
    }
    return resultat;
}

std::vector<Carte *> * Parser::rechercher_genre(int g,std::vector<Carte *> * arg)
{
    if(arg==NULL)
        arg=all_cards;
    std::vector<Carte *> *resultat = new std::vector<Carte *>();
    int i;
    for(i=0;i<(signed)arg->size();i++)
    {
        if(arg->at(i)->genre == g)
            resultat->push_back(arg->at(i));
    }
    return resultat;
}

std::vector<Carte *> * Parser::rechercher_atk(int a,std::vector<Carte *> * arg)
{
    if(arg==NULL)
        arg=all_cards;
    std::vector<Carte *> *resultat = new std::vector<Carte *>();
    int i;
    for(i=0;i<(signed)arg->size();i++)
    {
        if(arg->at(i)->atk >= a)
            resultat->push_back(arg->at(i));
    }
    return resultat;
}

std::vector<Carte *> * Parser::rechercher_def(int d,std::vector<Carte *> * arg)
{
    if(arg==NULL)
        arg=all_cards;
    std::vector<Carte *> *resultat = new std::vector<Carte *>();
    int i;
    for(i=0;i<(signed)arg->size();i++)
    {
        if(arg->at(i)->def >= d)
            resultat->push_back(arg->at(i));
    }
    return resultat;
}

std::vector<Carte *> * Parser::rechercher_attribut(int a,std::vector<Carte *> * arg)
{
    if(arg==NULL)
        arg=all_cards;
    std::vector<Carte *> *resultat = new std::vector<Carte *>();
    int i;
    for(i=0;i<(signed)arg->size();i++)
    {
        if(arg->at(i)->attribut == a)
            resultat->push_back(arg->at(i));
    }
    return resultat;
}

std::vector<Carte *> * Parser::rechercher_set(int s,std::vector<Carte *> * arg)
{
    if(arg==NULL)
        arg=all_cards;
    std::vector<Carte *> *resultat = new std::vector<Carte *>();
    int i;
    for(i=0;i<(signed)arg->size();i++)
    {
        if(arg->at(i)->set == s)
            resultat->push_back(arg->at(i));
    }
    return resultat;
}

std::vector<Carte *> * Parser::rechercher_sous_type(int ty,std::vector<Carte *> * arg)
{
    if(arg==NULL)
        arg=all_cards;
    std::vector<Carte *> *resultat = new std::vector<Carte *>();
    int i;
    for(i=0;i<(signed)arg->size();i++)
    {
        if(arg->at(i)->sous_type == ty)
            resultat->push_back(arg->at(i));
    }
    return resultat;
}

std::vector<Carte *> * Parser::rechercher_niveau(int n,std::vector<Carte *> * arg)
{
    if(arg==NULL)
        arg=all_cards;
    std::vector<Carte *> *resultat = new std::vector<Carte *>();
    int i;
    for(i=0;i<(signed)arg->size();i++)
    {
        if((signed)arg->at(i)->niveau >= n)
            resultat->push_back(arg->at(i));
    }
    return resultat;
}

std::vector<Carte *> * Parser::deck(QString s)
{
    int i;
    std::vector<Carte *> * resultat = new std::vector<Carte *>();
    QFile file(s);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
    QString line = in.readLine();
    while(!line.isNull())
    {
        if(!line.contains("#"))
        {
            for(i=0;i<(signed)all_cards->size();i++)
            {
                if(all_cards->at(i)->id == line.toInt())
                {
                   resultat->push_back(all_cards->at(i)->copie());
                   break;
                 }
            }
         }
        line = in.readLine();
     }
     file.close();
    return resultat;

}

Parser::~Parser()
{

}
