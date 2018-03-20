#include "essai.h"

Essai::Essai(QWidget *parent)
    : QMainWindow(parent)
{
    env = new QPushButton("Env",this);
    serv = new QPushButton("Yolo",this);
    ok = new QPushButton("Swag",this);
    socket = new QTcpSocket(this);
    QPushButton * ataq = new QPushButton("Attaque",this);
    QVBoxLayout * swag = new QVBoxLayout();
    QWidget* yolo = new QWidget();
    yolo->setLayout(swag);
    swag->addWidget(serv);
    swag->addWidget(ok);
    swag->addWidget(env);
    swag->addWidget(ataq);
    this->setCentralWidget(yolo);
    terrain_moi = new std::vector<Carte*>();
    terrain_adv = new std::vector<Carte*>();

    int i;
    for(i=0;i<5;i++)
    {
        terrain_moi->push_back(new Carte(-1,-1));
        terrain_adv->push_back(new Carte(-1,-1));
    }
    std::cout << "size :" << terrain_moi->size() << std::endl;
    d1 = new std::vector<Carte*>();
    d2 = new std::vector<Carte*>();

    d1->push_back(new Carte(1000,100));
    d1->push_back(new Carte(200,100));
    d1->push_back(new Carte(300,100));
    d1->push_back(new Carte(400,100));
    d1->push_back(new Carte(500,100));


    d2->push_back(new Carte(200,100));
    d2->push_back(new Carte(400,100));
    d2->push_back(new Carte(600,100));
    d2->push_back(new Carte(800,100));
    d2->push_back(new Carte(1000,100));

    main1= new std::vector<Carte *>();
    main2= new std::vector<Carte *>();

    piocher(2);
   std::cout << "size deck " << d1->size() << std::endl;
    std::cout << main1->at(0)->atk << std::endl;
    std::cout << main1->at(1)->atk << std::endl;
    std::cout << d1->front()->atk << std::endl;

   poser(0,1,false);

    // std::cout << "what" << main1->at(0)->atk << std::endl;
    poser(0,2,false);
 //std::cout << "euh2 ?" << std::endl;
    //std::cout << "yolo" << terrain_moi->at(1)->atk << std::endl;
adversaire_piocher(2);
adversaire_poser(0,1,false);
std::cout << "MAIN:" << main2->size() << std::endl;
adversaire_poser(0,2,false);
std::cout << "MAIN:" << main2->size() << std::endl;
    attaquer(1,2);
        std::cout << foeLife << std::endl;
       std::cout << "normalement j'affiche ça" << terrain_adv->at(2)->atk  << std::endl;
    connect(serv,SIGNAL(clicked(bool)),this,SLOT(go()));
    connect(ok,SIGNAL(clicked(bool)),this,SLOT(mondieu()));
    connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(env,SIGNAL(clicked(bool)),this,SLOT(send()));
    connect(ataq,SIGNAL(clicked(bool)),this,SLOT(attaque()));
}



void Essai::piocher(int n)
{
    int i;
    for(i=0;i<n;i++)
    {
            Carte* debut = d1->front();
            main1->push_back(debut);
            enlever_i(&d1,0);
    }
    return;
}

void Essai::poser(int main_x, int terrain_x, bool def)
{
       terrain_moi->at(terrain_x)=main1->at(main_x);
       terrain_moi->at(terrain_x)->pos=def;
       enlever_i(&main1,main_x);
}

void Essai::adversaire_poser(int main_x,int terrain_x, bool def)
{
    terrain_adv->at(terrain_x)=main2->at(main_x);
    terrain_adv->at(terrain_x)->pos=def;

    enlever_i(&main2,main_x);
}

void Essai::poser(int sac1_x, int sac2_x, int main_x, int terrain_x, bool def)
{
  detruire_moi(sac1_x);
   detruire_moi(sac2_x);
   terrain_moi->at(terrain_x) = main1->at(main_x);
   main1->erase(main1->begin()+main_x-1);

}

void Essai::adversaire_piocher(int n)
{
    int i;
    for(i=0;i<n;i++)
    {
            Carte* debut = d2->front();
            main2->push_back(debut);
            enlever_i(&d2,0);
    }
    return;
}


