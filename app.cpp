#include "app.h"


App::App () {

    layout = new QGridLayout;


    // Text label

    text = new QLabel();
    QString strLabel = QString::fromUtf8("Azerty");
    text -> setText(strLabel);
    text -> setAlignment(Qt::AlignCenter);
    text -> setTextInteractionFlags(Qt::TextSelectableByMouse);

    layout -> addWidget(text, 0, 0, 2, 3);


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



    this -> setLayout(layout);

}

    
App::~App (){

    delete text;
    delete button;
    delete quit;

    delete layout;
}


void App::emitNewStack (){
    emit newStack();
}
