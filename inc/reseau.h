#ifndef RESEAU_H
#define RESEAU_H
#include <QtNetwork>
#include <QWidget>
#include <iostream>
#include "../inc/carte.h"
#include <string>
#include <sstream>
class Reseau : public QWidget
{
    Q_OBJECT
public:
    Reseau();
    QTcpSocket *socket;
     quint16 tailleMessage=0;
     QTcpServer *serveur;
     QList<QTcpSocket *> clients;
     quint16 tailleMessage2=0;
     void envoyer(const QString &message);
     void parser(std::string s);
public slots:
     void afficher(Carte* c);
     void nouvelleConnexion();
     void donneesRecues();
     void deconnexionClient();
     void go(QString);
     void connecte();
     void mondieu();
     void donneesServ();
     void send();
     void attaque();
     void attaquer(int x,int y);
     void gagne();
     void piocher();
     void env_deck(int d);
     void poser(int main_x,int terrain_x,bool def);
     void change_pos(int x);
signals:
    void a_parser(QString chaine);
	void hostReady(int);

};

#endif // RESEAU_H
