#ifndef RESEAU_H
#define RESEAU_H
#include <QtNetwork>
#include <random>
#include <QWidget>
#include <iostream>
#include "../inc/carte.h"
#include <string>
#include <QString>
#include <sstream>
#include <QTcpSocket>
class Reseau : public QWidget
{
    Q_OBJECT

public:
    Reseau();
    QTcpSocket *socket;
    QTcpSocket * keep;
     quint16 tailleMessage=0;
     QTcpServer *serveur;
     QList<QTcpSocket *> clients;
     quint16 tailleMessage2=0;
     void envoyer(const QString &message);
    QString getIp();
     void parser(std::string s);
     QHostAddress adresse;
       int port;
       int port_k;
       bool alreadyinit=false;
       bool isAlive=true;
       int nbrtick=0;

public slots:
	 void sendOK();
	 void sendERR(QAbstractSocket::SocketError);
     void afficher(Carte* c);
     void nouvelleConnexion();
     void donneesRecues();
     void deconnexionClient();
     void go(QString);
     void connecte();
     void mondieu(QString);
     void donneesServ();
     void send();
     void attaque();
     void attaquer(int x,int y);
     void gagne();
     void piocher();
     void env_deck(int d);
     void poser(int main_x,int terrain_x,bool def);
     void change_pos(int x);
     void prochaine_phase();
     void ton_tour();
     void transmettre(QString chaine);
     //void keepAlive();
     //void alive();

signals:
    void a_parser(QString chaine);
	void hostReady(int);
	void connectOK(int);
    void connectKO(int);
    void hasDied();
};

#endif // RESEAU_H
