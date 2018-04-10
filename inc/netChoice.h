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

#include "../inc/flatButt.h"

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
	void sendIP(QString);
	void createHost(QString);

    private:
    QGridLayout * layout;
    QShortcut *shortcut;
    QLabel* msgAttente;
    QLabel* msgAttente2;

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
