#include "parser.h"
#include "carte.h"
#include "QCoreApplication"
Parser::Parser(QWidget *parent)
    : QWidget(parent)
{
    courante = new Carte();
    all_cards = new std::vector<Carte*>();
    QStringList list = QDir("/adhome/v/vc/vcostantino/DocumentsLinux/Documents/IHM/PROJET/sets/").entryList();
    int i;
    std::cout << "je suis ici" << std::endl;
    for(i=0;i<list.length();i++)
    {

        if((list.at(i).compare(QString("."))!=0) && (list.at(i).compare(QString(".."))!=0))
        {
            std::cout << "je parcours la list" << list.at(i).toStdString() << std::endl;
            fichier_courant = "/adhome/v/vc/vcostantino/DocumentsLinux/Documents/IHM/PROJET/sets/"+list.at(i);
        getAll();
        }
    }
    for(i=0;i<all_cards->size();i++)
    {
        std::cout << "je parcours la list" << std::endl;
           all_cards->at(i)->afficher_infos();
    }
       std::vector<Carte *> * search = rechercher_nom("Drag");
       std::cout << "J'AI TROUVE" << std::endl;
       for(i=0;i<search->size();i++)
           search->at(i)->afficher_infos();
    /*
    QFile fichier("/adhome/v/vc/vcostantino/Documents/IHM/PROJET/yugioh.set");
    fichier.open(QFile::ReadOnly | QFile::Text);
     QTextStream in(&fichier);
      QString line = in.readLine();
       Carte * plus;
       while(!line.isNull())
     {

        parser(line.toStdString());
        line = in.readLine();
        //if(etape==12)
     //       plus = new Carte(nom);
     }
       fichier.close();
       std::cout << "nom : " << plus->carte_nom.toStdString() << std::endl;
       std::cout << "ID " << id << "genre: " << genre << std::endl;
       std::vector<Carte *> * yolo = Parser::rechercher("or");
       std::cout << yolo->at(0)->carte_nom.toStdString() << std::endl;
       std::cout << yolo->at(1)->carte_nom.toStdString() << std::endl;*/
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
        if(etape==12)
        {
             all_cards->push_back(courante);
         }
        line = in.readLine();
     }
     file.close();
    return;
}

//PERMET DE RECUPERER LES EFFETS SOUS FORME DE STRING QUI DEVRONT ETRE EUX MEMES MODIFIES
void Parser::recup_effet(std::string effets)
{
    char * arg = new char[effets.length()+1];
    std::strcpy(arg,effets.c_str());
    char * parcourir = std::strtok(arg,"{{");
    std::string vrai;
    if(parcourir!=NULL)
     vrai = parcourir;
    while(parcourir!=NULL)
    {

                std::cout << "parc" << parcourir << " vrai:"<< vrai << std::endl;
                effet=effet+vrai;
                parcourir = std::strtok(NULL,"{{");
                if(parcourir!=NULL)
                   vrai = parcourir;

    }
    delete(arg);
}


//PARSE UNE LIGNE COMME IL FAUT
void Parser::parser(std::string ligne)
{
    if(etape==12)
     {
        etape=0;
        effet="";
        courante = new Carte();
    }

    if(ligne.empty() || ligne.find(" ")==0)
        return;

    if(ligne.find("##")==std::string::npos)
    {
        std::cout << ligne << std::endl;
        switch(etape)
        {
            case 0:
                courante->id = atoi(ligne.c_str());
                //courante->image = truc du fichier + id;
                //courante->set = truc
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
                    recup_effet(ligne);
                    etape++;
                 }
                break;
            case 8:
                recup_effet(ligne);
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
std::vector<Carte *> * Parser::rechercher_nom(std::string nom)
{
    std::vector<Carte *> *resultat = new std::vector<Carte *>();
    int i;
    for(i=0;i<all_cards->size();i++)
    {
        if(all_cards->at(i)->nom.contains(QString::fromStdString(nom)))
            resultat->push_back(all_cards->at(i));
    }
    return resultat;
}

std::vector<Carte *> * Parser::rechercher_type(int ty)
{
    std::vector<Carte *> *resultat = new std::vector<Carte *>();
    int i;
    for(i=0;i<all_cards->size();i++)
    {
        if(all_cards->at(i)->type == ty)
            resultat->push_back(all_cards->at(i));
    }
    return resultat;
}

std::vector<Carte *> * Parser::rechercher_genre(int g)
{
    std::vector<Carte *> *resultat = new std::vector<Carte *>();
    int i;
    for(i=0;i<all_cards->size();i++)
    {
        if(all_cards->at(i)->genre == g)
            resultat->push_back(all_cards->at(i));
    }
    return resultat;
}

std::vector<Carte *> * Parser::rechercher_atk(int a)
{
    std::vector<Carte *> *resultat = new std::vector<Carte *>();
    int i;
    for(i=0;i<all_cards->size();i++)
    {
        if(all_cards->at(i)->atk >= a)
            resultat->push_back(all_cards->at(i));
    }
    return resultat;
}

std::vector<Carte *> * Parser::rechercher_def(int d)
{
    std::vector<Carte *> *resultat = new std::vector<Carte *>();
    int i;
    for(i=0;i<all_cards->size();i++)
    {
        if(all_cards->at(i)->def >= d)
            resultat->push_back(all_cards->at(i));
    }
    return resultat;
}

std::vector<Carte *> * Parser::rechercher_attribut(int a)
{
    std::vector<Carte *> *resultat = new std::vector<Carte *>();
    int i;
    for(i=0;i<all_cards->size();i++)
    {
        if(all_cards->at(i)->attribut == a)
            resultat->push_back(all_cards->at(i));
    }
    return resultat;
}
Parser::~Parser()
{

}