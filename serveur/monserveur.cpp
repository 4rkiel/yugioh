#include "monserveur.h"

MonServeur::MonServeur(QObject *parent) : QObject(parent){

    adresse_hote=new QHostAddress;
    port_hote=new quint16;
    socket=new QUdpSocket(this);

    //on fixe l'adresse serveur
    socket->bind(QHostAddress("192.168.2.16"),9000);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

}

void MonServeur::readyRead(){

    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());
    QByteArray buffer2;

    QHostAddress sender;
    quint16 senderPort;

    //le serveur reçoit le message d'un client et le stock avec ses coordonnées

    socket->readDatagram(buffer.data(),buffer.size(),&sender,&senderPort);

    //si pas d'hote, on stock ses coordonnées
    if((adresse_hote->toString()).isEmpty()){
        *adresse_hote=sender;
        *port_hote=senderPort;
    }
    //si hote, on envoie à chaque client leurs rôles
    else{
        buffer2.append("hote");
        socket->writeDatagram(buffer2,*adresse_hote,*port_hote);

        buffer2.clear();
        buffer2.append(adresse_hote->toString());
        socket->writeDatagram(buffer2,sender,senderPort);
        adresse_hote->clear();

    }

}
