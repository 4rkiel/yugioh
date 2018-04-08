#ifndef HOSTCHOICE
#define HOSTCHOICE

#include <QtCore>
#include <QApplication>
#include <QFrame>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QGraphicsDropShadowEffect>

#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QShortcut>

#include "../inc/reseau.h"
#include "../inc/flatButt.h"

class HostChoice : public QFrame {

Q_OBJECT
    
public:
    
    HostChoice();
    ~HostChoice();
    void init();

public slots:

    void emitChoice();

signals:
    
    void choiceStack();
	void createHost(QString);

private:
	
    QString ip;
    
    void setIP(QString);
    
    QGridLayout * layout;
    QShortcut *shortcut;

    QWidget * infoBox;

        QGraphicsDropShadowEffect * iffect;
        QHBoxLayout * infoLayout;
        QLabel * info;
        FlatButt * choice;
    
    QWidget * introBox;
    
        QGridLayout * box;
        QGraphicsDropShadowEffect * effect;

        QLabel * intro;
        QLabel * state;
        QLabel * ipIntro;
        QLabel * phrase;
        QLabel * adr;

};


#endif
