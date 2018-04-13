#include "../inc/darkButt.h"

/******************************************************************************

    Réimplémentation des QPushButton

	Permet d'avoir un bouton avec ombre et icone/texte

******************************************************************************/

DarkButt::DarkButt (QString icoStr, QString textStr){
 
    // Button content


    layout = new QHBoxLayout;
    layout -> setSizeConstraint(QLayout::SetMinimumSize);
    layout -> setMargin(0);
    layout -> setSpacing(0);
    layout -> setContentsMargins(0,0,0,0);

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

        layout -> addStretch(1);
            
        layout -> addWidget(txt, 0, Qt::AlignRight);
        
        if (icoStr != ""){
            layout -> addStretch(2);
        } else {
            layout -> addStretch(1);
        }
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
    pressTask = new DarkTask;
    pressTask -> moveToThread(pressThread);


    connect( this, SIGNAL(askWait()), pressTask, SLOT(buttLoop()) );
    connect( this, SIGNAL(newState()), this, SLOT(runNewState()) );
    connect( pressTask, SIGNAL(newState()), this, SLOT(runNewState()) );

    connect( pressThread, SIGNAL(finished()), pressTask, SLOT(deleteLater()) );
    connect( pressThread, SIGNAL(finished()), pressThread, SLOT(deleteLater()) );

    pressThread -> start();

}



DarkButt::~DarkButt (){

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



void DarkTask::buttLoop (){

    Sleeper::msleep(42);
    
	emit newState();

}


void DarkButt::buttonPressed(){

    state = 0;
    
    emit newState();
}



void DarkButt::buttonReleased(){

    state = 1;

    emit newState();
}


void DarkButt::setText (QString str){
    txt -> setText(str);
}

void DarkButt::setIcon(QString icoStr)
{
    ico -> setText(icoStr);
}


void DarkButt::runNewState (){

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

