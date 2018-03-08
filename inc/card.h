#ifndef CARD
#define CARD

#include <QPushButton>

#include <QGridLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QPropertyAnimation>



class Card : public QPushButton {

    Q_OBJECT

    public: 
    Card();
    ~Card();

    public slots:
    void turnDef();

    private:
    bool posi;
    QGridLayout * layout;
    QGraphicsView * view;
    QGraphicsScene * scene;
    QGraphicsProxyWidget * proxy;

    QPropertyAnimation * anim;
};


#endif
