#include "../inc/slotCard.h"

#include <iostream>

SlotCard::SlotCard (int p){

    // Init cards values

    mode = true;
    posi = p;
    pic = "";


    // Set properties

    setObjectName("fieldCard");
    
    setFlat(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    
    // Creating clickable picture zone

    layout = new QGridLayout;


    view = new QGraphicsView;
    view -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view -> setStyleSheet("background: transparent");
    view->setFrameStyle(0);
    
    scene = new QGraphicsScene;
    view -> setScene(scene);

    
    imgButt = new QPushButton;

    if (isDeck()){
    
        imgButt -> setObjectName("fieldDeckInside");
        
        if (isAdv()){

            imgButt -> setStyleSheet("margin: 0px 6px 6px 0px;");
        
        } else {
        
            imgButt -> setStyleSheet("margin: 0px 0px 6px 6px;");
        }

    } else {

        imgButt -> setObjectName("fieldCardInside");
    }

    proxy = scene -> addWidget(imgButt);

    layout -> addWidget(view);

    setLayout(layout);
    
    

    // Initiating animations

    if (isAdv()){
        int w = width();
        int h = height();

        proxy -> setRotation(180);
        proxy -> setGeometry(QRect(w,h,w,h));
    }

    rotAnim = new QPropertyAnimation(proxy, "rotation");
    rotAnim -> setDuration(500);

    scaleAnim = new QPropertyAnimation(proxy, "geometry");
    scaleAnim -> setDuration(500);


    
    connect(this, SIGNAL(clicked()), this, SLOT(onClick()));
    connect(imgButt, SIGNAL(clicked()), this, SLOT(onClick()));
}



SlotCard::~SlotCard (){

    delete scaleAnim;
    delete rotAnim;

    delete proxy;
    delete scene;
    delete view;
}


void SlotCard::resizeEvent (QResizeEvent*){
   
    int w = width();
    int h = height();

    view -> setGeometry(0,0,w,h);
    scene -> setSceneRect(0,0,w,h);

    if (mode){
    
        if (isAdv()){

            if (isDeck()){
                proxy -> setGeometry(QRect(w-6,h-6,w,h));
            } else {
                proxy -> setGeometry(QRect(w,h,w,h));
            }
        }
        
        imgButt -> resize(QSize(w,h));
    
    } else {

        if (isAdv()){
            proxy -> setGeometry(QRect(w,0,w,h));
        }

        imgButt -> resize(QSize(h,w));
    }
    
}



void SlotCard::turn (){
    
    mode = !mode;
    
    int w = width();
    int h = height();

    if (isAdv()){

        if (mode){
            scaleAnim -> setStartValue(QRect(w,0,h,w));
            scaleAnim -> setEndValue(QRect(w,h,w,h));
        } else {
            scaleAnim -> setStartValue(QRect(w,h,w,h));
            scaleAnim -> setEndValue(QRect(w,0,h,w));
        }

    } else {

        if (mode){
            scaleAnim -> setStartValue(QRect(0,h,h,w));
            scaleAnim -> setEndValue(QRect(0,0,w,h));
        } else {
            scaleAnim -> setStartValue(QRect(0,0,w,h));
            scaleAnim -> setEndValue(QRect(0,h,h,w));
        }
    }

    if (isAdv()){
        rotAnim -> setStartValue((-90 + ((mode?0:1) * 90)) + 180);
        rotAnim -> setEndValue(((mode?0:1) * -90) + 180);
    } else {
        rotAnim -> setStartValue(-90 + ((mode?0:1) * 90));
        rotAnim -> setEndValue((mode?0:1) * -90);
    }

    scaleAnim -> start();
    rotAnim->start();

}



void SlotCard::setPic(QString str){
   
    mode = true;
    
    pic = str;
    imgButt -> setStyleSheet("border-image: url(" + pic + ");");

    int w = width();
    int h = height();

    if (isAdv()){
        proxy -> setRotation(180);
        proxy -> setGeometry(QRect(w,h,w,h));
    } else {
        proxy -> setRotation(0);
        proxy -> setGeometry(QRect(0,0,w,h));
    }

    imgButt -> resize(QSize(w,h));

}



void SlotCard::rmPic(){

    imgButt -> setStyleSheet("border-image: none");
}



bool SlotCard::isAdv(){
    return (posi >= 75);
}

bool SlotCard::isMonst(){
    return ((posi >= 0 && posi <= 6)||(posi >= 75 && posi <=81));
}

bool SlotCard::isMagic(){
    return ((posi >= 7 && posi <= 13)||(posi >= 82 && posi <= 88));
}

bool SlotCard::isHand(){
    return ((posi >= 14 && posi <= 74)||(posi >= 89 && posi <= 149));
}

bool SlotCard::isDeck(){
    return ((posi == 13) || (posi == 82));
}




void SlotCard::onClick (){

    emit clicked(posi);
}
