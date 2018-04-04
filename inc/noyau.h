#ifndef NOYAU_H
#define NOYAU_H
#include <QtNetwork>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <cstring>
#include "carte.h"
#include "reseau.h"


class Noyau : public QWidget
{
    Q_OBJECT
public:
    Noyau();
    void init();
    bool online;
    int tour;
    int phase=1;
    int selfLife=4000;
    int foeLife=4000;
    //void piocher(int n);
    void poser(int main_x, int terrain_x, bool def,bool vis);
    void poser(int sac_x,int main_x,int terrain_x, bool def);
    void poser(int sac1_x, int sac2_x, int main_x, int terrain_x,bool def);
    void attaquer(int attaquant_x, int adversaire_x=-1);
    void switch_position(int terrain_x);
    void detruire(int x);
    void phase_suivante();
    void adversaire_poser(int main_x,int terrain_x, bool def);
    void adversaire_piocher(int n);
    void switch_position_adv(int terrain_x);
    void enlever_x(std::vector<Carte *> **vect, int x);
    void enlever_i(std::vector<Carte *> **vect, int i);
    void chargerDeck(int x);
    Carte * trouver(int x);
    int perfect_position(int zone);

    std::vector<Carte *> * terrain;


    std::vector<Carte*> * d1;
    std::vector<Carte*> * d2;

    std::vector<Carte *> *cimetiere1;
    std::vector<Carte *> *cimetiere2;
    Reseau * res;
    void deckAdverse(int x);
public slots:
    void piocher(int x);
    void go();
    void mondieu();
    void send();
    void attaque();
    void traiter(QString s);
    void setReseau(bool b);

signals:
    void emit_go();
    void emit_mondieu();
    void emit_send();
    void emit_attaque();
    void emit_charge_deck(QString contenu);
    void switch_pos(int x);
    void je_pioche();
    void je_pose(QString img,int main_x,int terrain_x,bool def,bool vis);
    void j_attaque(int attaquant_x,int adversaire_x);
    void je_gagne();
    void e_deck(int x);
    void destruction(int x);
    void chat(QString);
    void visible(QString s,int x);
    void nonvis(int x);
    void defens(int x);
};


#endif
