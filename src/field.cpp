#include "../inc/field.h"

Field::Field () {

    overLayout = new QGridLayout;
    //overLayout -> setAlignment(Qt::AlignCenter);
    overLayout -> setSpacing(0);
    overLayout -> setMargin(0);

  

    // Scene principale

    sceneBox = new QWidget;
    sceneLayout = new QGridLayout;
    sceneLayout -> setSpacing(0);
    sceneLayout -> setMargin(0);



        // Left bar ...........................................................

        leftBarBox = new QWidget;
//        leftBarBox -> setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        leftBarLayout = new QGridLayout;
        leftBarLayout -> setSpacing(0);
        leftBarLayout -> setMargin(0);
//        leftBarLayout -> setAlignment(Qt::AlignHCenter);


            // Text label

            lifeAdv = new AppIndicator();
            QString strAdv = QString::fromUtf8("8000");
            lifeAdv -> setText(strAdv);
            lifeAdv -> setObjectName("Life");
            leftBarLayout -> addWidget(lifeAdv, 0, 1, 1, 1);
          

            QSpacerItem * spacerLeftTop = new QSpacerItem(3,1,
                QSizePolicy::Preferred,QSizePolicy::Expanding);
            leftBarLayout -> addItem(spacerLeftTop, 1, 0);


            card = new AppIndicator();
            card -> setObjectName("Card");
            card -> setWordWrap(true);
            QString strCard = QString::fromUtf8(""
                "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
                "Morbi molestie arcu viverra urna faucibus tempor. "
                "Mauris nulla elit, elementum a dolor eu, condimentum eleifend elit. "
                "Nullam aliquet varius magna nec elementum. "
                "Aliquam elementum dapibus justo, eget imperdiet arcu pretium sit amet. "
                "Aenean vitae eros tortor. "
                "Etiam interdum erat dolor, et lacinia purus vestibulum id. "
                "Quisque pretium neque vel commodo tincidunt. "
                "Sed in suscipit erat."
                "\n\n"
                "★ ★ 8"
                "\n"
                "ATK/2000"
                "\n"
                "DEF/2000"
            );
            card -> setText(strCard);
            leftBarLayout -> addWidget(card, 2, 0, 1, 3);


            QSpacerItem * spacerLeftBot = new QSpacerItem(3,1,
                QSizePolicy::Preferred,QSizePolicy::Expanding);
            leftBarLayout -> addItem(spacerLeftBot, 3, 0);


            actionButt = new ShadowButt("\uf04b", "");
            actionButt -> setToolTip("Terminer le tour");
            leftBarLayout -> addWidget(actionButt, 4, 1, 1, 1);

           
        leftBarBox -> setObjectName("leftBarBox");            
        leftBarBox -> setLayout(leftBarLayout);



        // Arena ..............................................................

        arenaView = new QGraphicsView;
        arenaView->setFrameStyle(0);
        arenaView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        arenaView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        arenaView->setStyleSheet("background: transparent");
        arenaView->setCacheMode(QGraphicsView::CacheBackground);

        arenaView -> setRenderHints(
                QPainter::Antialiasing
                | QPainter::SmoothPixmapTransform
                | QPainter::TextAntialiasing
                | QPainter::HighQualityAntialiasing 
        );
        
        arenaScene = new QGraphicsScene;
        
        arenaProxy = new QGraphicsProxyWidget;



        arenaBox = new QWidget;
        arenaBox -> setObjectName("arenaBox");
        arenaLayout = new QGridLayout;
       

            // Opponent 
                
            advBox = new QWidget;
            advLayout = new QGridLayout;
            advLayout -> setSpacing(0);
            advLayout -> setMargin(0);

           
                advHand = new QWidget;
                advHand -> setObjectName("advHand");
                advHandLayout = new QHBoxLayout;
                advHandLayout -> setMargin(10);
                advHandLayout -> setSpacing(10);

                    advHand0 = new SlotDeck;
                    advHand0 -> setObjectName("advDeck");

                    advHandLayout -> addWidget(advHand0);
                    advHand1 = new SlotCard;
                    advHandLayout -> addWidget(advHand1);
                    advHand2 = new SlotCard;
                    advHandLayout -> addWidget(advHand2);
                    advHand3 = new SlotCard;
                    advHandLayout -> addWidget(advHand3);
                    advHand4 = new SlotCard;
                    advHandLayout -> addWidget(advHand4);
                    advHand5 = new SlotCard;
                    advHandLayout -> addWidget(advHand5);
                    advHand6 = new SlotCard;
                    advHandLayout -> addWidget(advHand6);

                advHand -> setLayout(advHandLayout);
                advLayout -> addWidget(advHand, 2,0,1,1);

                advMagic = new QWidget;
                advMagic -> setObjectName("advMagic");
                advMagicLayout = new QHBoxLayout;
                advMagicLayout -> setMargin(10);
                advMagicLayout -> setSpacing(10);
                
                    advMagic0 = new SlotCard;
                    advMagicLayout -> addWidget(advMagic0);
                    advMagic1 = new SlotCard;
                    advMagicLayout -> addWidget(advMagic1);
                    advMagic2 = new SlotCard;
                    advMagicLayout -> addWidget(advMagic2);
                    advMagic3 = new SlotCard;
                    advMagicLayout -> addWidget(advMagic3);
                    advMagic4 = new SlotCard;
                    advMagicLayout -> addWidget(advMagic4);
                    advMagic5 = new SlotCard;
                    advMagicLayout -> addWidget(advMagic5);
                    advMagic6 = new SlotCard;
                    advMagicLayout -> addWidget(advMagic6);
               
                advMagic -> setLayout(advMagicLayout);
                advLayout -> addWidget(advMagic, 1,0,1,1);

                advMonst = new QWidget;
                advMonst -> setObjectName("advMonst");
                advMonstLayout = new QHBoxLayout;
                advMonstLayout -> setMargin(10);
                advMonstLayout -> setSpacing(10);

                    advMonst0 = new SlotCard;
                    advMonstLayout -> addWidget(advMonst0);
                    advMonst1 = new SlotCard;
                    advMonstLayout -> addWidget(advMonst1);
                    advMonst2 = new SlotCard;
                    advMonstLayout -> addWidget(advMonst2);
                    advMonst3 = new SlotCard;
                    advMonstLayout -> addWidget(advMonst3);
                    advMonst4 = new SlotCard;
                    advMonstLayout -> addWidget(advMonst4);
                    advMonst5 = new SlotCard;
                    advMonstLayout -> addWidget(advMonst5);
                    advMonst6 = new SlotCard;
                    advMonstLayout -> addWidget(advMonst6);
                          
                advMonst -> setLayout(advMonstLayout);
                advLayout -> addWidget(advMonst,0,0,1,1);

            advBox -> setLayout(advLayout);
            arenaLayout -> addWidget(advBox, 0,0,1,1);

                
                // Self

            slfBox = new QWidget;
            slfLayout = new QGridLayout;
            slfLayout -> setMargin(0);
            slfLayout -> setSpacing(0);
            //slfLayout -> setAlignment(Qt::AlignCenter);
            
                slfMonst = new QWidget;
                slfMonst -> setObjectName("slfMonst");
                slfMonstLayout = new QHBoxLayout;
                slfMonstLayout -> setMargin(10);
                slfMonstLayout -> setSpacing(10);
     
                    slfMonst0 = new SlotCard;
                    slfMonstLayout -> addWidget(slfMonst0);
                    slfMonst1 = new SlotCard;
                    slfMonstLayout -> addWidget(slfMonst1);
                    slfMonst2 = new SlotCard;
                    slfMonstLayout -> addWidget(slfMonst2);
                    slfMonst3 = new SlotCard;
                    slfMonstLayout -> addWidget(slfMonst3);
                    slfMonst4 = new SlotCard;
                    slfMonstLayout -> addWidget(slfMonst4);
                    slfMonst5 = new SlotCard;
                    slfMonstLayout -> addWidget(slfMonst5);
                    slfMonst6 = new SlotCard;
                    slfMonstLayout -> addWidget(slfMonst6);
                                     
                slfMonst -> setLayout(slfMonstLayout);
                slfLayout -> addWidget(slfMonst, 0,0,1,1);

                slfMagic = new QWidget;
                slfMagic -> setObjectName("slfMagic");
                slfMagicLayout = new QHBoxLayout;
                slfMagicLayout -> setMargin(10);
                slfMagicLayout -> setSpacing(10);
     
                    slfMagic0 = new SlotCard;
                    slfMagicLayout -> addWidget(slfMagic0);
                    slfMagic1 = new SlotCard;
                    slfMagicLayout -> addWidget(slfMagic1);
                    slfMagic2 = new SlotCard;
                    slfMagicLayout -> addWidget(slfMagic2);
                    slfMagic3 = new SlotCard;
                    slfMagicLayout -> addWidget(slfMagic3);
                    slfMagic4 = new SlotCard;
                    slfMagicLayout -> addWidget(slfMagic4);
                    slfMagic5 = new SlotCard;
                    slfMagicLayout -> addWidget(slfMagic5);
                    slfMagic6 = new SlotCard;
                    slfMagicLayout -> addWidget(slfMagic6);
                
                slfMagic -> setLayout(slfMagicLayout);
                slfLayout -> addWidget(slfMagic, 1,0,1,1);

                slfHand = new QWidget;
                slfHand -> setObjectName("slfHand");
                slfHandLayout = new QHBoxLayout;
                slfHandLayout -> setMargin(10);
                slfHandLayout -> setSpacing(10);
      
                    slfHand0 = new SlotCard;
                    slfHandLayout -> addWidget(slfHand0);
                    slfHand1 = new SlotCard;
                    slfHandLayout -> addWidget(slfHand1);
                    slfHand2 = new SlotCard;
                    slfHandLayout -> addWidget(slfHand2);
                    slfHand3 = new SlotCard;
                    slfHandLayout -> addWidget(slfHand3);
                    slfHand4 = new SlotCard;
                    slfHandLayout -> addWidget(slfHand4);
                    slfHand5 = new SlotCard;
                    slfHandLayout -> addWidget(slfHand5);
                    
                    slfHand6 = new SlotDeck;
                    slfHand6 -> setObjectName("slfDeck");

                    slfHandLayout -> addWidget(slfHand6);
               
                slfHand -> setLayout(slfHandLayout);
                slfLayout -> addWidget(slfHand, 2,0,1,1);

            slfBox -> setLayout(slfLayout);
            arenaLayout -> addWidget(slfBox, 1,0,1,1);

        arenaBox -> setLayout(arenaLayout);
        arenaProxy -> setWidget(arenaBox);
        arenaScene -> addItem(arenaProxy);
        arenaView -> setScene(arenaScene);
        



        // Right Bar ..........................................................

        rightBarBox = new QWidget;
        rightBarLayout = new QVBoxLayout;
        rightBarLayout -> setSpacing(0);
        rightBarLayout -> setMargin(0);
        rightBarLayout -> setAlignment(Qt::AlignCenter);

            
            menuButt = new ShadowButt("\uf0c9", "");
            menuButt -> setToolTip("Menu");
            connect(menuButt, SIGNAL(clicked()), this, SLOT(openMenu()));
            rightBarLayout -> addWidget(menuButt);
           

            rightBarLayout -> addStretch();


            // turn


            rightBarLayout -> addStretch();


            lifeSlf = new AppIndicator();
            QString strSlf = QString::fromUtf8("8000");
            lifeSlf -> setText(strSlf);
            lifeSlf -> setObjectName("Life");

            rightBarLayout -> addWidget(lifeSlf);
           






        rightBarBox -> setObjectName("rightBarBox");
        rightBarBox -> setLayout(rightBarLayout);
   

    sceneLayout -> addWidget(leftBarBox, 0, 0, 3, 1);
    sceneLayout -> addWidget(arenaView, 0, 1, 3, 5);
    sceneLayout -> addWidget(rightBarBox, 0, 6, 3, 1);
    sceneBox -> setLayout(sceneLayout);


    /**************************************************************************
     *
     *          Popup Menu
     *
     **************************************************************************/

    popupOuter = new QWidget;   
    popupOuter -> setVisible(false);
    popupOuterLayout = new QGridLayout;
    popupOuterLayout -> setSpacing(0);
    popupOuterLayout -> setMargin(0);
    popupOuterLayout -> setAlignment(Qt::AlignCenter);

    popupShadow = new QPushButton;
    popupShadow -> setObjectName("popupShadow");
    popupShadow -> setFocusPolicy(Qt::NoFocus);
    popupShadow -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(popupShadow, SIGNAL(clicked()), this, SLOT(closeMenu()));
    
    popupBox = new QWidget;
    popupBox -> setObjectName("popupBox");
    popupLayout = new QStackedLayout;
    popupLayout -> setSizeConstraint(QLayout::SetFixedSize);
    popupLayout -> setSpacing(0);
    popupLayout -> setMargin(0);

        popupEffect = new QGraphicsDropShadowEffect; 
        popupEffect -> setBlurRadius(5); 
        popupEffect -> setXOffset(0); 
        popupEffect -> setYOffset(5); 
        popupEffect -> setColor(QColor(0,0,0,150)); 

        popupBox -> setGraphicsEffect(popupEffect); 



        // menu

        menuOuter = new QWidget;
        menuOuterLayout = new QGridLayout;

        menuBox = new QWidget;
        menuBox -> setObjectName("menuBox");
        menuLayout = new QVBoxLayout;
        menuLayout -> setAlignment(Qt::AlignCenter);


            quit = new ShadowButt("\uf00d", "Abandonner");
            quit -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            quit -> setToolTip("Quitter le Duel");
            connect(quit, SIGNAL(clicked()), this, SLOT(emitIntroStack()));
            menuLayout -> addWidget(quit);

            back = new ShadowButt("\uf078", "Fermer");
            back -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            back -> setToolTip("Retour au Duel");
            connect(back, SIGNAL(clicked()), this, SLOT(closeMenu()));
            menuLayout -> addWidget(back);



        menuBox -> setLayout(menuLayout);
        
        menuOuterLayout -> addWidget(menuBox);
        menuOuter -> setLayout(menuOuterLayout);

    popupLayout -> addWidget(menuOuter);
    popupBox -> setLayout(popupLayout);

    popupOuterLayout -> addWidget(popupShadow, 0, 0, 3, 3);
    popupOuterLayout -> addWidget(popupBox, 1, 1, 1, 1);
    popupOuter -> setLayout(popupOuterLayout);
    
    overLayout -> addWidget(sceneBox, 0, 0);
    overLayout -> addWidget(popupOuter, 0, 0);

    this -> setLayout(overLayout);




}

    
Field::~Field (){

            delete quit;
            delete back;

        delete menuLayout;
        delete menuBox;
        delete menuOuterLayout;
        delete menuOuter;

    delete popupEffect;
    delete popupLayout;
    delete popupBox;
    delete popupShadow;
    delete popupOuterLayout;
    delete popupOuter;

            delete menuButt;
            delete lifeSlf;

        delete rightBarLayout;
        delete rightBarBox;

                    delete advHand0;
                    delete advHand1;
                    delete advHand2;
                    delete advHand3;
                    delete advHand4;
                    delete advHand5;
                    delete advHand6;

                delete advHandLayout;
                delete advHand;
                
                    delete advMagic0;
                    delete advMagic1;
                    delete advMagic2;
                    delete advMagic3;
                    delete advMagic4;
                    delete advMagic5;
                    delete advMagic6;

                delete advMagicLayout;
                delete advMagic;
                
                    delete advMonst0;
                    delete advMonst1;
                    delete advMonst2;
                    delete advMonst3;
                    delete advMonst4;
                    delete advMonst5;
                    delete advMonst6;

                delete advMonstLayout;
                delete advMonst;

            delete advLayout;
            delete advBox;

                    delete slfMonst0;
                    delete slfMonst1;
                    delete slfMonst2;
                    delete slfMonst3;
                    delete slfMonst4;
                    delete slfMonst5;
                    delete slfMonst6;

                delete slfMonstLayout;
                delete slfMonst;
                
                    delete slfMagic0;
                    delete slfMagic1;
                    delete slfMagic2;
                    delete slfMagic3;
                    delete slfMagic4;
                    delete slfMagic5;
                    delete slfMagic6;

                delete slfMagicLayout;
                delete slfMagic;
                
                    delete slfHand0;
                    delete slfHand1;
                    delete slfHand2;
                    delete slfHand3;
                    delete slfHand4;
                    delete slfHand5;
                    delete slfHand6;
                
                delete slfHandLayout;
                delete slfHand;
       
            delete slfLayout;
            delete slfBox;
        
        delete arenaLayout;
        delete arenaBox;
        
        //delete arenaProxy;
        delete arenaScene;
        delete arenaView;

            delete actionButt;
            delete lifeAdv;
            delete card;

        delete leftBarLayout;
        delete leftBarBox;

    delete sceneLayout;
    delete sceneBox;
    
    delete overLayout;
}


