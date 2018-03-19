#ifndef ESSAI_H
#define ESSAI_H
#include <QtNetwork>
#include <QMainWindow>
#include <iostream>
#include <vector>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHostAddress>
class Carte
{
public:
    int atk;
    int def;
    bool pos;
    Carte(int a,int d);
    Carte();

};

class Essai : public QMainWindow
{
    Q_OBJECT

public:
    Essai(QWidget *parent = 0);
    ~Essai();
    QTcpSocket *socket; // Représente le serveur
    quint16 tailleMessage=0;
    QTcpServer *serveur;
    QList<QTcpSocket *> clients;
    quint16 tailleMessage2=0;
    QPushButton * serv;
    QPushButton * ok;
    QPushButton * env;
    bool online;
    int tour;
    int phase=1;
    int selfLife=4000;
    int foeLife=4000;
    void piocher(int n);
    void poser(int main_x, int terrain_x, bool def);
    void poser(int sac_x,int main_x,int terrain_x, bool def);
    void poser(int sac1_x, int sac2_x, int main_x, int terrain_x,bool def);
    void attaquer(int moi_x, int adversaire_x=-1);
    void se_faire_attaquer(int adversaire_x,int moi_x=-1);
    void switch_position(int terrain_x);
    void detruire_moi(int x);
    void phase_suivante();
    void detruire_adversaire(int x);
    void adversaire_poser(int main_x,int terrain_x, bool def);
    void adversaire_piocher(int n);
    void switch_position_adv(int terrain_x);
    void enlever_i(std::vector<Carte *> **vect, int i);


    void envoyer(const QString &message);


    std::vector<Carte *> * terrain_moi;
    std::vector<Carte *> * terrain_adv;

    std::vector<Carte *> * main1;
    std::vector<Carte *> * main2;


    std::vector<Carte*> * d1;
    std::vector<Carte*> * d2;

public slots:
    void nouvelleConnexion();
    void donneesRecues();
    void deconnexionClient();
    void go();
    void connecte();
    void mondieu();
    void donneesServ();
    void send();
};





#endif // ESSAI_H
