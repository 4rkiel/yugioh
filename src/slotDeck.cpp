#include "../inc/slotDeck.h"
#include <iostream>

#include <QGridLayout>
#include <QWidget>
#include <QPushButton>

SlotDeck::SlotDeck (){


    size = 60;

    setFrameStyle(0);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCacheMode(QGraphicsView::CacheBackground);
        setStyleSheet("background: red; padding: 30px; margin:30px");
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
        
        content -> setStyleSheet("background: blue; padding: 30px; margin:30px");
        proxy -> setWidget(content);

}


SlotDeck::~SlotDeck (){
   delete proxy;
   delete scene;

}


void SlotDeck::changeState(int sz){

    size = sz;
    QString str = "border-bottom:" + QString::number(size / 10) + "px solid blue";
}


void SlotDeck::draw(){

    size --;
    QString str = "border-bottom:" + QString::number(size / 10) + "px solid blue";
}
