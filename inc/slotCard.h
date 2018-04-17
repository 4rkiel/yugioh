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
	void reveal(QString str);

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
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void affChat();

signals:
    void leftClick(int posi);
    void rightClick(int posi);
    void doubleClick(int posi);
    void entered(int posi);
    void leaved(int posi);
    void rcvQuit();
    void mvRight();
    void mvLeft();
    void mvUp();
    void mvDown();
    void swChat();

private:
    int posi;
    bool mode;
    QString pic;
    QShortcut* shortcut;
    QShortcut* shortcut2;
    QShortcut* shortcut3;
    QShortcut* shortcut4;
    QShortcut* shortcut5;
    QShortcut* shortcut6;
    QShortcut* shortcut7;

    QGridLayout * layout;

    QGraphicsView * view;
    QGraphicsScene * scene;
    QGraphicsProxyWidget * proxy;

    zButt * imgButt;
    
    QPropertyAnimation * rotAnim;
    QPropertyAnimation * scaleAnim;
};


#endif
