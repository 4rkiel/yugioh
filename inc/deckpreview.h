#ifndef DECKPREVIEW
#define DECKPREVIEW

#include "carte.h"

#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QString>

#include <QMouseEvent>


class DeckPreview : public QPushButton {

    Q_OBJECT

    public:

        DeckPreview(QString deck, QString img);
        ~DeckPreview();

    private:

        QGridLayout * layout;
        QLabel * pic;
        QLabel * name;

    public slots:
   
        void doClick();
        
    signals:

        void isClick(QString);


};

#endif 
