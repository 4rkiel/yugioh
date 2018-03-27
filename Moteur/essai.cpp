//TESTE POUR VOIR A QUOI RESSEMBLERA LE COMBAT EN RESEAU
#include "essai.h"
#include "noyau.h"
#include "parser.h"
Essai::Essai(QWidget *parent)
    : QMainWindow(parent)
{
  /* env = new QPushButton("Envoyer un message",this);
    serv = new QPushButton(QString::fromUtf8("Créer un serveur"),this);
    ok = new QPushButton("Connecter la socket",this);
    ligne = new QLineEdit(this);
    QPushButton * ataq = new QPushButton("Attaque",this);
    QVBoxLayout * swag = new QVBoxLayout();
    QWidget* yolo = new QWidget();
    yolo->setLayout(swag);
    swag->addWidget(serv);
    swag->addWidget(ok);
    swag->addWidget(env);
    swag->addWidget(ataq);
    swag->addWidget(ligne);
    this->setCentralWidget(yolo);

    Noyau * test = new Noyau();
    test->setReseau(true);
    connect(serv,SIGNAL(clicked(bool)),test,SLOT(go()));
    connect(ok,SIGNAL(clicked(bool)),test,SLOT(mondieu()));
  //  connect(test->socket, SIGNAL(connected()), test, SLOT(connecte()));
   // connect(test->socket, SIGNAL(readyRead()), test, SLOT(donneesRecues()));
    connect(env,SIGNAL(clicked(bool)),test,SLOT(send()));
    connect(ataq,SIGNAL(clicked(bool)),test,SLOT(attaque()));
    connect(ligne,SIGNAL(returnPressed()),this,SLOT(commande()));
    connect(this,SIGNAL(emit_commande(QString)),test,SLOT(traiter(QString)));
//QPushButton * but = new QPushButton("yolo",this);*/
//this->setCentralWidget(but);
//connect(ataq,SIGNAL(clicked(bool)),this,SLOT(afficher()));

//connect(this,SIGNAL(emit_aff(Carte*)),test,SLOT(afficher(Carte*)));

    Parser* yolo = new Parser();
    std::vector<Carte *> * test = yolo->deck("/adhome/v/vc/vcostantino/Documents/IHM/PROJET/Version26/yugioh/deck/1.deck");
    int i;
    for(i=0;i<test->size();i++)
    {
        std::cout << "JE PARCOURS LE DECK" << std::endl;
           test->at(i)->afficher_infos();
    }
  // std::vector<Carte *> * what = yolo->rechercher_nom("magicien blanc");
   //std::cout << "description:" << what->at(0)->description.toStdString()<< std::endl;

}

void Essai::commande()
{
    emit Essai::emit_commande(ligne->text());
}

void Essai::afficher()
{
    emit Essai::emit_aff(new Carte(5,5));
}

Essai::~Essai()
{
    /*delete(Essai::terrain_adv);
    delete(Essai::terrain_moi);
    delete(Essai::main1);
    delete(Essai::main2);
    delete(Essai::d1);
    delete(Essai::d2);*/
}
