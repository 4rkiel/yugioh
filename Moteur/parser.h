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
#include <QDir>

class Parser : public QWidget
{
    Q_OBJECT

public:
    Parser(QWidget *parent = 0);

    QString fichier_courant;
    void recup_effet(std::string effets);
    ~Parser();

    int etape=0;
    int set;
    std::string effet="";

    Carte * courante;
    void getAll();

    std::string getSet(std::string nom);

    std::vector<Carte *> * all_cards;
    std::vector<Carte *> * rechercher_nom(std::string nom);
    std::vector<Carte *> * rechercher_sous_type(int ty);
    std::vector<Carte *> * rechercher_type(int ty);
    std::vector<Carte *> * rechercher_genre(int g);
    std::vector<Carte *> * rechercher_atk(int a);
    std::vector<Carte *> * rechercher_def(int d);
    std::vector<Carte *> * rechercher_attribut(int a);
    std::vector<Carte *> * rechercher_set(int s);
    std::vector<Carte *> * rechercher_niveau(int n);

    void parser(std::string ligne);
};

#endif // PARSER_H
