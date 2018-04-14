#ifndef DECKEDIT_H
#define DECKEDIT_H

#include <QFrame>
#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QSpinBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QCompleter>
#include <QFileDialog>
#include <QCoreApplication>
#include <QStringList>
#include <algorithm>
#include <QMargins>
#include <QShortcut>
#include <QScrollArea>
#include <vector>
#include <QMessageBox>
#include <QStringListModel>
#include <QGraphicsDropShadowEffect>

#include "carte.h"
#include "parser.h"
#include "duplica.h"
#include "cardlistpreview.h"
#include "darkButt.h"
#include "combo.h"
#include "flatButt.h"


#define NBR_CARTE_DECK_VISU 40 // multiple de 10
#define NBR_CARTE_EXTRA_DECK 10

class deckEdit : public QFrame {

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

        deckEdit(std::vector<Carte*> *allCard, QString nomDuDeck);
        QString deckName;
        QString newDeckName;

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

        QVBoxLayout *mainLayout;
        QHBoxLayout *mainL1;
        QHBoxLayout *mainL2;

        QVBoxLayout *deckVisuLayout;

        QFrame *editCreate;
        QFrame *frameNomDeck;
        QGridLayout *nomLayout;
        QLineEdit*nomDeck;
        DarkButt *supprDeck;
        DarkButt *plusBut;

        QFrame *stealBut;
        QGridLayout *cachayLayout;
        DarkButt *shuffleDeck;
        DarkButt *sortDeck;
        DarkButt *eraseDeck;


        QVBoxLayout *editCreateLayout;

        QFrame *cardFilter;
        QHBoxLayout *colonne;
        QFrame *propFilter;
        QFormLayout *propForm;
        QHBoxLayout *genreColonne;
        QVBoxLayout *prop2Vmain;
        QHBoxLayout *prop2H;
        QVBoxLayout *deleteSearch;
        QHBoxLayout *annSearch;
        QScrollArea *deckScroll;

        QHBoxLayout *part1;
        QVBoxLayout *part2;

        QFrame *cardInfo;
        QHBoxLayout *layoutInfo;
        QFrame *deckVisu;
        QGridLayout *layoutCard;

        QHBoxLayout *buttonH;

        std::vector<Carte*> deck;
        std::vector<Carte*> extraDeck;

        std::vector<Carte*> *allCards;

        std::vector< std::vector<Carte*> > undoList;


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

        QPushButton *effectBoxBut;
        std::vector<QPushButton *> tabBut;
        std::vector<QPushButton *> tabCardVisu;
        std::vector<QPushButton *> tabExtraDeck;

        QLabel *deckLabel;
        QLabel *infoMonstreLabel;
        QLabel *infoMagieLabel;
        QLabel *infoPiegeLabel;
        QLabel *infoFusionLabel;


        void sauvegarderDiscretionMax();
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

            void plus2But();
};

#endif // DECKEDIT_H
