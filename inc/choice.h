#ifndef CHOICE
#define CHOICE

#include <QApplication>
#include <QFrame>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QGraphicsDropShadowEffect>

#include <QPushButton>
#include <QString>
#include <QShortcut>

#include "../inc/flatButt.h"
#include "../inc/flatExpButt.h"

class Choice : public QFrame {

    Q_OBJECT
    
    public:
    Choice();
    ~Choice();
    void init();

    public slots:
    void emitIntro();
    void emitSolo();
    void emitJoin();
    void emitHost();
    void emitNet();

    signals:
    void introStack();
    void soloStack();
    void joinStack();
    void hostStack();
    void netStack();

    private:
    QGridLayout * layout;

    QWidget * infoBox;
    QShortcut *shortcut;
        QGraphicsDropShadowEffect * iffect;
        QHBoxLayout * infoLayout;
        QLabel * info;
        FlatButt * intro;
    
    QWidget * introBox;
    
        QVBoxLayout * box;
        QGraphicsDropShadowEffect * effect;

        FlatExpButt * host;
        FlatExpButt * group;
        FlatExpButt * online;
        FlatExpButt * solo;

        QFrame * sep1;
        QFrame * sep2;
        QFrame * sep3;

};


#endif
