#ifndef SLOTDECK
#define SLOTDECK

#include <QGridLayout>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

#include <QPropertyAnimation>

#include <QPushButton>
#include <QString>



class SlotDeck : public QPushButton {

Q_OBJECT

public: 
    SlotDeck();
    ~SlotDeck();
    void resizeEvent (QResizeEvent*);
    void setPic(QString str);

public slots:
    void turn();

private:
    bool posi;
    QString url;

    QGridLayout * layout;

    QGraphicsView * view;
    QGraphicsScene * scene;
    QGraphicsProxyWidget * proxy;

    QPushButton * imgButt;
    
    QPropertyAnimation * rotAnim;
    QPropertyAnimation * scaleAnim;
};


#endif
