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
#include <QFileInfo>

#include "carte.h"
#include "parser.h"
#include "duplica.h"
#include "cardlistpreview.h"
#include "darkButt.h"
#include "combo.h"
#include "flatButt.h"


#define NBR_CARTE_DECK_VISU 40 // multiple de 10
#define NBR_CARTE_EXTRA_DECK 10
#define TAILLE_UNDO 50

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
        ~deckEdit();
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

        QHBoxLayout *mainLayout;
        QVBoxLayout *mainL1;
        QVBoxLayout *mainL2;

        QHBoxLayout *attrLayout;

        QVBoxLayout *deckVisuLayout;
        QVBoxLayout *layoutRechercheCarteAdv;

        QFrame *editCreate;
        QFrame *frameNomDeck;
        QFrame *cardFilterAdv;
        QGridLayout *nomLayout;
        QLineEdit*nomDeck;
        DarkButt *supprDeck;
        DarkButt *plusBut;

        QFrame *stealBut;
        QGridLayout *cachayLayout;
        DarkButt *shuffleDeck;
        DarkButt *sortDeck;
        DarkButt *eraseDeck;
        DarkButt *undo;
        DarkButt *redo;
        DarkButt *butClearSearch;

        DarkButt *plusFiltrBut;


        QVBoxLayout *editCreateLayout;

        QFrame *cardFilter;
        QGridLayout *layoutRechercheCarte;
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
        std::vector< std::vector<Carte*> > redoList;


        Combo *selectDeck;
        Combo *choixGenre;
        Combo *choixSousGenre;
        Combo *choixAttribut;
        Combo *choixType;
        QShortcut *shortcut;
        QShortcut *shortcutRedo;
        QShortcut *shortcutRedo2;

        QLineEdit *newDeck;
        QLineEdit *textSearch;

        QSpinBox *spinNiveau;
        QSpinBox *spinAtk;
        QSpinBox *spinDef;

        CardListPreview *cardList;

        QPushButton *effectBoxBut;
        std::vector<QPushButton *> tabCardVisu;
        std::vector<QPushButton *> tabExtraDeck;

        QLabel *deckLabel;
        QLabel *infoMonstreLabel;
        QLabel *infoMagieLabel;
        QLabel *infoPiegeLabel;
        QLabel *infoFusionLabel;

        QLabel *genreLabel;
        QLabel *attrLabel;

        QSizePolicy sp_retain_choixGenre;
        QSizePolicy sp_retain_cachay;

        bool fileExists(QString path);
        int nrFichierSansNom = 0;
signals:

    public slots:
            void slotAttribut();
            void addCard2Deck(Carte* carte);
            void rmvCard2Deck();
            void sauvegarder();
            void sauvegarderDiscretionMax();
            void creer();
            void effacerDeck();
            void melangerDeck();
            void trierDeck();
            void updPreview();
            void clearSearch();
            void loadDeck();
            void obliterationDuDeck();

            void plus2But();
            void slotUndo();
            void slotRedo();
            void toujoursPlus2But();
};

#endif // DECKEDIT_H
