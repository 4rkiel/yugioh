#include "parser.h"
#include "carte.h"
#include "carte_monstre.h"
Parser::Parser(QWidget *parent)
    : QWidget(parent)
{
    QFile fichier("/adhome/v/vc/vcostantino/Documents/IHM/PROJET/yugioh.set");
    fichier.open(QFile::ReadOnly | QFile::Text);
     QTextStream in(&fichier);
      QString line = in.readLine();
       while(!line.isNull())
     {

        parser(line.toStdString());
        line = in.readLine();
     }
       fichier.close();
       std::cout << "ID " << id << "genre: " << genre << std::endl;
       std::vector<Carte *> * yolo = Parser::rechercher("or");
       std::cout << yolo->at(0)->carte_nom.toStdString() << std::endl;
       std::cout << yolo->at(1)->carte_nom.toStdString() << std::endl;
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
int Parser::parser(std::string ligne)
{
    if(etape==12)
     {
        etape=0;
        effet="";
        description="";
    }
    if(ligne.empty() || ligne.find(" ")==0)
        return 0;
    if(ligne.find("##")==std::string::npos)
  {  std::cout << ligne << std::endl;
    switch(etape)
    {
        case 0:
            id= atoi(ligne.c_str());
             break;
        case 1:
            genre=atoi(ligne.c_str());
        break;
    case 2:
        sous_type=atoi(ligne.c_str());
    break;
    case 3:
        nom=QString::fromStdString(ligne);
    break;
    case 4:
        attr=(attribut) atoi(ligne.c_str());
    break;
    case 5:
        niveau=atoi(ligne.c_str());
    break;
    case 6:
        ty=(type) atoi(ligne.c_str());
    break;
    case 7:
        if(ligne.find("{{")==std::string::npos)
        {
                description = description+ligne;
                 etape--;
        }

        else
          {  recup_effet(ligne);
            etape++;
          }
    break;
    case 8:
        recup_effet(ligne);
    break;
     case 9:
        atk=atoi(ligne.c_str());
    break;
    case 10:
        def=atoi(ligne.c_str());
        break;
    default:
        break;
    }
    etape++;
    }
}

//PERMET DE RECHERCHER DES CARTES DONT LE NOM EST NOM
std::vector<Carte *> * Parser::rechercher(std::string nom)
{
    std::vector<Carte *> *resultat = new std::vector<Carte *>();
    //INDIQUER LE BON ENDROIT DU FICHIER
    QFile fichier("/adhome/v/vc/vcostantino/Documents/IHM/PROJET/yugioh.set");
    fichier.open(QFile::ReadOnly | QFile::Text);
     QTextStream in(&fichier);
      QString line = in.readLine();
       while(!line.isNull())
     {

        int yolo = Parser::parser(line.toStdString());
        if(etape==12 && Parser::nom.toStdString().find(nom)!=std::string::npos)
        {
            if(Parser::genre==0)
             resultat->push_back(new carte_monstre(Parser::nom,QString("yolo"),LUMIERE,DRAGON));
             //GERER LES AUTRES CARTES (PIEGE,MAGIE,..)
  }
        line = in.readLine();
     }
       fichier.close();
    return resultat;
}
Parser::~Parser()
{

}
