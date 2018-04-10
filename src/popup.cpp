#include "../inc/popup.h"


Popup::Popup (){

    setVisible(false);

    layout = new QGridLayout;
    layout -> setSpacing(0);
    layout -> setMargin(0);
    layout -> setAlignment(Qt::AlignCenter);

    popupShadow = new QPushButton;
    popupShadow->setDefault(true);
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

        menuOuter = new QWidget;
        menuOuterLayout = new QGridLayout;


        // Choose Posi 

        posiBox = new QWidget;
        posiBox -> setObjectName("posiBox");
        posiLayout = new QGridLayout;
        posiLayout -> setAlignment(Qt::AlignCenter);


            posino = new ShadowButt("\uf0e3", tr("Atk"));
            posino -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            posino -> setToolTip(tr("Monstre en mode Attaque"));
            connect(posino, SIGNAL(clicked()), this, SLOT(atkMode()));
            posiLayout -> addWidget(posino, 1,0,1,1);

            posiya = new ShadowButt("\uf3ed", tr("Def"));
            posiya -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            posiya -> setToolTip(tr("Monstre en mode Defense"));
            connect(posiya, SIGNAL(clicked()), this, SLOT(defMode()));
            posiLayout -> addWidget(posiya, 1,1,1,1);

            posiback = new ShadowButt("\uf00d", tr("Annuler"));
            posiback -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            posiback -> setToolTip(tr("Annuler l'action"));
            connect(posiback, SIGNAL(clicked()), this, SLOT(closePosi()));
            posiLayout -> addWidget(posiback, 2,0,1,2);

            posiLabel = new QLabel(tr("Choisir la position"));
            posiLayout -> addWidget(posiLabel, 0,0,1,2);





        posiBox -> setLayout(posiLayout);
        posiBox -> setVisible(false);
        menuOuterLayout -> addWidget(posiBox, 0, 0, 1, 1);



        // Quit Safety

        quitBox = new QWidget;
        quitBox -> setObjectName("quitBox");
        quitLayout = new QGridLayout;
        quitLayout -> setAlignment(Qt::AlignCenter);


            quitno = new ShadowButt("\uf00d", tr("Non"));
            quitno -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            quitno -> setToolTip(tr("Croire en l'âme des cartes"));
            connect(quitno, SIGNAL(clicked()), this, SLOT(closeQuit()));
            quitLayout -> addWidget(quitno, 1,0,1,1);

            quitya = new ShadowButt("\uf00c", tr("Abandonner"));
            quitya -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            quitya -> setToolTip(tr("Abandonner le duel"));
            connect(quitya, SIGNAL(clicked()), this, SLOT(emitIntroStack()));
            quitLayout -> addWidget(quitya, 1,1,1,1);

            quitLabel = new QLabel(tr("Voulez-vous abandonner ?"));
            quitLayout -> addWidget(quitLabel, 0,0,1,2);



        quitBox -> setLayout(quitLayout);
        quitBox -> setVisible(false);
        menuOuterLayout -> addWidget(quitBox, 0, 0, 1, 1);


/*
        // Menu

        menuBox = new QWidget;
        menuBox -> setObjectName("menuBox");
        menuLayout = new QVBoxLayout;
        menuLayout -> setAlignment(Qt::AlignCenter);


            quit = new ShadowButt("\uf256", tr("Abandonner"));
            quit -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            quit -> setToolTip(tr("Quitter le Duel"));
            connect(quit, SIGNAL(clicked()), this, SLOT(openQuit()));
            menuLayout -> addWidget(quit);

            back = new ShadowButt("\uf078", tr("Fermer"));
            back -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            back -> setToolTip(tr("Retour au Duel"));
            connect(back, SIGNAL(clicked()), this, SLOT(closeMenu()));
            menuLayout -> addWidget(back);

        menuBox -> setLayout(menuLayout);
        menuBox -> setVisible(false);


        menuOuterLayout -> addWidget(menuBox, 0, 0, 1, 1);

*/
        
        
        menuOuter -> setLayout(menuOuterLayout);



    popupLayout -> addWidget(menuOuter);
    popupBox -> setLayout(popupLayout);

    layout -> addWidget(popupShadow, 0, 0, 3, 3);
    layout -> addWidget(popupBox, 1, 1, 1, 1);

    setLayout(layout);
}


Popup::~Popup (){

            delete posiback;     
            delete posino;
            delete posiya;
            delete posiLabel;

        delete posiLayout;
        delete posiBox;

            delete quitno;
            delete quitya;
            delete quitLabel;

        delete quitLayout;
        delete quitBox;

        //    delete quit;
        //    delete back;

        //delete menuLayout;
        //delete menuBox;
        
        delete menuOuterLayout;
        delete menuOuter;

    delete popupEffect;
    delete popupLayout;
    delete popupBox;
    delete popupShadow;

    delete layout;

}



void Popup::emitIntroStack (){
    emit introStack();
}


void Popup::openPosi (){
    
    openMenu();
    posiBox -> setVisible(true);
    posino -> setFocus();
}

void Popup::atkMode (){
    emit sendAtk();
    closePosi();
}

void Popup::defMode (){
    emit sendDef();
    closePosi();
}

void Popup::closePosi (){ 
    closeMenu();
}


void Popup::openQuit (){
    
    openMenu();
    quitBox -> setVisible(true);
    quitno -> setFocus();
}

void Popup::closeQuit (){
    closeMenu();
}


void Popup::openMenu (){
    setVisible(true);
}

void Popup::closeMenu (){
    
    posiBox -> setVisible(false);
    quitBox -> setVisible(false);
    setVisible(false);
}

