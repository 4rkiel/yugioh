#include "../inc/field.h"

/******************************************************************************

	Widget implémentant le plateau de jeu

	Initialisé lors du lancement d'une partie

******************************************************************************/

Field::Field () {

    overLayout = new QGridLayout;
    overLayout -> setSpacing(0);
    overLayout -> setMargin(0);

  

    // Scene principale

    sceneBox = new QWidget;
    sceneLayout = new QGridLayout;
    sceneLayout -> setSpacing(0);
    sceneLayout -> setMargin(0);


        // Left bar ...........................................................

        leftBarBox = new QWidget;
        leftBarLayout = new QGridLayout;
        leftBarLayout -> setSpacing(0);
        leftBarLayout -> setMargin(0);


            // Text label

            lifeAdv = new ShadowLab();
            QString strAdv = QString::fromUtf8("8000");
            lifeAdv -> setText(strAdv);
            lifeAdv -> setObjectName("Life");
            leftBarLayout -> addWidget(lifeAdv, 0, 1, 1, 1);

            
            
            QSpacerItem * spacerLeftTop = new QSpacerItem(3,1,
                QSizePolicy::Preferred,QSizePolicy::Expanding);
            leftBarLayout -> addItem(spacerLeftTop, 1, 0);


            intel = new ShadowLab();
            intel -> setObjectName("Intel");
            intel -> setWordWrap(true);
            leftBarLayout -> addWidget(intel, 2, 0, 1, 3);
            
            
            QSpacerItem * spacerLeftBot = new QSpacerItem(3,1,
                QSizePolicy::Preferred,QSizePolicy::Expanding);
            leftBarLayout -> addItem(spacerLeftBot, 3, 0);



            actionButt = new ShadowButt("\uf04b", "");
            actionButt -> setToolTip("Terminer le tour");
            leftBarLayout -> addWidget(actionButt, 4, 1, 1, 1);
            connect(actionButt, SIGNAL(clicked()), this, SLOT(test()));

           
        leftBarBox -> setObjectName("leftBarBox");            
        leftBarBox -> setLayout(leftBarLayout);



        // Arena ..............................................................

        fieldStack = new std::vector<SlotCard *> (150, nullptr);


        arenaBox = new QWidget;
        arenaBox -> setObjectName("arenaBox");
        arenaLayout = new QGridLayout;

            // Opponent 
                
            advBox = new QWidget;
            advBox -> setObjectName("advBox");
            advLayout = new QGridLayout;
            advLayout -> setSpacing(0);
            advLayout -> setMargin(0);
            advLayout -> setContentsMargins(0,5,0,10);

                advHand = new QWidget;
                advHand -> setObjectName("advHand");
                advHandLayout = new QHBoxLayout;
                advHandLayout -> setMargin(0);
                advHandLayout -> setSpacing(0);
                advHandLayout -> setContentsMargins(0,0,0,4);

                    for (int k=89; k<=95; k++){
                        fieldStack -> at(k) = new SlotCard(k);
                        advHandLayout -> addWidget(fieldStack -> at(k));
                    }

                advHand -> setLayout(advHandLayout);
                advLayout -> addWidget(advHand, 0,0,1,1);

                advMagic = new QWidget;
                advMagic -> setObjectName("advMagic");
                advMagicLayout = new QHBoxLayout;
                advMagicLayout -> setMargin(0);
                advMagicLayout -> setSpacing(0);
                advMagicLayout -> setContentsMargins(0,2,0,2);
 
                    for (int k=82; k<=88; k++){
                        fieldStack -> at(k) = new SlotCard(k);
                        advMagicLayout -> addWidget(fieldStack -> at(k));
                    }
               
                advMagic -> setLayout(advMagicLayout);
                advLayout -> addWidget(advMagic, 1,0,1,1);

                advMonst = new QWidget;
                advMonst -> setObjectName("advMonst");
                advMonstLayout = new QHBoxLayout;
                advMonstLayout -> setMargin(0);
                advMonstLayout -> setSpacing(0);
                advMonstLayout -> setContentsMargins(0,2,0,2);
 
                    for (int k=75; k<=81; k++){
                        fieldStack -> at(k) = new SlotCard(k);
                        advMonstLayout -> addWidget(fieldStack -> at(k));
                    }
               
                advMonst -> setLayout(advMonstLayout);
                advLayout -> addWidget(advMonst,2,0,1,1);

            advBox -> setLayout(advLayout);
            arenaLayout -> addWidget(advBox, 0,0,1,1);

                
                // Self

            slfBox = new QWidget;
            slfBox -> setObjectName("slfBox");
            slfLayout = new QGridLayout;
            slfLayout -> setMargin(0);
            slfLayout -> setSpacing(0);
            slfLayout -> setContentsMargins(0,10,0,5);
            
                slfMonst = new QWidget;
                slfMonst -> setObjectName("slfMonst");
                slfMonstLayout = new QHBoxLayout;
                slfMonstLayout -> setMargin(0);
                slfMonstLayout -> setSpacing(0);
                slfMonstLayout -> setContentsMargins(0,2,0,2);
     
                    for (int k=0; k<=6; k++){
                        fieldStack -> at(k) = new SlotCard(k);
                        slfMonstLayout -> addWidget(fieldStack -> at(k));
                    }
                    
                slfMonst -> setLayout(slfMonstLayout);
                slfLayout -> addWidget(slfMonst, 0,0,1,1);

                slfMagic = new QWidget;
                slfMagic -> setObjectName("slfMagic");
                slfMagicLayout = new QHBoxLayout;
                slfMagicLayout -> setMargin(0);
                slfMagicLayout -> setSpacing(0);
                slfMagicLayout -> setContentsMargins(0,2,0,2);
     
                    for (int k=7; k<=13; k++){
                        fieldStack -> at(k) = new SlotCard(k);
                        slfMagicLayout -> addWidget(fieldStack -> at(k));
                    }
                    
                slfMagic -> setLayout(slfMagicLayout);
                slfLayout -> addWidget(slfMagic, 1,0,1,1);

                slfHand = new QWidget;
                slfHand -> setObjectName("slfHand");
                slfHandLayout = new QHBoxLayout;
                slfHandLayout -> setMargin(0);
                slfHandLayout -> setSpacing(0);
                slfHandLayout -> setContentsMargins(0,4,0,0);
      
                    for (int k=14; k<=20; k++){
                        fieldStack -> at(k) = new SlotCard(k);
                        slfHandLayout -> addWidget(fieldStack -> at(k));
                    }
                    
                slfHand -> setLayout(slfHandLayout);
                slfLayout -> addWidget(slfHand, 2,0,1,1);

            slfBox -> setLayout(slfLayout);
            arenaLayout -> addWidget(slfBox, 1,0,1,1);

        arenaBox -> setLayout(arenaLayout);
        

       // connect'ing cards to field

        for (int k=0; k<150; k++){
            if (fieldStack -> at(k) != nullptr){
                
                SlotCard * ptr = fieldStack -> at(k);

                connect(
                    ptr, SIGNAL(clicked(int)),
                    this, SLOT(cardClicked(int))
                );

                connect(
                    ptr, SIGNAL(entered(int)),
                    this, SLOT(cardEntered(int))
                );

                connect(
                    ptr, SIGNAL(leaved(int)),
                    this, SLOT(cardLeaved(int))
                );

            }
        }




        // Right Bar ..........................................................

        rightBarBox = new QWidget;
        rightBarLayout = new QGridLayout;
        rightBarLayout -> setSpacing(0);
        rightBarLayout -> setMargin(0);
        rightBarLayout -> setAlignment(Qt::AlignCenter);

            
            menuButt = new ShadowButt("\uf0c9", "");
            menuButt -> setToolTip("Menu");
            connect(menuButt, SIGNAL(clicked()), this, SLOT(openMenu()));
            rightBarLayout -> addWidget(menuButt, 0, 1, 1, 1);
           

            QSpacerItem * spacerRightTop = new QSpacerItem(3,1,
                QSizePolicy::Preferred,QSizePolicy::Expanding);
            rightBarLayout -> addItem(spacerRightTop, 1, 0);
            
            
            fullCard = new Duplica();
//            fullCard -> setObjectName("Card");
//            fullCard -> setWordWrap(true);
            rightBarLayout -> addWidget(fullCard, 2, 0, 1, 3);


            QSpacerItem * spacerRightBot = new QSpacerItem(3,1,
                QSizePolicy::Preferred,QSizePolicy::Expanding);
            rightBarLayout -> addItem(spacerRightBot, 3, 0);


            lifeSlf = new ShadowLab();
            QString strSlf = QString::fromUtf8("8000");
            lifeSlf -> setText(strSlf);
            lifeSlf -> setObjectName("Life");

            rightBarLayout -> addWidget(lifeSlf, 4, 1, 1, 1);
           



        rightBarBox -> setObjectName("rightBarBox");
        rightBarBox -> setLayout(rightBarLayout);
   

    sceneLayout -> addWidget(leftBarBox, 0, 0, 3, 1);
    sceneLayout -> addWidget(arenaBox, 0, 1, 3, 5);
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
            delete fullCard;
            delete lifeSlf;

        delete rightBarLayout;
        delete rightBarBox;
 
        for (int k=0; k<150; k++){
            if (fieldStack -> at(k) != nullptr){
                delete fieldStack -> at(k);
            }
        }
        
        delete fieldStack;

                delete advHandLayout;
                delete advHand;
                
                delete advMagicLayout;
                delete advMagic;
                
                delete advMonstLayout;
                delete advMonst;

            delete advLayout;
            delete advBox;

                delete slfMonstLayout;
                delete slfMonst;
                
                delete slfMagicLayout;
                delete slfMagic;
                
                delete slfHandLayout;
                delete slfHand;
       
            delete slfLayout;
            delete slfBox;
        
        delete arenaLayout;
        delete arenaBox;

            delete actionButt;
            delete intel;
            delete lifeAdv;

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


void Field::cardHover (){

    QString strCard = QString::fromUtf8(
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
//    fullCard -> setText(strCard);

}


void Field::cardClicked(int x){
    std::cout << x << " clicked \n"; 
}

void Field::cardEntered(int x){
    std::cout << x << " entered \n";
}

void Field::cardLeaved(int x){
    std::cout << x << " leaved \n";
}



void Field::test (){

    fieldStack -> at(3) -> setPic("img/cards/001/LOB-EN125-GaiatheDragonChampion.jpg");
    fieldStack -> at(79) -> setPic("img/cards/001/LOB-EN125-GaiatheDragonChampion.jpg");

    cardHover();

}
