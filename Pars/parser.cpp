#include "parser.h"

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
}

void Parser::recup_effet(std::string effets)
{
    char * arg = new char[effets.length()+1];
    std::strcpy(arg,effets.c_str());
    char * parcourir = std::strtok(arg,"{{");
    while(parcourir!=NULL)
    {
std::cout << "parc" << parcourir << std::endl;
parcourir = std::strtok(NULL,"{{");
    }
    delete(arg);
}

int Parser::parser(std::string ligne)
{
    if(etape==12)
        etape=0;
    if(ligne.empty() || ligne.find(" ")==0)
        return 0;
    if(ligne.find("##")==std::string::npos)
  {  std::cout << ligne << std::endl;
    switch(etape)
    {
        case 0:
            id=ligne;
             break;
            //LE SET N'EST PAS A INCLURE !!!!!!!!!!!!!
        case 1:
            genre=ligne;
        break;
    case 2:
        sous_type=ligne;
    break;
    case 3:
        nom=ligne;
    break;
    case 4:
        attribut=ligne;
    break;
    case 5:
        niveau=ligne;
    break;
    case 6:
        type=ligne;
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
        atk=ligne;
    break;
    case 10:
        def=ligne;
        break;
    default:
        break;
    }
    etape++;
    }
}

Parser::~Parser()
{

}
