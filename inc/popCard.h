#ifndef POPCARD
#define POPCARD

#include <QGridLayout>

#include <QPushButton>
#include <QString>

#include <QStyle>
#include <QMouseEvent>
#include <QShortcut>

#include "../inc/superButt.h"
#include "../inc/zButt.h"


class PopCard : public SuperButt {

Q_OBJECT

public: 
    PopCard(int p);
    ~PopCard();

    void setPic(QString str);

    void leaveEvent(QEvent * event);
    void enterEvent(QEvent * event);
    void focusInEvent(QFocusEvent* e);
    void focusOutEvent(QFocusEvent* e);

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
    QString pic;
    bool selected;

    QShortcut* shortcut;
    QShortcut* shortcut2;
    QShortcut* shortcut3;
    QShortcut* shortcut4;
    QShortcut* shortcut5;
    QShortcut* shortcut6;
    QShortcut* shortcut7;
    QShortcut* shortcut8;
    QShortcut* shortcut9;

    QGridLayout * layout;

    zButt * imgButt;
};


#endif
