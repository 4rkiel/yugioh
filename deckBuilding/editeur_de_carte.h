#ifndef EDITEUR_DE_CARTE_H
#define EDITEUR_DE_CARTE_H

#include "carte.h"
#include <QDialog>
#include <QtGui>
#include <QMenuBar>
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

        QMenu *fileMenu;
        QAction *exitAction;
};

#endif // EDITEUR_DE_CARTE_H
