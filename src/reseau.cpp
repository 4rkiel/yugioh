#include "../inc/reseau.h"

Reseau::Reseau()
{
    socket = new QTcpSocket(this);
     connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
     connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
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

void Reseau::go(QString str)
{

    serveur = new QTcpServer(this);
    if(!serveur->listen(QHostAddress(str), 50885)){
        std::cout << "je connecte PAS le serveur" << std::endl;
    } else {
        std::cout << "je connecte le serveur" << std::endl;
    }

    connect(serveur, SIGNAL(newConnection()), this, SLOT(nouvelleConnexion()));
    tailleMessage2=0;
}

void Reseau::nouvelleConnexion()
{

     socket = serveur->nextPendingConnection();
      std::cout << "YEAAAAH MUNITION AU MAX!!" << std::endl;
      connect(socket,SIGNAL(readyRead()),this,SLOT(donneesRecues()));
      connect(socket,SIGNAL(disconnected()),this,SLOT(deconnexionClient()));
     // emit a_parser(QString("tt"));
    
    emit hostReady(21);
}

void Reseau::mondieu(QString str)
{
    socket->abort();
    
    connect(socket, SIGNAL(connected()), this, SLOT(sendOK()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
                    this, SLOT(sendERR(QAbstractSocket::SocketError)));

    socket->connectToHost(QHostAddress(str), 50885);
    //socket->connectToHost(QHostAddress(getIp()), 50885);
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
     std::cout << "j'ai reçu dans donnes Recues ";
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
}

void Reseau::connecte()
{
    std::cout << "la fin négro" << std::endl;
}

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

void Reseau::sendERR(QAbstractSocket::SocketError){
    emit connectKO(23);
}
