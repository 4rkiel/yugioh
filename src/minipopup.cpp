#include "../inc/minipopup.h"


MiniPopup::MiniPopup (){

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
    connect(popupShadow, SIGNAL(clicked()), this, SLOT(checkCloseMenu()));

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



        // Choose Magic Posi 

        magiBox = new QWidget;
        magiBox -> setObjectName("magiBox");
        magiLayout = new QGridLayout;
        magiLayout -> setAlignment(Qt::AlignCenter);


            magino = new ShadowButt("\uf06e", tr("Visible"));
            magino -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            magino -> setToolTip(tr("Carte face visible"));
            connect(magino, SIGNAL(clicked()), this, SLOT(visiMode()));
            magiLayout -> addWidget(magino, 1,0,1,1);

            magiya = new ShadowButt("\uf070", tr("Masquée"));
            magiya -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            magiya -> setToolTip(tr("Carte face masquée"));
            connect(magiya, SIGNAL(clicked()), this, SLOT(hideMode()));
            magiLayout -> addWidget(magiya, 1,1,1,1);

            magiback = new ShadowButt("\uf00d", tr("Annuler"));
            magiback -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            magiback -> setToolTip(tr("Annuler l'action"));
            connect(magiback, SIGNAL(clicked()), this, SLOT(closeMagi()));
            magiLayout -> addWidget(magiback, 2,0,1,2);

            magiLabel = new QLabel(tr("Choisir la position"));
            magiLayout -> addWidget(magiLabel, 0,0,1,2);


        magiBox -> setLayout(magiLayout);
        magiBox -> setVisible(false);
        menuOuterLayout -> addWidget(magiBox, 0, 0, 1, 1);




        // Card SEE 

        seeBox = new QWidget;
        seeBox -> setObjectName("seeBox");
        seeLayout = new QGridLayout;
        seeLayout -> setAlignment(Qt::AlignCenter);

            seeBack = new ShadowButt("\uf078", tr("Retour"));
            seeBack -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            seeBack -> setToolTip(tr("Retourner au terrain"));
            connect(seeBack, SIGNAL(clicked()), this, SLOT(closeSee()));
            seeLayout -> addWidget(seeBack, 1,1,1,1);





        seeBox -> setLayout(seeLayout);
        seeBox -> setVisible(false);
        menuOuterLayout -> addWidget(seeBox, 0, 0, 1, 1);



        
       


        menuOuter -> setLayout(menuOuterLayout);



    popupLayout -> addWidget(menuOuter);
    popupBox -> setLayout(popupLayout);

    layout -> addWidget(popupShadow, 0, 0, 3, 3);
    layout -> addWidget(popupBox, 1, 1, 1, 1);

    //shortcut echap
    shortcut = new QShortcut(QKeySequence("Escape"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(closeMenu()));

    setLayout(layout);
}


MiniPopup::~MiniPopup (){

        delete shortcut;
            delete posiback;     
            delete posino;
            delete posiya;
            delete posiLabel;

        delete posiLayout;
        delete posiBox;

            delete magiback;     
            delete magino;
            delete magiya;
            delete magiLabel;

        delete magiLayout;
        delete magiBox;


            delete winLabel;
            delete winBack;
            delete winQuit;

        delete winLayout;
        delete winBox;

            delete lostLabel;
            delete lostBack;
            delete lostQuit;

        delete lostLayout;
        delete lostBox;



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



void MiniPopup::emitIntroStack (){
    emit introStack();
}


void MiniPopup::openPosi (){
    
    openMenu();
    posiBox -> setVisible(true);
    posino -> setFocus();
}

void MiniPopup::atkMode (){
    emit sendAtk();
    closePosi();
}

void MiniPopup::defMode (){
    emit sendDef();
    closePosi();
}

void MiniPopup::closePosi (){ 
    closeMenu();
}


void MiniPopup::openMagi (){
    
    openMenu();
    magiBox -> setVisible(true);
    magino -> setFocus();
}

void MiniPopup::visiMode (){
    emit sendVisi();
    closeMagi();
}

void MiniPopup::hideMode (){
    emit sendHide();
    closeMagi();
}

void MiniPopup::closeMagi (){ 
    closeMenu();
}



void MiniPopup::openSee (){
    
    openMenu();
    seeBox -> setVisible(true);
    seeBack -> setFocus();
}


void MiniPopup::openChooseLocked (){
    
    openMenu();
    chooseBox -> setVisible(true);
}


void MiniPopup::openChoose (){
    
    openMenu();
    seeBox -> setVisible(true);
    seeBack -> setFocus();
}


void MiniPopup::closeSee (){

    closeMenu();
}



void MiniPopup::checkCloseMenu (){

    if (!locked){
        closeMenu();
    }
}


void MiniPopup::openMenu (){
    setVisible(true);
    emit moiFocus();
}

void MiniPopup::closeMenu (){
    
    chooseBox -> setVisible(false);
    seeBox -> setVisible(false);
    posiBox -> setVisible(false);
    magiBox -> setVisible(false);
    setVisible(false);
    emit focusField();
}