void Field::emitIntroStack (){
    emit introStack();
}

void Field::openMenu (){
    popupOuter -> setVisible(true);
    menuButt -> setEnabled(false);
    back -> setFocus();
}

void Field::closeMenu (){
    popupOuter -> setVisible(false);
    menuButt -> setEnabled(true);
    menuButt -> setFocus();
}


void Field::init(){

    rotateXField();

    /*
    lastPosi = 0;

    fieldThread = new QThread;
    fieldTask = new FieldTask;
    fieldTask -> moveToThread(fieldThread);

    connect( this, SIGNAL(askWait()), fieldTask, SLOT(fieldLoop()) );
    connect( fieldTask, SIGNAL(newState()), this, SLOT(runNewState()) );
    
    connect( fieldThread, SIGNAL(finished()), fieldTask, SLOT(deleteLater()) );
    connect( fieldThread, SIGNAL(finished()), fieldThread, SLOT(deleteLater()) );

    fieldThread -> start();
 
    
    emit askWait();
    */

}


void FieldTask::fieldLoop (){

    Sleeper::msleep(8);

    emit newState();
}


void Field::runNewState (){

    lastPosi ++;

    rotateYField(lastPosi);

    if (lastPosi < 360){
        emit askWait();
    } else {
        rotateXField();
    }
}


