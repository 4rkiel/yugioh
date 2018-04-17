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




        // Quit After Fight

        endBox = new QWidget;
        endBox -> setObjectName("endBox");
        endLayout = new QGridLayout;
        endLayout -> setAlignment(Qt::AlignCenter);


            endno = new ShadowButt("\uf00d", tr("Non"));
            endno -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            endno -> setToolTip(tr("Rester sur le terrain"));
            connect(endno, SIGNAL(clicked()), this, SLOT(closeQuit()));
            endLayout -> addWidget(endno, 1,0,1,1);

            endya = new ShadowButt("\uf00c", tr("Quitter"));
            endya -> setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            endya -> setToolTip(tr("Retour à l'accueil"));
            connect(endya, SIGNAL(clicked()), this, SLOT(emitIntroStack()));
            endLayout -> addWidget(endya, 1,1,1,1);

            endLabel = new QLabel(tr("Quitter le terrain ?"));
            endLayout -> addWidget(endLabel, 0,0,1,2);



        endBox -> setLayout(endLayout);
        endBox -> setVisible(false);
        menuOuterLayout -> addWidget(endBox, 0, 0, 1, 1);




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


Popup::~Popup (){

        delete shortcut;

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

            delete endno;
            delete endya;
            delete endLabel;

        delete endLayout;
        delete endBox;

            delete quitno;
            delete quitya;
            delete quitLabel;

        delete quitLayout;
        delete quitBox;

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



void Popup::openEnd (){
    
    openMenu();
    endBox -> setVisible(true);
    endno -> setFocus();
}

void Popup::closeEnd (){
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
    emit moiFocus();
}


void Popup::closeMenu (){
    
    winBox -> setVisible(false);
    lostBox -> setVisible(false);
    quitBox -> setVisible(false);
    endBox -> setVisible(false);
    setVisible(false);
    emit focusField();
}

