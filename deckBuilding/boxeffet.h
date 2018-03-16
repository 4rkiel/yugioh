#ifndef BOXEFFET_H
#define BOXEFFET_H


class BoxEffet : public QComboBox
{
    Q_OBJECT

    public:
        BoxEffet();

        QComboBox *quoi, *qui, *joueur, *ou, *quand, *combien;
};

#endif // BOXEFFET_H
