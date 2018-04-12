#ifndef DECKSELECTOR
#define DECKSELECTOR

#include "carte.h"
#include <QBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMouseEvent>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QStringList>
#include <QWidget>
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QGraphicsDropShadowEffect>
#include <vector>
#include <QPixmap>
#include <QFrame>
#include "deckpreview.h"
#include "flatExpButt.h"
#include "parser.h"
#include "QPushButton"
#include "deckedit.h"

class DeckSelector : public QWidget
{
    Q_OBJECT

    QString imgPreviewDeck(std::vector<Carte *> *deck);
public:

    const QString appPath = QCoreApplication::applicationDirPath();
    const QString imgRep = appPath+"/img/img_attr/";
    const QString defaultImage = imgRep + "DEFAULT.jpg";
    const QString deckRep = appPath+"/deck/";

    const QStringList deckList = QDir(deckRep).entryList({"*.deck"});

    const unsigned int NBR_DECK = deckList.size();

    QVBoxLayout *mainLayout;

    Parser leParser;

    std::vector<DeckPreview*> tabDeckButton;
    std::vector<QFrame*> tabSep;
    //std::vector<QPushButton*> tabDeckButton;

    DeckSelector();

public slots:
    void openDeck(QString nomDeck);
};

#endif // DECKSELECTOR

