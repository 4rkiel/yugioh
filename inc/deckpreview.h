#ifndef DECKPREVIEW
#define DECKPREVIEW

#include "carte.h"
#include <QBoxLayout>
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
#include "flatExpButt.h"

class DeckPreview : public QWidget
{
    Q_OBJECT

    enum infoLabel
    {
        NOM,
        VALIDE,
        INFOLABEL_MAX
    };

    public:

        DeckPreview(QString deck, QString img);

    private:

        QHBoxLayout *mainLayout;

        QString monDeck;

        QLabel tabInfoLabel[INFOLABEL_MAX];

    signals:

        void clicked(QString);

    protected:

        void mousePressEvent(QMouseEvent *event) override;
};

#endif // DECKPREVIEW
