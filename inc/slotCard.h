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
#include <QMouseEvent>
#include <QShortcut>

#include "../inc/superButt.h"
#include "../inc/zButt.h"


class SlotCard : public SuperButt {

Q_OBJECT

public: 
    SlotCard(int p);
    ~SlotCard();
    void resizeEvent (QResizeEvent*);

    void setPic(QString str);
    void posePic();
    void maskPic();
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
	void doubleClicked();
	void rightClicked();
	void leftClicked();
    void openQuit();

signals:
    void leftClick(int posi);
    void rightClick(int posi);
    void doubleClick(int posi);
    void entered(int posi);
    void leaved(int posi);
    void rcvQuit();

private:
    int posi;
    bool mode;
    QString pic;
    QShortcut* shortcut;

    QGridLayout * layout;

    QGraphicsView * view;
    QGraphicsScene * scene;
    QGraphicsProxyWidget * proxy;

    zButt * imgButt;
    
    QPropertyAnimation * rotAnim;
    QPropertyAnimation * scaleAnim;
};


#endif
