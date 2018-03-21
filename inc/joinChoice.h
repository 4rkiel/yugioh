#ifndef JOINCHOICE
#define JOINCHOICE

#include <QApplication>
#include <QFrame>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QGraphicsDropShadowEffect>

#include <QPushButton>
#include <QString>

#include "../inc/shadowButt.h"

class JoinChoice : public QFrame {

    Q_OBJECT
    
    public:
    JoinChoice();
    ~JoinChoice();
    void init();

    public slots:
    void emitChoice();

    signals:
    void choiceStack();

    private:
    QGridLayout * layout;

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