void Essai::attaquer(int moi_x, int adversaire_x)
{
    if(adversaire_x==-1)
        std::cout << "You're already dead." << std::endl;
    else
    {
           if(terrain_moi->at(moi_x)->atk > terrain_adv->at(adversaire_x)->def)
           {

                foeLife = foeLife - (terrain_moi->at(moi_x)->atk - terrain_adv->at(adversaire_x)->def);
                detruire_adversaire(adversaire_x);

           }
           else
                  return;
    }
}

void Essai::se_faire_attaquer(int adversaire_x,int moi_x)
{
    if(moi_x==-1)
        std::cout << "You're already dead." << std::endl;
    else
    {
           if(terrain_adv->at(adversaire_x)->atk > terrain_moi->at(moi_x)->def)
           {

                selfLife = selfLife - (terrain_adv->at(adversaire_x)->atk - terrain_moi->at(moi_x)->def);
                detruire_adversaire(adversaire_x);

           }
           else
                  return;
    }
}
void Essai::switch_position(int terrain_x)
{
    terrain_moi->at(terrain_x)->pos = !(terrain_moi->at(terrain_x)->pos);
}

void Essai::switch_position_adv(int terrain_x)
{
    terrain_adv->at(terrain_x)->pos = !(terrain_adv->at(terrain_x)->pos);
}

void Essai::detruire_moi(int x)
{
       terrain_moi->at(x) = new Carte(-1,-1);
}

void Essai::detruire_adversaire(int x)
{
    terrain_adv->at(x) = new Carte(-1,-1);
}

void Essai::enlever_i(std::vector<Carte *> **vect, int i)
{
    std::vector<Carte *>* res = new std::vector<Carte *>();
    if((*vect)->size()==1)
    {
        *vect = res;
        return;
    }
   int j;
   for(j=0;j<i;j++)
   {
      res->push_back((*vect)->at(j));
   }
   for(j=i+1;j<(*vect)->size();j++)
   {
        res->push_back((*vect)->at(j));
   }
    *vect = res;
}

void Essai::phase_suivante()
{
    if(phase==5)
        phase=1;
    else
        phase++;
}

void Essai::go()
{
    serveur = new QTcpServer(this);
    if(!serveur->listen(QHostAddress::Any, 50885))
    std::cout << "je connecte PAS le serveur" << std::endl;
    else
         std::cout << "je connecte le serveur" << std::endl;
    connect(serveur, SIGNAL(newConnection()), this, SLOT(nouvelleConnexion()));

    tailleMessage2=0;
}

void Essai::nouvelleConnexion()
{

     socket = serveur->nextPendingConnection();
      std::cout << "YEAAAAH MUNITION AU MAX!!" << std::endl;
      connect(socket,SIGNAL(readyRead()),this,SLOT(donneesServ()));
}

void Essai::mondieu()
{
    socket->abort();
    socket->connectToHost("127.0.0.1", 50885);
}

void Essai::donneesServ()
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

void Essai::donneesRecues()
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
    parser(messageRecu.toStdString());
    // On remet la taille du message à 0 pour pouvoir recevoir de futurs messages
    tailleMessage = 0;
}

void Essai::deconnexionClient()
{
    return;
}

void Essai::connecte()
{
    std::cout << "la fin négro" << std::endl;
}

void Essai::envoyer(const QString &message)
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

void Essai::parser(std::string s)
{
    if(s[0]=='a')
        std::cout << "wooooow" << std::endl;
}

void Essai::send()
{
    envoyer("YOLO PUTAIN ENVOIE CE MESSAGE BORDEL DE MERDE");
}

void Essai::attaque()
{
    envoyer("a1000-1");
}

Carte::Carte(int a,int d)
{
    atk=a;
    def=d;
}

Essai::~Essai()
{
    delete(Essai::terrain_adv);
    delete(Essai::terrain_moi);
    delete(Essai::main1);
    delete(Essai::main2);
    delete(Essai::d1);
    delete(Essai::d2);
}
