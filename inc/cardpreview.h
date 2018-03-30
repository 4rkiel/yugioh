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

        CardPreview(const Carte *carte);

    private:

        QHBoxLayout *mainLayout;

        QLabel *tabInfoLabel[INFOLABEL_MAX];

    signals:

        void rightClicked();
        void clicked();

    protected:

        void mousePressEvent(QMouseEvent *event) override;
};

#endif // CARDPREVIEW_H
