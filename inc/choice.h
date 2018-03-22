#ifndef CHOICE
#define CHOICE

#include <QApplication>
#include <QFrame>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QGraphicsDropShadowEffect>

#include <QPushButton>
#include <QString>

#include "../inc/shadowButt.h"

class Choice : public QFrame {

    Q_OBJECT
    
    public:
    Choice();
    ~Choice();
    void init();

    public slots:
    void emitIntro();
    void emitSolo();
    void emitMultiPlayer();
    void emitJoin();
    void emitHost();
    void emitNet();

    signals:
    void introStack();
    void soloStack();
    void multiplayerStack();
    void joinStack();
    void hostStack();
    void netStack();

    private:
    QGridLayout * layout;

    QWidget * infoBox;

        QGraphicsDropShadowEffect * iffect;
        QHBoxLayout * infoLayout;
        QLabel * info;
    
    QWidget * introBox;
    
        QVBoxLayout * box;
        QGraphicsDropShadowEffect * effect;

        ShadowButt * intro;
        ShadowButt * host;
        ShadowButt * group;
        ShadowButt * online;
        ShadowButt * solo;
        ShadowButt * multiplayer;

};


#endif
