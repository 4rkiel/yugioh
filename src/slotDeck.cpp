#include "../inc/slotDeck.h"

SlotDeck::SlotDeck (){

    posi = 0;
    url = "img/cards/001/LOB-EN124-ExodiatheForbiddenOneTCG.jpg";

    setObjectName("fieldDeck");
    setFlat(true);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    
    layout = new QGridLayout;


    view = new QGraphicsView;
    view -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view -> setStyleSheet("background: transparent");
    view->setFrameStyle(0);
    
    scene = new QGraphicsScene;
    view -> setScene(scene);

    
    imgButt = new QPushButton;
    imgButt -> setObjectName("fieldDeckInside");
    imgButt -> setStyleSheet("border-image: url(" + url + ");");

    
    proxy = scene -> addWidget(imgButt);

    layout -> addWidget(view);

    setLayout(layout);
    
    

    rotAnim = new QPropertyAnimation(proxy, "rotation");
    rotAnim -> setDuration(500);

    scaleAnim = new QPropertyAnimation(proxy, "geometry");
    scaleAnim -> setDuration(500);


    
//    connect(this, SIGNAL(clicked()), this, SLOT(turn()));
//    connect(imgButt, SIGNAL(clicked()), this, SLOT(turn()));

}



SlotDeck::~SlotDeck (){

    delete scaleAnim;
    delete rotAnim;

    delete proxy;
    delete scene;
    delete view;
}


void SlotDeck::resizeEvent (QResizeEvent*){
   
    int w = width();
    int h = height();

    view -> setGeometry(0,0,w,h);
    scene->setSceneRect(0,0,w,h);

    if (posi){
        imgButt -> resize(QSize(h,w));
    } else {
        imgButt -> resize(QSize(w,h));
    }
}


void SlotDeck::turn (){
    
    posi = (posi + 1) % 2;
    
    int w = width();
    int h = height();

    if (posi == 0){
        scaleAnim->setStartValue(QRect(0,h,h,w));
        scaleAnim->setEndValue(QRect(0,0,w,h));
    } else {
        scaleAnim->setStartValue(QRect(0,0,w,h));
        scaleAnim->setEndValue(QRect(0,h,h,w));
    }

    rotAnim->setStartValue(-90 + (posi * 90));
    rotAnim->setEndValue(posi * -90);
    
    scaleAnim -> start();
    rotAnim->start();


}


void SlotDeck::setPic(QString str){
    url = str;
    imgButt -> setStyleSheet("border-image: url(" + url + ");");
}
