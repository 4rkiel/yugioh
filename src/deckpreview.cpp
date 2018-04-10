#include "../inc/deckpreview.h"

DeckPreview::DeckPreview(QString deck ,int idCarte, const std::vector<Carte *>& allCard)
{
    QHBoxLayout mainLayout;

    monDeck = deck;

    QString image = QCoreApplication::applicationDirPath() + "img/card.svg";

    for(Carte* carte : allCard)
    {
        if(carte->id == idCarte)
        {
            image = carte->image;
            break;
        }
    }

    QPixmap monImage(image);

    QString name = deck;
    name.chop(5);

    FlatExpButt preview(monImage, name);

    mainLayout.addWidget(&preview);

    setLayout(&mainLayout);
}

void DeckPreview::mousePressEvent (QMouseEvent * e)
{
    if (e->button() == Qt::LeftButton || e->button() == Qt::RightButton )
    {
        emit clicked(monDeck);
    }
}

