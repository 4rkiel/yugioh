#ifndef EDITEUR_DE_CARTE_H
#define EDITEUR_DE_CARTE_H

#include <QDialog>
#include <vector>
#include <QString>
#include <string>
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
#include <QPushButton>
#include <QTextEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QCompleter>
#include <QFileDialog>
#include <iostream>
#include <sstream>
#include <QShortcut>
#include <QMessageBox>

#include "../inc/carte.h"
#include "../inc/combo.h"
#include "../inc/spin.h"
#include "../inc/shadowButt.h"
#include "../inc/parser.h"

using namespace std;

enum GENRE
{
    MONSTRE,
    MAGIE,
    PIEGE
};

class CardEditor : public QFrame
{
    Q_OBJECT

    public:
        CardEditor(Parser* parser);
        ~CardEditor();

public slots:
        void sauvegarder();
        void selectImg();
        void slotAttribut();
        void slotNormal();
        void updateImg();
        void nameRandom();

private:
        void createMenu();
        void createHorizontalGroupBox();
        void createGridGroupBox();
        void createFormGroupBox();

        Parser* parse;
        std::vector<Carte*> *allCards;

        const QString imgRep = QCoreApplication::applicationDirPath()+"/img/img_attr/";
        QString absoluteUrlImage = imgRep + "DEFAULT.jpg";

        QGridLayout* layout;
        QGroupBox *formGroupBox;
        QTextEdit *bigEditor;

        QGridLayout * mainLayout;
        
        QLineEdit *nom;
        QLineEdit *description;
        QLineEdit *imageUrl;
        QShortcut *shortcut;
        Combo *genreCarte;
        Combo *typePrimaire;
        Combo *typeSecondaire;
        Combo *attribut;
        Combo *nrSet;
        Combo *effectBox;

        QPushButton *image;
        ShadowButt *buttonSave;

        Spin *ID;        
        Spin *spinAttaque;
        Spin *spinDefense;
        Spin *niveau;

        QAction *exitAction;
};

#endif // EDITEUR_DE_CARTE_H
