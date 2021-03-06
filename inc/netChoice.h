#ifndef NETCHOICE
#define NETCHOICE

#include <QApplication>
#include <QFrame>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QGraphicsDropShadowEffect>

#include <QPushButton>
#include <QString>
#include <QShortcut>
#include <sstream>
#include <QUdpSocket>
#include <iostream>

#include "../inc/flatButt.h"
#include "../inc/matchmaking.h"

class NetChoice : public QFrame {

    Q_OBJECT
    
    public:
    NetChoice();
    ~NetChoice();
    void init();

    public slots:
    void emitChoice();
    void emitClient(QString);
    void emitHost(QString);

    signals:
    void choiceStack();
    void sendIP(QString);
    void createHost(QString);

    private:
    QGridLayout * layout;
    QShortcut *shortcut;
    QLabel* msgAttente;
    QLabel* msgAttente2;
    Matchmaking* matchmaker;

    QWidget * infoBox;

        QGraphicsDropShadowEffect * iffect;
        QHBoxLayout * infoLayout;
        QLabel * info;
        FlatButt * choice;
    
    QWidget * introBox;
    
        QVBoxLayout * box;
        QGraphicsDropShadowEffect * effect;


};


#endif
