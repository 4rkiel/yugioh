#ifndef EDITEUR_DE_CARTE_H
#define EDITEUR_DE_CARTE_H

#include <QDialog>
#include <QtGui>
#include <QMenuBar>
#include <vector>
#include <QString>
#include <string>
#include <QDebug>
#include <ctime>
#include <QList>
#include <algorithm>
#include <fstream>
#include <QFrame>
#include <QAction>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QTextEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QCompleter>
#include <QFileDialog>
#include <iostream>
#include "shadowButt.h"
#include <sstream>

using namespace std;

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
        void selectImg();
        void slotAttribut();
        void slotNormal();
        void updateImg();

private:
        void createMenu();
        void createHorizontalGroupBox();
        void createGridGroupBox();
        void createFormGroupBox();

        const QString imgRep = QCoreApplication::applicationDirPath()+"/img/img_attr/";

        QGroupBox *formGroupBox;
        QTextEdit *bigEditor;
        QFrame *buttonBox;

        QLineEdit *nom;
        QLineEdit *description;
        QLineEdit *imageUrl;

        QComboBox *genreCarte;
        QComboBox *typePrimaire;
        QComboBox *typeSecondaire;
        QComboBox *attribut;
        QComboBox *type;
        QComboBox *nrSet;
        QComboBox *effectBox;

        QPushButton *image;

        QSpinBox *ID;        
        QSpinBox *spinAttaque;
        QSpinBox *spinDefense;
        QSpinBox *niveau;

        QAction *exitAction;
};

#endif // EDITEUR_DE_CARTE_H
