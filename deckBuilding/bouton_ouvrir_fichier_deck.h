#ifndef BOUTON_OUVRIR_FICHIER_DECK_H
#define BOUTON_OUVRIR_FICHIER_DECK_H

#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <unistd.h>
#include <iostream>
#include <QColorDialog>
#include <QDebug>
#include <QLineEdit>
#include <string>
#include <QtGui>
#include <iostream>
#include <fstream>
#include <ostream>

class bouton_ouvrir_fichier_deck : public QPushButton
{
    Q_OBJECT
public:
    bouton_ouvrir_fichier_deck();

public slots:
        void selecteur();
};

#endif // BOUTON_OUVRIR_FICHIER_DECK_H
