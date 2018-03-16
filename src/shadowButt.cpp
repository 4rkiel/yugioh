#include "../inc/shadowButt.h"

ShadowButt::ShadowButt (QString icoStr, QString textStr){
 
    // Button content


    layout = new QHBoxLayout;
    layout -> setSizeConstraint(QLayout::SetMinimumSize);

    ico = nullptr;
    txt = nullptr;

    if (icoStr != ""){
        ico = new QLabel;
        ico -> setMargin(10);
        ico -> setFont(QFont("Font Awesome 5 Free", 12));
        ico -> setText(icoStr);
   
        if (textStr == ""){
            setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

            layout -> addStretch();
            layout -> addWidget(ico, 0, Qt::AlignCenter);
            layout -> addStretch();
        } else {
            layout -> addWidget(ico, 0, Qt::AlignLeft);
        }
    }

    if (textStr != ""){
        txt = new QLabel;
        txt -> setText(textStr);

        layout -> addStretch();
        layout -> addWidget(txt, 0, Qt::AlignRight);
        layout -> addStretch();
    }

    setLayout(layout);


    // Button shadow

    effectButt = new QGraphicsDropShadowEffect;
    effectButt -> setBlurRadius(5);
    effectButt -> setYOffset(5);
    effectButt -> setXOffset(0);
    effectButt -> setColor(QColor(0,0,0,150));

    setGraphicsEffect(effectButt);


    lastPosi = 5;

    connect(this, SIGNAL(released()), this, SLOT(buttonReleased()));
    connect(this, SIGNAL(pressed()), this, SLOT(buttonPressed()));


    // run effect thread 

    pressThread = new QThread;
    pressTask = new ShadowTask;
    pressTask -> moveToThread(pressThread);


    connect( this, SIGNAL(askWait()), pressTask, SLOT(buttLoop()) );
    connect( this, SIGNAL(newState()), this, SLOT(runNewState()) );
    connect( pressTask, SIGNAL(newState()), this, SLOT(runNewState()) );

    connect( pressThread, SIGNAL(finished()), pressTask, SLOT(deleteLater()) );
    connect( pressThread, SIGNAL(finished()), pressThread, SLOT(deleteLater()) );

    pressThread -> start();

}



ShadowButt::~ShadowButt (){

    if (ico != nullptr){
        delete ico;
    }

    if (txt != nullptr){
        delete txt;
    }

    delete layout;

    delete effectButt;

    pressThread -> quit();
}



void ShadowTask::buttLoop (){

    Sleeper::msleep(42);

    emit newState();

}


void ShadowButt::buttonPressed(){

    state = 0;
    
    emit newState();
}



void ShadowButt::buttonReleased(){

    state = 1;

    emit newState();
}



void ShadowButt::runNewState (){

    if (state == 0 && lastPosi > 0){

        lastPosi -- ;

		if (lastPosi == 0){
			
            effectButt -> setColor(QColor(0,0,0,0));

		} else {

			effectButt -> setBlurRadius(lastPosi);
			effectButt -> setYOffset(lastPosi);

		    effectButt -> update();
		}

        emit askWait();

    } else if (state == 1 && lastPosi < 5){

        lastPosi ++ ;

		if (lastPosi == 1){

            effectButt -> setColor(QColor(0,0,0,150));

		}

		effectButt -> setBlurRadius(lastPosi);
		effectButt -> setYOffset(lastPosi);

		effectButt -> update();


        emit askWait();
    }
}
