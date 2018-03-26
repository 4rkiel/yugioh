#ifndef JOINCHOICE
#define JOINCHOICE

#include <QApplication>
#include <QFrame>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QGraphicsDropShadowEffect>

#include <QPushButton>
#include <QString>

#include <QLineEdit>

#include "../inc/shadowButt.h"

class JoinChoice : public QFrame {

    Q_OBJECT
    
    public:
    JoinChoice();
    ~JoinChoice();
    void init();

    public slots:
    void emitChoice();
	void connectIP();

    signals:
	void sendIP(QString);
	void choiceStack();

    private:
    QGridLayout * layout;

    QWidget * infoBox;

        QGraphicsDropShadowEffect * iffect;
        QHBoxLayout * infoLayout;
        QLabel * info;
    
    QWidget * introBox;
    
        QGridLayout * box;
        QGraphicsDropShadowEffect * effect;

        ShadowButt * choice;
        QLineEdit * input;

};


#endif
