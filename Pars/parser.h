#ifndef PARSER_H
#define PARSER_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <string.h>
#include <cstring>
class Parser : public QWidget
{
    Q_OBJECT

public:
    Parser(QWidget *parent = 0);
    int parser(std::string ligne);
    void recup_effet(std::string effets);
    ~Parser();
    int etape=0;
    std::string id;
    //std::string set;
    std::string genre;
    std::string sous_type;
    std::string nom;
    std::string attribut;
    std::string niveau;
    std::string type;
    std::string description="";
    std::string effet;
    std::string atk;
    std::string def;
    std::string hash;
    bool verif = true;

};

#endif // PARSER_H
