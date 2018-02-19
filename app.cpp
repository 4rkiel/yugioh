#include "app.h"


App::App () {

    overLayout = new QGridLayout;
    //overLayout -> setAlignment(Qt::AlignCenter);
    overLayout -> setSpacing(0);
    overLayout -> setMargin(0);

  

    // Scene principale

    sceneBox = new QWidget;
    sceneLayout = new QGridLayout;
    sceneLayout -> setSpacing(0);
    sceneLayout -> setMargin(0);



        // Left bar

        leftBarBox = new QWidget;
        leftBarLayout = new QVBoxLayout;
        leftBarLayout -> setSpacing(0);
        leftBarLayout -> setMargin(0);
        leftBarLayout -> setAlignment(Qt::AlignCenter);


            // Text label

            lifeAdv = new QLabel();
            QString strAdv = QString::fromUtf8("8000");
            lifeAdv -> setText(strAdv);

            leftBarLayout -> addWidget(lifeAdv);
           

            leftBarLayout -> addStretch();


           
        leftBarBox -> setObjectName("leftBarBox");            
        leftBarBox -> setLayout(leftBarLayout);



        // Arena

        arenaBox = new QWidget;
        arenaLayout = new QGridLayout;


        arenaBox -> setObjectName("arenaBox");



        // Right Bar

        rightBarBox = new QWidget;
        rightBarLayout = new QVBoxLayout;
        rightBarLayout -> setSpacing(0);
        rightBarLayout -> setMargin(0);
        rightBarLayout -> setAlignment(Qt::AlignCenter);

            
            menuButt = new QPushButton;
            menuButt -> setFont(QFont("Font Awesome 5 Free", 14));
            menuButt -> setText("\uf0c9");
            
            connect(menuButt, SIGNAL(clicked()), this, SLOT(openMenu()));
            
            rightBarLayout -> addWidget(menuButt);
           

            rightBarLayout -> addStretch();


            // turn


            rightBarLayout -> addStretch();

            lifeSlf = new QLabel();
            QString strSlf = QString::fromUtf8("8000");
            lifeSlf -> setText(strSlf);

            rightBarLayout -> addWidget(lifeSlf);
           






        rightBarBox -> setObjectName("rightBarBox");
        rightBarBox -> setLayout(rightBarLayout);
    

    sceneLayout -> addWidget(leftBarBox, 0, 0, 3, 1);
    sceneLayout -> addWidget(arenaBox, 0, 1, 3, 5);
    sceneLayout -> addWidget(rightBarBox, 0, 6, 3, 1);
    sceneBox -> setLayout(sceneLayout);




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


    
        // TODO battle intro

        

        // menu

        menuOuter = new QWidget;
        menuOuterLayout = new QGridLayout;

        menuOuterLayout -> setSpacing(0);
        menuOuterLayout -> setMargin(0);



        menuBox = new QWidget;
        menuBox -> setObjectName("menuBox");
        menuLayout = new QVBoxLayout;
        menuLayout -> setAlignment(Qt::AlignCenter);
 
            back = new QPushButton;

//            QIcon icoButton("nyancat.png");
//            quit -> setIcon(icoButton);

            QString strBack = QString::fromUtf8("Retour");
            back -> setText(strBack);

            back -> setToolTip("Retour au Duel");

            connect(back, SIGNAL(clicked()), this, SLOT(closeMenu()));
            
            menuLayout -> addWidget(back);



            quit = new QPushButton;

            QIcon icoButton("nyancat.png");
            quit -> setIcon(icoButton);

            QString strButton = QString::fromUtf8("Quitter");
            quit -> setText(strButton);

            quit -> setToolTip("Quitter le Duel");

            connect(quit, SIGNAL(clicked()), this, SLOT(emitNewStack()));
            
            menuLayout -> addWidget(quit);



            


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

    
App::~App (){

            delete quit;
            delete back;

        delete menuLayout;
        delete menuBox;
        delete menuOuterLayout;
        delete menuOuter;
    
    delete popupLayout;
    delete popupBox;
    delete popupShadow;
    delete popupOuterLayout;
    delete popupOuter;

            delete menuButt;
            delete lifeSlf;
            delete lifeAdv;

        delete rightBarLayout;
        delete rightBarBox;
        delete arenaLayout;
        delete arenaBox;
        delete leftBarLayout;
        delete leftBarBox;

    delete sceneLayout;
    delete sceneBox;
    
    delete overLayout;
}


void App::emitNewStack (){
    emit newStack();
}

void App::openMenu (){
    popupOuter -> setVisible(true);
    menuButt -> setEnabled(false);
    back -> setFocus();
}

void App::closeMenu (){
    popupOuter -> setVisible(false);
    menuButt -> setEnabled(true);
    menuButt -> setFocus();
}
