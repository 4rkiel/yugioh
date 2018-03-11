#include "../inc/card.h"

#include <QLabel>

Card::Card (){

    posi = 0;

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    layout = new QGridLayout;
    layout->setSpacing(0);
    layout->setMargin(0);


    view = new QGraphicsView;
    view->setFrameStyle(0);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setStyleSheet("background: red"); 
    view->setCacheMode(QGraphicsView::CacheBackground);
    //view->setRenderHints(QPainter::Antialiasing);
    view->setRenderHints(QPainter::HighQualityAntialiasing|QPainter::TextAntialiasing);


    scene = new QGraphicsScene;
    view -> setScene(scene);

    proxy = new QGraphicsProxyWidget();
    scene -> addItem(proxy);

    QPushButton * lab = new QPushButton;
    lab -> setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    lab -> setGeometry(0,0,view->width(),view->height());


    
    proxy -> setWidget(lab);


    proxy -> setScale(1);
    proxy -> setRotation(0);
    proxy -> setTransformOriginPoint(0,0);//view -> width(), view -> height());
    
    
    layout -> addWidget(view,0,1,3,1);
    setLayout(layout);


    rotAnim = new QPropertyAnimation(proxy, "rotation");
    rotAnim -> setDuration(500);

    scaleAnim = new QPropertyAnimation(proxy, "geometry");
    scaleAnim -> setDuration(500);


    // anim->setLoopCount(-1);

    connect(lab, SIGNAL(clicked()), this, SLOT(turnDef()));
    
}



Card::~Card (){
    
    delete scaleAnim;
    delete rotAnim;
    delete proxy;
    delete scene;
    delete view;
    delete layout;
}

void Card::turnDef (){
    
    posi = (posi + 1) % 2;
    
    if (posi == 0){
        scaleAnim->setStartValue(QRect(0,view->height(), view->height(), view->width()));
        scaleAnim->setEndValue(QRect(0,0,view->width(),view->height()));
    } else {
        scaleAnim->setStartValue(QRect(0,0,view->width(),view->height()));
        scaleAnim->setEndValue(QRect(0,view->height(), view->height(), view->width()));
    }
    scaleAnim -> start();
    
    rotAnim->setStartValue(-90 + (posi * 90));
    rotAnim->setEndValue(posi * -90);
    //anim->setEasingCurve(QEasingCurve::OutQuad);
    rotAnim->start(/*QAbstractAnimation::DeleteWhenStopped*/);


}
