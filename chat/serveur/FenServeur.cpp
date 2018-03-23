#include "FenServeur.h"

FenServeur::FenServeur()
{
    // Cr�ation et disposition des widgets de la fen�tre
    etatServeur = new QLabel;
    boutonQuitter = new QPushButton(tr("Quitter"));
    connect(boutonQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(etatServeur);
    layout->addWidget(boutonQuitter);
    setLayout(layout);

    setWindowTitle(tr("ZeroChat - Serveur"));

    // Gestion du serveur
    serveur = new QTcpServer(this);
    if (!serveur->listen(QHostAddress::Any, 50885)) // D�marrage du serveur sur toutes les IP disponibles et sur le port 50585
    {
        // Si le serveur n'a pas �t� d�marr� correctement
        etatServeur->setText(tr("Le serveur n'a pas pu �tre d�marr�. Raison :<br />") + serveur->errorString());
    }
    else
    {
        // Si le serveur a �t� d�marr� correctement
        etatServeur->setText(tr("Le serveur a �t� d�marr� sur le port <strong>") + QString::number(serveur->serverPort()) + tr("</strong>.<br />Des clients peuvent maintenant se connecter."));
        connect(serveur, SIGNAL(newConnection()), this, SLOT(nouvelleConnexion()));
    }

    tailleMessage = 0;
}

void FenServeur::nouvelleConnexion()
{
    envoyerATous(tr("<em>Un nouveau client vient de se connecter</em>"));

    QTcpSocket *nouveauClient = serveur->nextPendingConnection();
    clients << nouveauClient;

    connect(nouveauClient, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(nouveauClient, SIGNAL(disconnected()), this, SLOT(deconnexionClient()));
}

void FenServeur::donneesRecues()
{
    // 1 : on re�oit un paquet (ou un sous-paquet) d'un des clients

    // On d�termine quel client envoie le message (recherche du QTcpSocket du client)
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) // Si par hasard on n'a pas trouv� le client � l'origine du signal, on arr�te la m�thode
        return;

    // Si tout va bien, on continue : on r�cup�re le message
    QDataStream in(socket);

    if (tailleMessage == 0) // Si on ne conna�t pas encore la taille du message, on essaie de la r�cup�rer
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16)) // On n'a pas re�u la taille du message en entier
             return;

        in >> tailleMessage; // Si on a re�u la taille du message en entier, on la r�cup�re
    }

    // Si on conna�t la taille du message, on v�rifie si on a re�u le message en entier
    if (socket->bytesAvailable() < tailleMessage) // Si on n'a pas encore tout re�u, on arr�te la m�thode
        return;


    // Si ces lignes s'ex�cutent, c'est qu'on a re�u tout le message : on peut le r�cup�rer !
    QString message;
    in >> message;


    // 2 : on renvoie le message � tous les clients
    envoyerATous(message);

    // 3 : remise de la taille du message � 0 pour permettre la r�ception des futurs messages
    tailleMessage = 0;
}

void FenServeur::deconnexionClient()
{
    envoyerATous(tr("<em>Un client vient de se d�connecter</em>"));

    // On d�termine quel client se d�connecte
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) // Si par hasard on n'a pas trouv� le client � l'origine du signal, on arr�te la m�thode
        return;

    clients.removeOne(socket);

    socket->deleteLater();
}

void FenServeur::envoyerATous(const QString &message)
{
    // Pr�paration du paquet
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0; // On �crit 0 au d�but du paquet pour r�server la place pour �crire la taille
    out << message; // On ajoute le message � la suite
    out.device()->seek(0); // On se replace au d�but du paquet
    out << (quint16) (paquet.size() - sizeof(quint16)); // On �crase le 0 qu'on avait r�serv� par la longueur du message


    // Envoi du paquet pr�par� � tous les clients connect�s au serveur
    for (int i = 0; i < clients.size(); i++)
    {
        clients[i]->write(paquet);
    }

}
