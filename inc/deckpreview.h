#ifndef DECKPREVIEW
#define DECKPREVIEW

#include "carte.h"

#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QString>

#include <QMouseEvent>
#include <QShortcut>


class DeckPreview : public QPushButton {

    Q_OBJECT

    public:

        QString nomDeck;

        DeckPreview(QString deck, QString img);
        ~DeckPreview();

    private:

        QGridLayout * layout;
        QLabel * pic;
        QLabel * name;
        QShortcut* shortcut;

    public slots:
   
        void doClick();
        
    signals:

        void isClick(QString);


};

#endif 
