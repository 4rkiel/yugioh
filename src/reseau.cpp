#include "../inc/reseau.h"

Reseau::Reseau()
{
    socket = new QTcpSocket(this);
    keep = new QTcpSocket(this);
    socket->setSocketOption(QAbstractSocket::KeepAliveOption,1);
     connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
     //connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
     connect(keep,SIGNAL(readyRead()),this,SLOT(alive()));
}

QString Reseau::getIp()
{
    QHostInfo hostInfo = QHostInfo::fromName(QHostInfo::localHostName());
    QList<QHostAddress> interfaceAddressList = QNetworkInterface::allAddresses();

    QString hostIpStr;
    foreach(QHostAddress addr, interfaceAddressList){
    if(addr.protocol() == QAbstractSocket::IPv6Protocol && !addr.toString().startsWith("fe80")){
            hostIpStr = addr.toString();
        }
    }
    std::cout << "au final j'ai " << hostIpStr.toStdString() << std::endl;
return hostIpStr;
}


/*void Reseau::alive()
{
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;

    keep->readDatagram(buffer.data(), buffer.size(),
                         &sender, &senderPort);
    std::cout << "====================== J'AI RECU UN IMALIVE =========================" << std::endl;
    isAlive=true;
}*/

/*void Reseau::keepAlive()
{
    //std::cout << "je suis entré dans le keep et nbrtick ="<< nbrtick << std::endl;
    nbrtick++;
    if(nbrtick==50)
    {
        std::cout << "================ J'ENVOIE UN KEEP A "<<adresse.toString().toStdString() << " SUR "<< port_k << "=============" << std::endl;
        QByteArray paquet;
        paquet.append(QString("ImAlive"));
        keep->writeDatagram(paquet,adresse,port_k);
    }
    if(nbrtick==100)
    {
        if(isAlive)
        {
            std::cout << "=================== IS ALIVE ====================" << std::endl;
            isAlive = false;
        }
        else
         {
            std::cout << "================= HAS DIED =============" << std::endl;
            emit hasDied();
        }
         nbrtick = 0;
    }


}*/

void Reseau::go(QString str)
{
    serveur = new QTcpServer(this);
    //serveur = new QTcpServer(this);
        //socket->open(QIODevice::ReadWrite);
    if(!serveur->listen(QHostAddress(str), 50885)){
        std::cout << "je connecte PAS le serveur" << std::endl;
    } else {
        std::cout << "je connecte le serveur" << std::endl;
    }

    connect(serveur, SIGNAL(newConnection()), this, SLOT(nouvelleConnexion()));
    //keep->bind(QHostAddress(str),50881);
    //port_k=50880;
    //tailleMessage2=0;
}

void Reseau::nouvelleConnexion()
{

     socket = serveur->nextPendingConnection();
      //std::cout << "YEAAAAH MUNITION AU MAX!!" << std::endl;
      connect(socket,SIGNAL(readyRead()),this,SLOT(donneesRecues()));
      connect(socket,SIGNAL(disconnected()),this,SLOT(deconnexionClient()));
     // emit a_parser(QString("tt"));
    emit a_parser(QString("init"));
    emit hostReady(21);
}

void Reseau::mondieu(QString str)
{
    socket->abort();
    
    connect(socket, SIGNAL(connected()), this, SLOT(sendOK()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
                    this, SLOT(sendERR(QAbstractSocket::SocketError)));
    //std::cout << "Je vais write" << std::endl;
   // QString message("MEESSSSSSSSSSSSSSSSSSSAAAAAAAAAAAAGGGGGEEEEEEEEEEE");
    //QByteArray paquet;
    //paquet.append("init");
   // QDataStream out(&paquet, QIODevice::WriteOnly);
    //out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    //out << message; // On ajoute le message à la suite
    //out.device()->seek(0); // On se replace au début du paquet
    //out << (quint16) (paquet.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message
    adresse = QHostAddress(str);
    port = 50885;
    std::cout << "je tente de me co à " << str.toStdString() << " et port:" << port << std::endl;
    // Envoi du paquet préparé à tous les clients connectés au serveur
    //socket->bind(50886);
    //socket->writeDatagram(paquet,adresse,port);
    //keep->bind(50880);
    //port_k=50881;
     //emit hostReady(21);
      connect(socket,SIGNAL(readyRead()),this,SLOT(donneesRecues()));
    socket->connectToHost(adresse, port);

}

void Reseau::donneesServ()
{
    std::cout << "je suis dans donnesRecues !!" << std::endl;
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) // Si par hasard on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
        return;

    // Si tout va bien, on continue : on récupère le message
    QDataStream in(socket);

    if (tailleMessage2 == 0) // Si on ne connaît pas encore la taille du message, on essaie de la récupérer
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16)) // On n'a pas reçu la taille du message en entier
             return;

        in >> tailleMessage2; // Si on a reçu la taille du message en entier, on la récupère
    }

    // Si on connaît la taille du message, on vérifie si on a reçu le message en entier
    if (socket->bytesAvailable() < tailleMessage2) // Si on n'a pas encore tout reçu, on arrête la méthode
        return;


    // Si ces lignes s'exécutent, c'est qu'on a reçu tout le message : on peut le récupérer !
    QString message;
    in >> message;


    // 2 : on renvoie le message à tous les clients
    std::cout << message.toStdString() << std::endl;
    tailleMessage2 = 0;
}

