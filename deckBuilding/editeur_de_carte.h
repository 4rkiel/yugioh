#ifndef EDITEUR_DE_CARTE_H
#define EDITEUR_DE_CARTE_H

#include "carte.h"
#include <QDialog>
#include <QtGui>
#include <QMenuBar>
#include <vector>
#include <QString>
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;

enum { NumGridRows = 3, NumButtons = 4 };

class editeur_de_carte : public QDialog
{
    Q_OBJECT

    public:
        editeur_de_carte();

public slots:
        void sauvegarder();
private:
        void createMenu();
        void createHorizontalGroupBox();
        void createGridGroupBox();
        void createFormGroupBox();



        QMenuBar *menuBar;
        QGroupBox *horizontalGroupBox;
        QGroupBox *gridGroupBox;
        QGroupBox *formGroupBox;
        QTextEdit *smallEditor;
        QTextEdit *bigEditor;
        QLabel *labels[NumGridRows];
        QLineEdit *lineEdits[NumGridRows];
        QPushButton *buttons[NumButtons];
        QDialogButtonBox *buttonBox;

        QLineEdit *nom;
        QLineEdit *description;

        QComboBox *genreCarte;
        QComboBox *sousGenreCarte;
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
