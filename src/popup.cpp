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





        // LOST 

        lostBox = new QWidget;
        lostBox -> setObjectName("lostBox");
        lostLayout = new QGridLayout;
        lostLayout -> setAlignment(Qt::AlignCenter);

            lostBack = new ShadowButt("\uf078", tr("Retour"));
            lostBack -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            lostBack -> setToolTip(tr("Retourner au terrain"));
            connect(lostBack, SIGNAL(clicked()), this, SLOT(closeLost()));
            lostLayout -> addWidget(lostBack, 1,1,1,1);

            lostQuit = new ShadowButt("\uf015", tr("Quitter"));
            lostQuit -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            lostQuit -> setToolTip(tr("Retour à l'accueil"));
            connect(lostQuit, SIGNAL(clicked()), this, SLOT(emitIntroStack()));
            lostLayout -> addWidget(lostQuit, 1,0,1,1);

            lostLabel = new QLabel(tr("Vous avez Perdu..."));
            lostLayout -> addWidget(lostLabel, 0,0,1,2);


        lostBox -> setLayout(lostLayout);
        lostBox -> setVisible(false);
        menuOuterLayout -> addWidget(lostBox, 0, 0, 1, 1);





        // WIN 

        winBox = new QWidget;
        winBox -> setObjectName("winBox");
        winLayout = new QGridLayout;
        winLayout -> setAlignment(Qt::AlignCenter);

            winBack = new ShadowButt("\uf078", tr("Retour"));
            winBack -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            winBack -> setToolTip(tr("Retourner au terrain"));
            connect(winBack, SIGNAL(clicked()), this, SLOT(closeWin()));
            winLayout -> addWidget(winBack, 1,1,1,1);

            winQuit = new ShadowButt("\uf015", tr("Quitter"));
            winQuit -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            winQuit -> setToolTip(tr("Retour à l'accueil"));
            connect(winQuit, SIGNAL(clicked()), this, SLOT(emitIntroStack()));
            winLayout -> addWidget(winQuit, 1,0,1,1);

            winLabel = new QLabel(tr("Vous avez Gagné !"));
            winLayout -> addWidget(winLabel, 0,0,1,2);


        winBox -> setLayout(winLayout);
        winBox -> setVisible(false);
        menuOuterLayout -> addWidget(winBox, 0, 0, 1, 1);




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


void Popup::openMagi (){
    
    openMenu();
    magiBox -> setVisible(true);
    magino -> setFocus();
}

void Popup::visiMode (){
    emit sendVisi();
    closeMagi();
}

void Popup::hideMode (){
    emit sendHide();
    closeMagi();
}

void Popup::closeMagi (){ 
    closeMenu();
}



void Popup::openWin (){
    
    openMenu();
    winBox -> setVisible(true);
    winBack -> setFocus();
}

void Popup::closeWin (){
    closeMenu();
}


void Popup::openLost (){
    
    openMenu();
    lostBox -> setVisible(true);
    lostBack -> setFocus();
}

void Popup::closeLost (){
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
    
    winBox -> setVisible(false);
    lostBox -> setVisible(false);
    posiBox -> setVisible(false);
    quitBox -> setVisible(false);
    setVisible(false);
}

