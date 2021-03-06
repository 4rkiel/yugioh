#include "../inc/slotCard.h"
#include <iostream>

/******************************************************************************

	Widgets représentant les emplacements de cartes sur le terrain

	Ne stock que les composants utiles au visuel

******************************************************************************/

SlotCard::SlotCard (int p){

    // Init cards values

    mode = true;
    posi = p;
    pic = "";

    setFlat(true);

    // Set properties

    if (isHand()){

        setObjectName("handCard");

    } else if (isMagic()){

        setObjectName("magicCard");

    } else if (isMonst()){

        setObjectName("monstCard");

    } else if (isDeck()){

        setObjectName("deckCard");

    } else if (isFuse()){

        setObjectName("fuseCard");

    } else if (isGrave()){

        setObjectName("graveCard");

    } else if (isField()){

        setObjectName("fieldCard");

    }


    
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

    
    imgButt = new zButt;

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
    
    imgButt -> setFocusPolicy(Qt::NoFocus);
    proxy -> setFlag(QGraphicsItem::ItemIsFocusable, false);
    view -> setFocusPolicy(Qt::NoFocus);

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


	connect(this, SIGNAL(clicked()), this, SLOT(leftClicked()));
	connect(imgButt, SIGNAL(clicked()), this, SLOT(leftClicked()));
	connect(imgButt, SIGNAL(rightClicked()), this, SLOT(rightClicked()));
	connect(imgButt, SIGNAL(doubleClicked()), this, SLOT(doubleClicked()));

    //raccourci echap
    shortcut = new QShortcut(QKeySequence("Escape"), this);
    shortcut->setContext(Qt::WidgetWithChildrenShortcut);
    connect(shortcut, SIGNAL(activated()), this, SLOT(openQuit()));

    //raccourci entrée
    shortcut2 = new QShortcut(QKeySequence("Return"), this);
    shortcut2->setContext(Qt::WidgetWithChildrenShortcut);
    connect(shortcut2, SIGNAL(activated()), this, SLOT(doubleClicked()));

    //key shortcut
    shortcut3 = new QShortcut(QKeySequence("Up"), this);
    shortcut3->setContext(Qt::WidgetWithChildrenShortcut);
    connect(shortcut3, SIGNAL(activated()), this, SLOT(moveUp()));

    //key shortcut
    shortcut4 = new QShortcut(QKeySequence("Down"), this);
    shortcut4->setContext(Qt::WidgetWithChildrenShortcut);
    connect(shortcut4, SIGNAL(activated()), this, SLOT(moveDown()));

    //key shortcut
    shortcut5 = new QShortcut(QKeySequence("Left"), this);
    shortcut5->setContext(Qt::WidgetWithChildrenShortcut);
    connect(shortcut5, SIGNAL(activated()), this, SLOT(moveLeft()));

    //key shortcut
    shortcut6 = new QShortcut(QKeySequence("Right"), this);
    shortcut6->setContext(Qt::WidgetWithChildrenShortcut);
    connect(shortcut6, SIGNAL(activated()), this, SLOT(moveRight()));

    //key shortcut
    shortcut7 = new QShortcut(QKeySequence("F1"), this);
    shortcut7->setContext(Qt::WidgetWithChildrenShortcut);
    connect(shortcut7, SIGNAL(activated()), this, SLOT(affChat()));

    //key shortcut
    shortcut8 = new QShortcut(QKeySequence("Enter"), this);
    shortcut8->setContext(Qt::WidgetWithChildrenShortcut);
    connect(shortcut8, SIGNAL(activated()), this, SLOT(rightClicked()));

    //raccourci espace
    shortcut9 = new QShortcut(QKeySequence(Qt::Key_Space), this);
    shortcut9->setContext(Qt::WidgetWithChildrenShortcut);
    connect(shortcut9, SIGNAL(activated()), this, SLOT(leftClicked()));
}



SlotCard::~SlotCard (){

    delete shortcut;
    delete shortcut2;
    delete shortcut3;
    delete shortcut4;
    delete shortcut5;
    delete shortcut6;
    delete shortcut7;
    delete shortcut8;
    delete shortcut9;
    delete scaleAnim;
    delete rotAnim;

    delete proxy;
    delete scene;
    delete view;

    delete layout;
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
        } else {
            proxy -> setGeometry(QRect(0,h,w,h));
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


void SlotCard::reveal(QString str){
	   
    pic = str;
    imgButt -> setStyleSheet("border-image: url(" + pic + ");");

}



void SlotCard::setPic(QString str){
   
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

void SlotCard::maskPic(){

    imgButt -> setStyleSheet("border-image: url(\"img/card.svg\");");
    
}


void SlotCard::posePic(){

    imgButt -> setStyleSheet("border-image: url(\"img/card.svg\");");
    
    if (mode){
        turn();
    }

}

void SlotCard::rmPic(){

    imgButt -> setStyleSheet("border-image: none");
    
    if (!mode){
        turn();
    }

}



// TESTS

bool SlotCard::isAdv(){
    return (posi >= 75);
}

bool SlotCard::isMonst(){
    return ((posi >= 1 && posi <= 5)||(posi >= 76 && posi <= 80));
}

bool SlotCard::isMagic(){
    return ((posi >= 8 && posi <= 12)||(posi >= 83 && posi <= 87));
}

bool SlotCard::isHand(){
    return ((posi >= 14 && posi <= 74)||(posi >= 89 && posi <= 149));
}

bool SlotCard::isDeck(){
    return ((posi == 13) || (posi == 82));
}

bool SlotCard::isField(){
    return ((posi == 0) || (posi == 81));
}

bool SlotCard::isGrave(){
    return ((posi == 6) || (posi == 75));
}

bool SlotCard::isFuse(){
    return ((posi == 7) || (posi == 88));
}



// SIGNALS

void SlotCard::doubleClicked(){
	emit doubleClick(posi);
}

void SlotCard::rightClicked(){

	emit rightClick(posi);
}

void SlotCard::leftClicked(){
    emit leftClick(posi);
}

void SlotCard::enterEvent(QEvent * event){

    emit entered(posi);
    QWidget::enterEvent(event);
}

void SlotCard::leaveEvent(QEvent * event){
    
    emit leaved(posi);
    QWidget::leaveEvent(event);
}

void SlotCard::focusInEvent(QFocusEvent* e){
    emit entered(posi);
    QWidget::focusInEvent(e);
}

void SlotCard::focusOutEvent(QFocusEvent* e){
    emit leaved(posi);
    QWidget::focusOutEvent(e);
}

void SlotCard::openQuit(){
    emit rcvQuit();
}

void SlotCard::moveDown(){
    emit mvDown();
}

void SlotCard::moveUp(){
    emit mvUp();
}

void SlotCard::moveRight(){
    emit mvRight();
}

void SlotCard::moveLeft(){
    emit mvLeft();
}

void SlotCard::affChat(){
    emit swChat();
}
