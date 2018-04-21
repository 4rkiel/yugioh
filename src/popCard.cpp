#include "../inc/popCard.h"

/******************************************************************************

	Widgets représentant les emplacements de cartes sur le terrain

	Ne stock que les composants utiles au visuel

******************************************************************************/

PopCard::PopCard (int n){

    // Init cards values

    pic = "";
    posi = n;
    selected = false;
    setProperty("down", false);
    setFlat(true);

    // Set properties


    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Creating clickable picture zone

    layout = new QGridLayout;
    
        imgButt = new zButt;
        imgButt -> setFocusPolicy(Qt::StrongFocus);
        imgButt -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout -> addWidget(imgButt);

    setLayout(layout);
    

//	connect(this, SIGNAL(clicked()), this, SLOT(leftClicked()));
//	connect(imgButt, SIGNAL(clicked()), this, SLOT(leftClicked()));
//	connect(imgButt, SIGNAL(rightClicked()), this, SLOT(rightClicked()));
	connect(imgButt, SIGNAL(doubleClicked()), this, SLOT(doubleClicked()));

    /*

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

*/    
}



PopCard::~PopCard (){
/*
    delete shortcut;
    delete shortcut2;
    delete shortcut3;
    delete shortcut4;
    delete shortcut5;
    delete shortcut6;
    delete shortcut7;
    delete shortcut8;
    delete shortcut9;
*/
    delete imgButt;
    delete layout;
}


void PopCard::setPic(QString str){
   
    pic = str;
    imgButt -> setStyleSheet("border-image: url(" + pic + ");");
}


// SIGNALS

void PopCard::doubleClicked(){

    if (selected){
        selected = false;
        setProperty("down", false);

        style() -> unpolish(this);
        style() -> polish(this);

    } else {
        
        selected = true;
        setProperty("down", true);

        style() -> unpolish(this);
        style() -> polish(this);
    }

	emit doubleClick(posi);
}

void PopCard::rightClicked(){

	emit rightClick(posi);
}

void PopCard::leftClicked(){
	emit leftClick(posi);
}

void PopCard::enterEvent(QEvent * event){

    emit entered(posi);
    QWidget::enterEvent(event);
}

void PopCard::leaveEvent(QEvent * event){
    
    emit leaved(posi);
    QWidget::leaveEvent(event);
}

void PopCard::focusInEvent(QFocusEvent* e){
    emit entered(posi);
    QWidget::focusInEvent(e);
}

void PopCard::focusOutEvent(QFocusEvent* e){
    emit leaved(posi);
    QWidget::focusOutEvent(e);
}

void PopCard::openQuit(){
    emit rcvQuit();
}

void PopCard::moveDown(){
    emit mvDown();
}

void PopCard::moveUp(){
    emit mvUp();
}

void PopCard::moveRight(){
    emit mvRight();
}

void PopCard::moveLeft(){
    emit mvLeft();
}

void PopCard::affChat(){
    emit swChat();
}
