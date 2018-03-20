#ifndef SLOTCARD
#define SLOTCARD

#include <QGridLayout>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

#include <QPropertyAnimation>

#include <QPushButton>
#include <QString>

#include <QEvent>


class SlotCard : public QPushButton {

Q_OBJECT

public: 
    SlotCard(int p);
    ~SlotCard();
    void resizeEvent (QResizeEvent*);

    void setPic(QString str);
    void rmPic();
    void turn();

    bool isAdv();
    bool isMonst();
    bool isMagic();
    bool isHand();
    bool isDeck();
    bool isField();
    bool isGrave();
    bool isFuse();

    void leaveEvent(QEvent * event);
    void enterEvent(QEvent * event);

public slots:
    void onClick();

signals:
    void clicked(int posi);
    void entered(int posi);
    void leaved(int posi);

private:
    int posi;
    bool mode;
    QString pic;

    QGridLayout * layout;

    QGraphicsView * view;
    QGraphicsScene * scene;
    QGraphicsProxyWidget * proxy;

    QPushButton * imgButt;
    
    QPropertyAnimation * rotAnim;
    QPropertyAnimation * scaleAnim;
};


#endif
