#ifndef SLOTCARD
#define SLOTCARD

#include <QGridLayout>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

#include <QPropertyAnimation>

#include <QPushButton>
#include <QString>



class SlotCard : public QPushButton {

Q_OBJECT

public: 
    SlotCard();
    ~SlotCard();
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
