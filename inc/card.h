#ifndef CARD
#define CARD

#include <QPushButton>

#include <QGridLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QPropertyAnimation>

#include <QString>


class Card : public QGraphicsView {

    Q_OBJECT

    public: 
    Card();
    ~Card();
    void setContent(QString str);

    public slots:
    void turn();

    private:
    bool posi;
    
    QGraphicsScene * scene;
    QGraphicsProxyWidget * proxy;

    QPushButton * content;

    QPropertyAnimation * rotAnim;
    QPropertyAnimation * scaleAnim;
};


#endif
