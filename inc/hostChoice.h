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

#include "../inc/reseau.h"
#include "../inc/shadowButt.h"

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
	void createHostChoice(QString);

private:
	
    void setIP(QString str);
    
    QGridLayout * layout;

    QWidget * infoBox;

        QGraphicsDropShadowEffect * iffect;
        QHBoxLayout * infoLayout;
        QLabel * info;
    
    QWidget * introBox;
    
        QGridLayout * box;
        QGraphicsDropShadowEffect * effect;

        QLabel * intro;
        QLabel * phrase;
        QLabel * adr;
        ShadowButt * choice;

};


#endif