void Field::resizeEvent(QResizeEvent *){

    arenaView -> fitInView( arenaScene->sceneRect());

}


void Field::rotateXField (){
/* 
    QTransform matrix;
    
    int w = arenaView -> width();
    int h = arenaView -> height();
    int v = h - (h * cos(15 * M_PI / 180)); 

    matrix.translate(0, -3 * v);
    matrix.translate(w/2, h);
    matrix.rotate(15, Qt::XAxis);
    matrix.translate(-1 * w/2,  -1 * h);

    arenaProxy -> setTransform(matrix);
*/
    arenaView -> fitInView( arenaScene->sceneRect());

}


void Field::rotateYField (int /* x */){
/* 
    QTransform matrix;
 
    int w = arenaView -> width();
    int h = arenaView -> height();
    int v = h - (h * cos(15 * M_PI / 180)); 


    matrix.translate(arenaView -> width()/2, arenaView -> height()/2);
    matrix.rotate(x);
    matrix.translate(-1*arenaView -> width()/2, -1*arenaView -> height()/2);
    
    matrix.translate(0, -3 * v);
    matrix.translate(w, h);
    matrix.rotate(15, Qt::XAxis);
    matrix.translate(-1 * w,  -1 * h);

    arenaProxy -> setTransform(matrix);
    arenaView -> fitInView( arenaScene->sceneRect());
*/
}


