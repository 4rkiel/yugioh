#ifndef RESEAU_H
#define RESEAU_H
#include <QtNetwork>
#include <QWidget>
#include <iostream>
#include "carte.h"
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
     void go();
     void connecte();
     void mondieu();
     void donneesServ();
     void send();
     void attaque();
     void piocher();
     void poser(int main_x,int terrain_x,bool def);
signals:
    void a_parser(QString chaine);

};

#endif // RESEAU_H
