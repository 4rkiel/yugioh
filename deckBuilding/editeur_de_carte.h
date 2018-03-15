#ifndef EDITEUR_DE_CARTE_H
#define EDITEUR_DE_CARTE_H

#include "carte.h"
#include <QDialog>
#include <QtGui>
#include <QMenuBar>
#include <vector>
#include <QString>
#include <QDebug>
#include <ctime>

using namespace std;

class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;

enum GENRE
{
    MONSTRE,
    MAGIE,
    PIEGE
};

enum ATTRIBUT
{
    LUMIERE,
    TENEBRE,
    TERRE,
    EAU,
    FEU,
    VENT,
    DIVIN
};

class editeur_de_carte : public QDialog
{
    Q_OBJECT

    public:
        editeur_de_carte();

public slots:
        void sauvegarder();
        void slotAttribut();
private:
        void createMenu();
        void createHorizontalGroupBox();
        void createGridGroupBox();
        void createFormGroupBox();

        QString imgRep = QCoreApplication::applicationDirPath()+"/deckBuilding/img_attr/";

        QMenuBar *menuBar;
        QGroupBox *horizontalGroupBox;
        QGroupBox *gridGroupBox;
        QGroupBox *formGroupBox;
        QTextEdit *smallEditor;
        QTextEdit *bigEditor;
        QDialogButtonBox *buttonBox;
        QLineEdit *nom;
        QLineEdit *description;

        QComboBox *genreCarte;
        QComboBox *typePrimaire;
        QComboBox *typeSecondaire;
        QComboBox *attribut;
        QComboBox *type;
        QComboBox *nrSet;

        QSpinBox *ID;        
        QSpinBox *spinAttaque;
        QSpinBox *spinDefense;

        QComboBox *cb_categorie;
        QComboBox *cb_type;

        QMenu *fileMenu;
        QAction *exitAction;
};

#endif // EDITEUR_DE_CARTE_H
