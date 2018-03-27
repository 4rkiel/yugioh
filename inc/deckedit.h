#ifndef DECKEDIT_H
#define DECKEDIT_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>
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
        NBR_BUTTON_DECK_EDIT
    };

    Q_OBJECT

    public:
        explicit deckEdit();

        const QString appPath = QCoreApplication::applicationDirPath();
        const QString imgRep = appPath+"/img/img_attr/";
        const QString deckRep = appPath+"/deck/";
        const QStringList buttonName = {tr("Quitter"), tr("Mélanger"), tr("Trier"),
                                        tr("Effacer"), tr("Sauvegarder"), tr("Créer"),
                                        tr("Supprimer")};

    private:
        void createEdit();

        QComboBox *selectDeck;
        QLineEdit *newDeck;
        QPushButton *tabBut[NBR_BUTTON_DECK_EDIT];

    signals:

    public slots:
};

#endif // DECKEDIT_H
