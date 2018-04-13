#include "monserveur.h"

MonServeur::MonServeur(QObject *parent) : QObject(parent){

    adresse_hote=new QHostAddress;
    port_hote=new quint16;
    socket=new QUdpSocket(this);

    QHostInfo host = QHostInfo::fromName("yugiohserver.ddns.net");

    if (host.error() != QHostInfo::NoError) {
        qDebug() << "Lookup failed:" << host.errorString();
        return;
    }

    adresse_serveur = new QHostAddress(host.addresses().at(0));
    qDebug() << *adresse_serveur;

    //on fixe l'adresse serveur
    if(!socket->bind(*adresse_serveur,9000)){
        std::cout << "bug" << std::endl;
    }

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

    //si c'est un cancel, on supprime l'hôte
    QString msgRec(buffer.data());
    qDebug()<<msgRec;
    if(msgRec=="Cancel" && sender==*adresse_hote){
        adresse_hote->clear();
    }

    //si pas d'hote, on stock ses coordonnées
    else if((adresse_hote->toString()).isEmpty()){
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
    qDebug()<<*adresse_hote;

}

MonServeur::~MonServeur(){
    delete adresse_hote;
    delete socket;
    delete port_hote;
    delete adresse_serveur;
}
