#include "../inc/card.h"

#include <QLabel>

Card::Card (){

    posi = 0;

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   
    layout = new QGridLayout;

    view = new QGraphicsView;
    view->setFrameStyle(0);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setStyleSheet("background: transparent"); 
    view->setCacheMode(QGraphicsView::CacheBackground);
    //view->setRenderHints(QPainter::Antialiasing);
    view->setRenderHints(QPainter::HighQualityAntialiasing|QPainter::TextAntialiasing);


    scene = new QGraphicsScene;
    view -> setScene(scene);

    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
    scene -> addItem(proxy);

    QLabel * lab = new QLabel("Azerty");
    
    
    proxy -> setWidget(lab);


    proxy -> setScale(1);
    proxy -> setRotation(0);
    proxy -> setTransformOriginPoint(scene -> width() / 2, scene -> height() / 2);
   
    layout -> addWidget(view,0,1,3,1);
    setLayout(layout);


    anim = new QPropertyAnimation(proxy, "rotation");
    anim->setDuration(500);

    // anim->setLoopCount(-1);

    connect(this, SIGNAL(clicked()), this, SLOT(turnDef()));
    
}



Card::~Card (){

}

void Card::turnDef (){

    posi = (posi + 1) % 2;
    anim->setStartValue(90 - (posi * 90));
    anim->setEndValue(posi * 90);
    //anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->start(/*QAbstractAnimation::DeleteWhenStopped*/);

}
