#ifndef DECKSELECTOR
#define DECKSELECTOR

#include <vector>

#include <QWidget>
#include <QVBoxLayout>

#include <QFile>
#include <QString>
#include <QStringList>

/*
#include <QBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QMouseEvent>
#include <QLabel>
#include <QPixmap>
#include <QGraphicsDropShadowEffect>
#include <QPixmap>
#include <QFrame>
#include "QPushButton"
*/

#include "carte.h"
#include "deckedit.h"
#include "parser.h"
#include "deckpreview.h"
//#include "flatExpButt.h"

class DeckSelector : public QWidget{

    Q_OBJECT

public:

    Parser leParser;
    
    QString appPath = QCoreApplication::applicationDirPath();
    QString imgRep = appPath+"/img/img_attr/";
    QString defaultImage = imgRep + "DEFAULT.jpg";
    QString deckRep = appPath+"/deck/";

    
    QStringList deckList = QDir(deckRep).entryList({"*.deck"});
    unsigned int NBR_DECK = deckList.size();


    QVBoxLayout * mainLayout;


    std::vector<DeckPreview*> tabDeckButton;
    std::vector<QFrame*> tabSep;


    DeckSelector();
    ~DeckSelector();

    QString imgPreviewDeck(std::vector<Carte*> * deck);


public slots:

    void openDeck(QString nomDeck);


};

#endif // DECKSELECTOR

