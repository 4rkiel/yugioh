#include "../inc/slotDeck.h"
#include <iostream>

SlotDeck::SlotDeck (){


    size = 60;

    setStyleSheet("background:red;");
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setMinimumWidth(200);
    setMinimumHeight(200);

        
        /*
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
        std::cout << height() << "\n";
        std::cout << content -> height() << "\n";
        content -> resize(width(), height() - 500);
        content -> setObjectName("fieldDeck");
        content -> setStyleSheet("#fieldDeck {"
            "background: green;"
            "padding: 100px;"
            "border-bottom-width: 10px;"
            "border-bottom-style: inset;"
            "border-bottom-color: white;"
        "}");
        proxy -> setWidget(content);
*/
}


SlotDeck::~SlotDeck (){
    
//    delete proxy;
//    delete scene;
}


void SlotDeck::changeState(int sz){

    size = sz;
    QString str = "border-bottom:" + QString::number(size / 10) + "px solid blue";
    setStyleSheet(str);
}


void SlotDeck::draw(){

    size --;
    QString str = "border-bottom:" + QString::number(size / 10) + "px solid blue";
    setStyleSheet(str);
}
