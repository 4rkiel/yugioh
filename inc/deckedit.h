#ifndef DECKEDIT_H
#define DECKEDIT_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include "flatButt.h"
#include <QPushButton>
#include <QTextEdit>
#include "combo.h"
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
#include <QShortcut>
#include <QScrollArea>
#include <vector>
#include <QMessageBox>
#include <QStringListModel>
#include "carte.h"
#include "parser.h"
#include "duplica.h"
#include "cardlistpreview.h"

#define NBR_CARTE_DECK_VISU 40 // multiple de 10
#define NBR_CARTE_EXTRA_DECK 10

class deckEdit : public QWidget
{
    enum buttonDeckEdit
    {
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
        TOUS,
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

        const QStringList buttonName = {tr("Mélanger"),
                                        tr("Trier"), tr("Effacer"),
                                        tr("Enregistrer"), tr("Créer"),
                                        tr("Supprimer"), tr("Annuler"),
                                        tr("Filtrer")};
        const QStringList genreList = {tr("Tous"), tr("Monstre"), tr("Magie"), tr("Piège")};
        const QStringList sousGenreList = {tr("Tous"), tr("Effet"), tr("Normal"),
                                           tr("Fusion"), tr("Toon"),
                                           tr("Rituel")};
        const QStringList attributList = {};

        deckEdit(std::vector<Carte*> *allCard);

    private:
        void createEdit();

        void updateDeckVisu();

        void updateDeckVisuLastCard();

        void updateExtraDeckVisu();

        void updateExtraDeckVisuLastCard();

        int indiceCarteDeck = 0;
        int nbrCarteMonstre = 0;
        int nbrCarteMagie = 0;
        int nbrCartePiege = 0;

        int indiceCarteExtraDeck = 0;

        std::vector<Carte*> deck;
        std::vector<Carte*> extraDeck;

        std::vector<Carte*> *allCards;

        Combo *selectDeck;
        Combo *choixGenre;
        Combo *choixSousGenre;
        Combo *choixAttribut;
        Combo *choixType;
        QShortcut *shortcut;

        QLineEdit *newDeck;
        QLineEdit *textSearch;

        QSpinBox *spinNiveau;
        QSpinBox *spinAtk;
        QSpinBox *spinDef;

        CardListPreview *cardList;

        FlatButt *effectBoxBut;
        FlatButt *tabBut[NBR_BUTTON_DECK_EDIT];
        std::vector<QPushButton *> tabCardVisu;
        std::vector<QPushButton *> tabExtraDeck;

        QLabel *deckLabel;
        QLabel *infoMonstreLabel;
        QLabel *infoMagieLabel;
        QLabel *infoPiegeLabel;
        QLabel *infoFusionLabel;


    signals:

    public slots:
            void slotAttribut();
            void addCard2Deck(Carte* carte);
            void rmvCard2Deck();
            void sauvegarder();
            void creer();
            void effacerDeck();
            void melangerDeck();
            void trierDeck();
            void updPreview();
            void clearSearch();
            void loadDeck();
};

#endif // DECKEDIT_H
