#ifndef CARD
#define CARD

#include <QPushButton>


class Card : public QPushButton {

    Q_OBJECT

    public: 
    Card();
    ~Card();

    public slots:
    void turnDef();

};


#endif
