#ifndef SLOTCARD
#define SLOTCARD

#include <QPushButton>

#include <QGridLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QPropertyAnimation>

#include <QString>


class SlotCard : public QGraphicsView {

    Q_OBJECT

    public: 
    SlotCard();
    ~SlotCard();
    void resizeEvent(QResizeEvent *);
    void setContent(QString str);

    public slots:
    void turn();

    private:
    bool posi;
    
    QGraphicsScene * scene;
    QGraphicsProxyWidget * proxy;

    QPushButton * content;

    QPropertyAnimation * rotAnim;
    QPropertyAnimation * scaleAnim;
};


#endif
