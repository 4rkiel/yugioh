#include "../inc/card.h"

#include <QGridLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QPropertyAnimation>
#include <QLabel>

Card::Card (){

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   
    QGridLayout * layout = new QGridLayout;

    QGraphicsView *view = new QGraphicsView;
    view->setFrameStyle(0);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setStyleSheet("background: transparent"); 
    view->setCacheMode(QGraphicsView::CacheBackground);
    //view->setRenderHints(QPainter::Antialiasing);
    view->setRenderHints(QPainter::HighQualityAntialiasing|QPainter::TextAntialiasing);


    QGraphicsScene *scene = new QGraphicsScene;
    view -> setScene(scene);

    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
    scene -> addItem(proxy);

    QLabel * lab = new QLabel("Azerty");
    
    
    proxy -> setWidget(lab);


    proxy -> setScale(1);
    proxy -> setRotation(0);
    proxy -> setTransformOriginPoint(scene -> width() / 2, scene -> height() / 2);

    QPropertyAnimation *anim = new QPropertyAnimation(proxy, "rotation");
    anim->setDuration(5000);
    anim->setStartValue(0);
    anim->setEndValue(360);
    anim->setLoopCount(-1);
    //anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->start(/*QAbstractAnimation::DeleteWhenStopped*/);
    
    
    layout -> addWidget(view,0,1,3,1);
    setLayout(layout);


    connect(this, SIGNAL(clicked()), this, SLOT(turnDef()));
    
}



Card::~Card (){

}

void Card::turnDef (){



}
