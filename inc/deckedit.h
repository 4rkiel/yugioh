#ifndef DECKEDIT_H
#define DECKEDIT_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QCompleter>
#include <QFileDialog>
#include <QCoreApplication>
#include <QStringList>
#include <QDebug>
#include <algorithm>
#include <QMargins>

#define NBR_CARTE_DECK_VISU 60 // multiple de 10
#define NBR_CARTE_EXTRA_DECK 15

class deckEdit : public QWidget
{
    enum buttonDeckEdit
    {
        QUITTER,
        MELANGER,
        TRIER,
        EFFACER,
        SAUVER,
        CREER,
        SUPPRIMER,
        ANNULER_RECHERCHE,
        FILTRER,
        NBR_BUTTON_DECK_EDIT
    };

    enum GENRE
    {
        MONSTRE,
        MAGIE,
        PIEGE
    };

    Q_OBJECT

    public:
        const QString appPath = QCoreApplication::applicationDirPath();
        const QString imgRep = appPath+"/img/img_attr/";
        const QString defaultImage = imgRep + "DEFAULT.jpg";
        const QString deckRep = appPath+"/deck/";

        const QStringList buttonName = {tr("Quitter"), tr("Mélanger"),
                                        tr("Trier"), tr("Effacer"),
                                        tr("Sauvegarder"), tr("Créer"),
                                        tr("Supprimer"), tr("Annuler"),
                                        tr("Filtrer")};
        const QStringList genreList = {"Monstre", tr("Magie"), tr("Piège")};
        const QStringList sousGenreList = {tr("Effet"), tr("Normal"),
                                           tr("Fusion"), tr("Toon"),
                                           tr("Rituel")};
        const QStringList attributList = {};

        explicit deckEdit();

    private:
        void createEdit();

        QComboBox *selectDeck;
        QComboBox *choixGenre;
        QComboBox *choixSousGenre;
        QComboBox *choixAttribut;
        QComboBox *choixType;

        QLineEdit *newDeck;
        QLineEdit *textSearch;

        QSpinBox *spinNiveau;
        QSpinBox *spinAtk;
        QSpinBox *spinDef;



        QPushButton *effectBoxBut;
        QPushButton *tabBut[NBR_BUTTON_DECK_EDIT];
        QPushButton *tabCardVisu[NBR_CARTE_DECK_VISU];
        QPushButton *tabExtraDeck[NBR_CARTE_EXTRA_DECK];

    signals:

    public slots:
            void slotAttribut();
};

#endif // DECKEDIT_H
