#include "../inc/deckpreview.h"

DeckPreview::DeckPreview(QString deck ,QString img)
{
    mainLayout = new QHBoxLayout;

    monDeck = deck;
    deck.chop(5);

    qDebug() << "creation bouton edition "+ monDeck + " alias " + deck;

    QPixmap image(img);
    image.scaled (QSize(200, 180), Qt::KeepAspectRatio);

    FlatExpButt *preview = new FlatExpButt(image, deck);
    preview->setToolTip(tr("Editer le deck ")+deck);
    mainLayout->addWidget(preview);



    setLayout(mainLayout);
}

void DeckPreview::mousePressEvent (QMouseEvent * e)
{
    if (e->button() == Qt::LeftButton || e->button() == Qt::RightButton )
    {
        emit clicked(monDeck);
    }
}

