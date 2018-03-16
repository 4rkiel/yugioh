#include "boxeffet.h"

BoxEffet::BoxEffet()
{
    QStringList quoiList;
    quoiList << "Bannir"  << "Detruire" << "Mode defense" << "Mode attaque" << "Modifier attaque" << "Modifier defense" << "Piocher";

    QStringList quiList;
    quiList << "Monstre"  << "Magie" << "Piege";

    QStringList joueurList;
    joueurList << "Joueur" << "Adversaire";

    QStringList ouList;
    ouList << "Terrain"  << "Main" << "Cimetiere";

    QStringList quandList;
    quandList << "Invocation d'un monstre" << "A l'activation" << "Subit_Attaque" << "Libre" << "Activation magie" << "Activation piege" << "Activation monstre";



    quoi = new QComboBox; // detruire               point d'attaque
    qui = new QComboBox; // monstre                 monstre
    joueur  = new QComboBox; // adversaire          moi
    ou = new QComboBox; // cimetière        +500
    quand = new QComboBox; // invocation            activation
    combien = new QComboBox;



}