void Reseau::donneesRecues()
{
     /*std::cout << "j'ai reçu dans donnes Recues ";
     QByteArray datagram;
     while (socket->hasPendingDatagrams()) {
         datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(),datagram.size());
        QDataStream in(&datagram,QIODevice::ReadOnly);
        QString yolo;
        in >> yolo;
        std::cout << "j'ai reçu " << yolo.toStdString();
     }*/
    // when data comes in
   /* QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;*/

    // qint64 QUdpSocket::readDatagram(char * data, qint64 maxSize,
    //                 QHostAddress * address = 0, quint16 * port = 0)
    // Receives a datagram no larger than maxSize bytes and stores it in data.
    // The sender's host address and port is stored in *address and *port
    // (unless the pointers are 0).

  /*  socket->readDatagram(buffer.data(), buffer.size(),
                         &sender, &senderPort);

    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << QString(buffer.data());
    if((QString(buffer.data()).compare(QString("init"))==0) && !alreadyinit)
       {
        std::cout << "MON DIEU CA MARCHE " << std::endl;
        adresse = QHostAddress(sender.toString());
        port = senderPort;
        alreadyinit = true;
        emit hostReady(21);

    }
    emit a_parser(QString(buffer.data()));*/
    QDataStream in(socket);
    if (tailleMessage == 0)
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
           {
            std::cout << "Je return après verif bytes avaible < sizeof" << std::endl;
            return;
        }


        in >> tailleMessage;
    }

    // Si on arrive jusqu'à cette ligne, on peut récupérer le message entier
    QString messageRecu;
    in >> messageRecu;

    // On affiche le message sur la zone de Chat
    std::cout << "j'ai reçu ceci " << messageRecu.toStdString() << std::endl;
    emit a_parser(messageRecu);
    //parser(messageRecu.toStdString());
    // On remet la taille du message à 0 pour pouvoir recevoir de futurs messages
    tailleMessage = 0;
}

void Reseau::deconnexionClient()
{
    std::cout << "Grievous a quitté le navire" << std::endl;
    emit hasDied();
}

void Reseau::connecte()
{
    std::cout << "je suis co" << std::endl;
    emit hostReady(21);
    envoyer("init");
}

/*void Reseau::envoyer(const QString &message)
{
    std::cout << "J'ENVOIE UN TRUC:" << message.toStdString() << std::endl;
    QByteArray paquet;
    paquet.append(message);
     socket->writeDatagram(paquet,adresse,port);
}*/



void Reseau::envoyer(const QString &message)
{
    std::cout << "JE VAIS ENVOYER " << std::endl;
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
        out << message; // On ajoute le message à la suite
        out.device()->seek(0); // On se replace au début du paquet
        out << (quint16) (paquet.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message

    // Envoi du paquet préparé à tous les clients connectés au serveur
    socket->write(paquet);
    socket->flush();

 //   socket->waitForBytesWritten(-1);
}

void Reseau::transmettre(QString chaine)
{
        envoyer(chaine);
}

//obsolète
void Reseau::parser(std::string s)
{
    if(s[0]=='a')
        std::cout << "wooooow" << std::endl;
    else if(s.compare("jpioche"))
        std::cout << "JE PIOCHE" << std::endl;

}

void Reseau::afficher(Carte* c)
{
    std::cout << "atk:" << c->atk << std::endl;
}


void Reseau::send()
{
    envoyer("J'envoie ce magnifique message");
}

void Reseau::attaque()
{
    envoyer("a1000-1");
}

void Reseau::poser(int main_x, int terrain_x, bool def)
{
    QString chaine ="p/";
    std::stringstream ss2;
    ss2 << Carte::correspondant(main_x);
    ss2 << "/";
    ss2 << Carte::correspondant(terrain_x);
    ss2 << "/";
    std::string fin = ss2.str();
    chaine = chaine + QString(fin.c_str());
    if(def)
      chaine = chaine + "1";
    else
        chaine = chaine + "0";
    envoyer(chaine);
}

void Reseau::attaquer(int x,int y)
{
    QString chaine ="a/";
    std::stringstream ss2;
    ss2 << Carte::correspondant(x);
    ss2 << "/";
    ss2 << Carte::correspondant(y);
    std::string fin = ss2.str();
    chaine = chaine + QString(fin.c_str());

    envoyer(chaine);
}

void Reseau::gagne()
{
    envoyer("g");
}

void Reseau::piocher()
{
    envoyer("apioche");
}

void Reseau::env_deck(int d)
{
    QString chaine ="d/";
    std::stringstream ss2;
    ss2 << d;
    std::string fin = ss2.str();
    chaine = chaine + QString(fin.c_str());

    envoyer(chaine);
}

void Reseau::change_pos(int x)
{
    QString chaine ="swap/";
    std::stringstream ss2;
    ss2 << Carte::correspondant(x);
    std::string fin = ss2.str();
    chaine = chaine + QString(fin.c_str());

    envoyer(chaine);
}

void Reseau::prochaine_phase()
{
    envoyer("np");
}

void Reseau::ton_tour()
{
    envoyer("tt");
}


void Reseau::sendOK(){
    emit connectOK(22);
}

void Reseau::sendERR(QAbstractSocket::SocketError erreur){
    emit connectKO(23);
    switch(erreur) // On affiche un message différent selon l'erreur qu'on nous indique
        {
            case QAbstractSocket::HostNotFoundError:
                std::cout << "ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.</em>" << std::endl;
                break;
            case QAbstractSocket::ConnectionRefusedError:
                std::cout << "ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.</em>" << std::endl;
                break;
            case QAbstractSocket::RemoteHostClosedError:
                std::cout << "<em>ERREUR : le serveur a coupé la connexion.</em>" << std::endl;
                break;
            default:
                std::cout << "<em>ERREUR : " + socket->errorString().toStdString() << std::endl;
        }
}
