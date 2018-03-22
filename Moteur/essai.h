#ifndef ESSAI_H
#define ESSAI_H

//TESTE POUR VOIR A QUOI RESSEMBLERA LE COMBAT EN RESEAU


#include <QtNetwork>
#include <QMainWindow>
#include <iostream>
#include <vector>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHostAddress>
#include "noyau.h"
#include "carte.h"
#include <QLineEdit>
class Essai : public QMainWindow
{
    Q_OBJECT

public:
    Essai(QWidget *parent = 0);
    ~Essai();

    QPushButton * serv;
    QPushButton * ok;
    QPushButton * env;
    QLineEdit * ligne;
    void getIp();
public slots:
     void afficher();
     void commande();
signals:
    void emit_commande(QString text);
    void emit_aff(Carte* c);
};


#endif // CARTE_H



