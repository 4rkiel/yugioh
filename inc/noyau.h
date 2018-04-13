#ifndef NOYAU_H
#define NOYAU_H
#include <QtNetwork>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <cstring>
#include "carte.h"
#include "reseau.h"
#include <string>
#include <QString>
#include <sstream>

class Noyau : public QWidget
{
    Q_OBJECT
public:
    Noyau();

    bool online;
    bool mon_tour;
    int tour;
    int phase;
    int selfLife;
    int foeLife;
    int aleatoire;
    int registre_0;
    std::vector<Carte *> * terrain;


    std::vector<Carte*> * d1;
    std::vector<Carte*> * d2;

    std::vector<Carte *> *cimetiere1;
    std::vector<Carte *> *cimetiere2;

    int nbrTick=0;
    bool lockTick = false;

    //comme son nom l'indique, init le noyau
    void init();

    /*comme son nom l'indique, permet de poser une carte à la position main_x
     * dans la main vers terrain_x sur le terrain,
     * def = true si carte en position defense, false sinon
     * vis = true si carte face recto, false sinon */
    void poser(int main_x, int terrain_x, bool def,bool vis);

    /*comme son nom l'indique, permet d'attaquer avec une carte
     * à la position attaquant_x vers la carte adverse en position
     * adversaire_x, si on attaque l'adversaire directement x = -1 */
    void attaquer(int attaquant_x, int adversaire_x=-1);

    /*comme son nom l'indique, change la position (atk/def) d'une carte
     * à la position terrain_x */
    void switch_position(int terrain_x);

    /*comme son nom l'indique, detruit la carte à la position x */
    void detruire(int x);


    /*comme son nom l'indique, passe à la phase_suivante
     * PAS ENCORE IMPLEMENTE */
    void phase_suivante();

    //FONCTIONS UTILE POUR D'AUTRES FONCTIONS, LEURS DESCRIPTIONS EST DANS LE CPP
    void enlever_x(std::vector<Carte *> **vect, int x);
    void enlever_i(std::vector<Carte *> **vect, int i);
    int perfect_terrain(int zone);
    int perfect_position(int zone);
    bool isAdv(int x);
    bool isMonst(int x);
    bool isMagic(int x);
    bool isHand(int x);
    bool isDeck(int x);
    bool isField(int x);
    bool isGrave(int x);
    bool isFuse(int x);
    void chargerDeck(int x);
    void deckAdverse(int x);
    Carte * trouver(int x);
    bool no_monster(int zone);
    bool can_poser();
    bool can_atak();
    bool can_switch();

    //obsolète
    Reseau * res;

public slots:
    //permet de piocher,x vaut 1 si c'est moi qui pioche sinon x vaut 76
    void piocher(int x);
    void go();
    void mondieu();
    void send();
    //obsolète
    void attaque();
    //sert à traiter les actions, voir commentaires cpp
    void traiter(QString s);
    //obsolète
    void setReseau(bool b);
    void poser_test(int x);
    void poserAtk();
    void poserDef();
    void donner_infos(int x);
    void attaquerSlot(int,int);
    void comptageTick();

signals:
    void emit_go();
    void emit_mondieu();
    void emit_send();
    void emit_attaque();
    void emit_charge_deck(QString contenu);
    void switch_pos(int x);
    void je_pioche();
    //void je_pose(QString img,int main_x,int terrain_x,bool def,bool vis);
    void j_attaque(int attaquant_x,int adversaire_x);
    void je_gagne();
    void je_perds();
    void e_deck(int x);
    void destruction(int x);
    void chat(QString);
    void visible(QString s,int x);
    void nonvis(int x);
    void defens(int x);
    void dialogue();
    void change_position(int x);
    void tiens(QString);
    void give_infos(QString,int,int,QString,int,QString,int,int);
    void giveLife(int x);
    void changeLife(int x,bool me);
    void setTour(int x);
    void sendInfo(QString i);
    void beginTour();
    void stopTick();

    //void met_en_defense(int x);
};


#endif
