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
    void emitLocal();

    signals:
    void introStack();
    void localStack();

    private:
    QGridLayout * layout;
    QWidget * introBox;
    
        QVBoxLayout * box;
        QGraphicsDropShadowEffect * effect;

        ShadowButt * intro;
        ShadowButt * group;
        ShadowButt * online;
        ShadowButt * local;

};


#endif
