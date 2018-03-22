#ifndef PARSER_H
#define PARSER_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <string.h>
#include <cstring>
#include <vector>
#include <carte.h>

class Parser : public QWidget
{
    Q_OBJECT

public:
    Parser(QWidget *parent = 0);

    void recup_effet(std::string effets);
    ~Parser();
    int etape=0;
    int id;
    //std::string set;
    int genre;
    int sous_type;
    QString nom;
    attribut attr;
    int niveau;
    type ty ;
    std::string description="";
    std::string effet="";
    int atk;
    int def;
    bool verif = true;

    std::vector<Carte *> * all_cards;

    std::vector<Carte *> * rechercher(std::string nom);
    std::vector<Carte *> * rechercher(std::string nom);

    int parser(std::string ligne);
};

#endif // PARSER_H
