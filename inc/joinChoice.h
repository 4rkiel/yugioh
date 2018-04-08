#ifndef JOINCHOICE
#define JOINCHOICE

#include <QApplication>
#include <QFrame>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QGraphicsDropShadowEffect>

#include <QPushButton>
#include <QString>
#include <QShortcut>

#include <QLineEdit>

#include "../inc/darkButt.h"
#include "../inc/flatButt.h"

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
        QLineEdit * input;
        DarkButt * valid;
};


#endif
