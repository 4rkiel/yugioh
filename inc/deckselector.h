#ifndef DECKSELECTOR
#define DECKSELECTOR

#include <vector>

#include <QFrame>
#include <QGridLayout>

#include <QFile>
#include <QString>
#include <QStringList>

#include <QRadioButton>
#include <QShortcut>

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
#include "deckpreview.h"
//#include "flatExpButt.h"

class DeckSelector : public QFrame {

    Q_OBJECT

public:

    QString appPath = QCoreApplication::applicationDirPath();
    QString imgRep = appPath+"/img/img_attr/";
    QString defaultImage = imgRep + "DEFAULT.jpg";
    QString deckRep = appPath+"/deck/";

    
    QStringList deckList = QDir(deckRep).entryList({"*.deck"});
    unsigned int NBR_DECK = deckList.size();


    QGridLayout * mainLayout;


    std::vector<DeckPreview *> tabDeckButton;
    std::vector<QFrame *> tabSep;
    std::vector<QRadioButton *> tabRadio;


    DeckSelector(QObject*);
    ~DeckSelector();

    QString imgPreviewDeck(std::vector<Carte*> * deck);


public slots:

    void openDeck(QString);
    void abandonFocus();
    void getsFocus();

signals:

	void popDeck(QString);

};

#endif // DECKSELECTOR

