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

#include "../inc/shadowButt.h"

class NetChoice : public QFrame {

    Q_OBJECT
    
    public:
    NetChoice();
    ~NetChoice();
    void init();

    public slots:
    void emitChoice();

    signals:
    void choiceStack();

    private:
    QGridLayout * layout;
    QShortcut *shortcut;

    QWidget * infoBox;

        QGraphicsDropShadowEffect * iffect;
        QHBoxLayout * infoLayout;
        QLabel * info;
    
    QWidget * introBox;
    
        QVBoxLayout * box;
        QGraphicsDropShadowEffect * effect;

        ShadowButt * choice;

};


#endif
