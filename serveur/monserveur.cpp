#include "monserveur.h"

MonServeur::MonServeur(QObject *parent) : QObject(parent){

    socket=new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHostIPv6,9000);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

}

void MonServeur::readyRead(){

    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    //le serveur reçoit le message d'un client et le stock avec ses coordonnées
    socket->readDatagram(buffer.data(),buffer.size(),&sender,&senderPort);
    QString msgRec(buffer.data());
    std::cout << msgRec.toStdString() << std::endl;

    //le serveur répond au client
    QByteArray Data;
    Data.append("Hello du serveur");
    socket->writeDatagram(Data,sender,senderPort);

}
