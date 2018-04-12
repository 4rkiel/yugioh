#include "../inc/matchmaking.h"

Matchmaking::Matchmaking(QObject *parent) : QObject(parent){

    // initialisation du socket
    socket=new QUdpSocket(this);
    adresse_bind=new QHostAddress(QHostAddress::AnyIPv6);
    socket->bind(*adresse_bind,9001);

    QHostAddress adresse;
    //on indique l'adresse du serveur !

    adresse.setAddress("2001:660:4701:2001:50d9:1d4e:41f2:392b");

    //création du msg à envoyer au serveur
    quint16 port = 9000;
    QByteArray paquet;
    paquet.append("Hello du client");

    //envoi de msg au serveur
    socket->writeDatagram(paquet,QHostAddress::LocalHostIPv6,port);


    // attente réponse serveur

        // Si client (connexion)

            // Recuperer l'adresse de l'host dans la reponse

            // Faire :
            // emit sendIP(QString)


        // Si host (mise en attente)

            // Faire (avec sa propre adresse) :
            // emit createHost(QString)

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));



}


void Matchmaking::readyRead(){

    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    //le client reçoit la réponse du serveur et la stock
    socket->readDatagram(buffer.data(),buffer.size(),0,0);
    QString msgRec(buffer.data());

    //si le client reçoit "hote" il est l'hote
    if(msgRec=="hote"){
        emit createHost(adresse_bind->toString());
    }
    //sinon il est le client
    else{
        emit sendIP(msgRec);
    }

}

Matchmaking::~Matchmaking(){
    delete socket;
    delete adresse_bind;
}
