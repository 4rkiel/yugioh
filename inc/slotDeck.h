#ifndef SLOTDECK
#define SLOTDECK

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QPushButton>

#include <QString>

class SlotDeck : public QGraphicsView {

    Q_OBJECT

    public: 
    SlotDeck();
    ~SlotDeck();
    void changeState(int sz);
    void draw();

    private:
    int size;
    QGraphicsScene * scene;
    QGraphicsProxyWidget * proxy;
    QPushButton * content;

};


#endif
