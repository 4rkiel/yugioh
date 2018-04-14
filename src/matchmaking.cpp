#include "../inc/matchmaking.h"

Matchmaking::Matchmaking(QObject *parent) : QObject(parent){

    // initialisation du socket
    socket=new QUdpSocket(this);
    adresse_bind=new QHostAddress(QHostAddress::AnyIPv6);
    socket->bind(*adresse_bind,9001);

    //on récolte l'adresse du serveur !

    QHostInfo host = QHostInfo::fromName("yugiohserver.ddns.net");

    if (host.error() != QHostInfo::NoError) {
        qDebug() << "Lookup failed:" << host.errorString();
        return;
    }

    int num_recup=0;
    if(host.addresses().at(0).toString().toStdString().find(".")!=std::string::npos)
        num_recup=1;

    adresse_serveur = new QHostAddress(host.addresses().at(num_recup));
    qDebug() << *adresse_serveur;

    //création du msg à envoyer au serveur
    quint16 port = 9000;
    QByteArray paquet;
    paquet.append("Hello du client");

    //envoi de msg au serveur
    socket->writeDatagram(paquet,*adresse_serveur,port);

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

void Matchmaking::cancelMatchmaking(){
    //création du msg à envoyer au serveur
    quint16 port = 9000;
    QByteArray paquet;
    paquet.append("Cancel");
    qDebug() << *adresse_serveur;

    //envoi de msg au serveur
    socket->writeDatagram(paquet,*adresse_serveur,port);
}

Matchmaking::~Matchmaking(){
    delete socket;
    delete adresse_bind;
    delete adresse_serveur;
}

