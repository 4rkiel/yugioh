#include "../inc/slotCard.h"

SlotCard::SlotCard (){

    posi = 0;

    setFrameStyle(0);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCacheMode(QGraphicsView::CacheBackground);
    setStyleSheet("background: transparent");
    setRenderHints(
            QPainter::Antialiasing
            | QPainter::SmoothPixmapTransform
            | QPainter::TextAntialiasing
            | QPainter::HighQualityAntialiasing);

    scene = new QGraphicsScene;
    setScene(scene);


    proxy = new QGraphicsProxyWidget();
    scene -> addItem(proxy);


        content = new QPushButton;

        content -> setObjectName("fieldCard");
        content -> resize(width(),height());
        
        proxy -> setWidget(content);

    proxy -> setTransformOriginPoint(0,0);

    rotAnim = new QPropertyAnimation(proxy, "rotation");
    rotAnim -> setDuration(500);

    scaleAnim = new QPropertyAnimation(proxy, "geometry");
    scaleAnim -> setDuration(500);


    connect(content, SIGNAL(clicked()), this, SLOT(turn()));
    
}



SlotCard::~SlotCard (){
   
    delete scaleAnim;
    delete rotAnim;

    delete proxy;
    delete scene;
}


void SlotCard::resizeEvent(QResizeEvent *){
}


void SlotCard::turn (){
    
    posi = (posi + 1) % 2;
    
    if (posi == 0){
        scaleAnim->setStartValue(QRect(0,height(),height(),width()));
        scaleAnim->setEndValue(QRect(0,0,width(),height()));
    } else {
        scaleAnim->setStartValue(QRect(0,0,width(),height()));
        scaleAnim->setEndValue(QRect(0,height(),height(),width()));
    }

    scaleAnim -> start();
    
    rotAnim->setStartValue(-90 + (posi * 90));
    rotAnim->setEndValue(posi * -90);
    
    rotAnim->start();


}


void SlotCard::setContent(QString str){
    content -> setText(str);
}
