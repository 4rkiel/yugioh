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

            
            menu = new QPushButton("menu", this);
            menu -> setFont(QFont("Font Awesome 5 Free", 14));
            menu -> setText("\uf0c9");
            
            rightBarLayout -> addWidget(menu);
           

            rightBarLayout -> addStretch();

            rightBarLayout -> addStretch();

            lifeSlf = new QLabel();
            QString strSlf = QString::fromUtf8("8000");
            lifeSlf -> setText(strSlf);

            rightBarLayout -> addWidget(lifeSlf);
           






        rightBarBox -> setObjectName("rightBarBox");
        rightBarBox -> setLayout(rightBarLayout);
    
        
    //popupLayout = new QGridStackedWidget;


        sceneLayout -> addWidget(leftBarBox, 0, 0, 3, 1);
        sceneLayout -> addWidget(arenaBox, 0, 1, 3, 5);
        sceneLayout -> addWidget(rightBarBox, 0, 6, 3, 1);
        sceneBox -> setLayout(sceneLayout);


    overLayout -> addWidget(sceneBox, 0, 0);

    this -> setLayout(overLayout);


/*
    // Text label

    QWidget * appBox = new QWidget;
    QVBoxLayout * box = new QVBoxLayout;


    QLabel * text2 = new QLabel();
    
    strLabel = QString::fromUtf8("      ");
    text2 -> setText(strLabel);
    text2 -> setAlignment(Qt::AlignCenter);
    text2 -> setTextInteractionFlags(Qt::TextSelectableByMouse);

    text2 -> setStyleSheet("background-color: rgba(85, 170, 255, 100);");
    text2 -> setMinimumWidth(250);
    text2 -> setMaximumWidth(500);
    text2 -> setMinimumHeight(400);
    text2 -> setMaximumHeight(800);

    box -> addWidget(text2);

    appBox -> setLayout(box);

    layout -> addWidget(appBox, 1, 1, 1, 1);



*/ 


/*
    // Button
    
    button = new QPushButton("Button", this);

    QIcon icoButton("nyancat.png");
    button -> setIcon(icoButton);

    QString strButton = QString::fromUtf8("😀 😀 😀");
    button -> setText(strButton);

    button -> setToolTip("Infobulle txt");

    layout -> addWidget(button, 2, 0, 2, 3);

    connect(button, SIGNAL(clicked()), this, SLOT(emitNewStack()));


    // Quit Button

    quit = new QPushButton("Quit", this);
     
    QIcon icoQuit("nyancat.png");
    quit -> setIcon(icoQuit);
    
    QString strQuit = QString::fromUtf8("😀 😀 😀");
    quit -> setText(strQuit);
    
    quit -> setToolTip("Infobulle txt");


    layout -> addWidget(quit, 4, 0, 2, 3);

    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));


*/


}

    
App::~App (){

    delete menu;
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
