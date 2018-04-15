#ifndef CARDPREVIEW_H
#define CARDPREVIEW_H

#include "carte.h"
#include <QBoxLayout>
#include <QFormLayout>
#include <QMouseEvent>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QStringList>
#include <QWidget>
#include <QDebug>

class CardPreview : public QWidget
{
    Q_OBJECT

    enum infoLabel
    {
        NOM,
        GENRE,
        NIVEAU,
        ATK,
        DEF,
        INFOLABEL_MAX
    };

    public:

        Carte *maCarte;
        CardPreview(Carte *carte);

    private:

        QHBoxLayout *mainLayout;

        QVBoxLayout *info;
        QLabel *imageLabel;

        QLabel *tabInfoLabel[INFOLABEL_MAX];

    signals:

        void clicked(Carte*);

    protected:

        void mousePressEvent(QMouseEvent *event) override;
};

#endif // CARDPREVIEW_H
