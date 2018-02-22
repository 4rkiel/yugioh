#ifndef CARTE_H
#define CARTE_H

#include<QString>

enum Etat
{
    RECTO,
    VERSO
};

class Carte
{
    public:

        Carte(QString carte_nom, QString carte_image);
        Carte(QString carte_nom);
        Carte();

        // Getteur / Setteur

        QString getCarte_nom() const;
        void setCarte_nom(const QString &value);

        QString getImage() const;
        void setImage(const QString &value);

        Etat getEtat() const;
        void setEtat(const Etat &value);

    private:

        QString carte_nom;
        QString image;

    protected:

        Etat etat; // recto / verso

};

#endif // CARTE_H
