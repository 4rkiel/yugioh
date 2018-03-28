#include "../inc/field.h"

/******************************************************************************

	Widget implémentant le plateau de jeu

	Initialisé lors du lancement d'une partie

******************************************************************************/

Field::Field () {

    lockPreview = false;

    overLayout = new QGridLayout;
    overLayout -> setSpacing(0);
    overLayout -> setMargin(0);

  

    // Scene principale

    sceneBox = new QWidget;
    sceneLayout = new QGridLayout;
    sceneLayout -> setSpacing(0);
    sceneLayout -> setMargin(0);



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
                    ptr, SIGNAL(leftClick(int)),
                    this, SLOT(cardClicked(int))
                );

                connect(
                    ptr, SIGNAL(rightClick(int)),
                    this, SLOT(cardRightClicked(int))
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
        rightBarLayout -> setContentsMargins(10, 0, 10, 0);

 
            lifeAdv = new ShadowLab();
            QString strAdv = QString::fromUtf8("8000");
            lifeAdv -> setText(strAdv);
            lifeAdv -> setObjectName("Life");
            rightBarLayout -> addWidget(lifeAdv, 0, 1, 1, 1);

            
            menuButt = new ShadowButt("\uf0c9", "");
            menuButt -> setToolTip("Menu");
            connect(menuButt, SIGNAL(clicked()), this, SLOT(openMenu()));
            rightBarLayout -> addWidget(menuButt, 0, 3, 1, 1);
           
/*
            QSpacerItem * spacerRightTop = new QSpacerItem(5,1,
                QSizePolicy::Preferred,QSizePolicy::Expanding);
            rightBarLayout -> addItem(spacerRightTop, 1, 0);
*/            
            
            // Sidebar

            side = new QWidget;
            side -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            side -> setStyleSheet("background: #546E7A");
            sidebar = new QGridLayout;   

                sideTool = new QWidget;
                sideToolLayout = new QGridLayout;
                sideToolLayout -> setMargin(0);
                sideToolLayout -> setSpacing(0);

                    statsButt = new FlatButt("\uf277","");
                    statsButt -> setToolTip(tr("Duel"));
                    connect(statsButt, SIGNAL(clicked()), this, SLOT(setStats()));
                    sideToolLayout -> addWidget(statsButt, 0, 0);
                    
                    chatButt = new FlatButt("\uf086","");
                    chatButt -> setToolTip(tr("Chat"));
                    connect(chatButt, SIGNAL(clicked()), this, SLOT(setChat()));
                    sideToolLayout -> addWidget(chatButt, 0, 1);

                sideTool -> setLayout(sideToolLayout);
                    
                sidebar -> addWidget(sideTool, 0, 0, 1, 1);


                fullCard = new Duplica;
                fullCard -> setVisible(false);
                connect(fullCard, SIGNAL(clicked()), this, SLOT(previewClicked()));
                sidebar -> addWidget(fullCard, 0, 0, 10, 1);


                stats = new Stats;
                stats -> setVisible(false);
                sidebar -> addWidget(stats, 1, 0, 9, 1);

                chat = new Chat;
                chat -> setVisible(false);
                sidebar -> addWidget(chat, 1, 0, 9, 1);

                connect(chat, SIGNAL(msgSent(QString)), this, SLOT(sendMsg(QString)));
                currentSide = stats;


/*                QSpacerItem * spacerSide = new QSpacerItem(5,5,
                    QSizePolicy::Preferred,QSizePolicy::Expanding);
                sidebar -> addItem(spacerSide, 1, 0);
*/
            side -> setLayout(sidebar);
            rightBarLayout -> addWidget(side, 2, 0, 1, 5);

/*
            QSpacerItem * spacerRightBot = new QSpacerItem(5,1,
                QSizePolicy::Preferred,QSizePolicy::Expanding);
            rightBarLayout -> addItem(spacerRightBot, 3, 0);
*/

            lifeSlf = new ShadowLab();
            QString strSlf = QString::fromUtf8("8000");
            lifeSlf -> setText(strSlf);
            lifeSlf -> setObjectName("Life");
            rightBarLayout -> addWidget(lifeSlf, 4, 1, 1, 1);

            actionButt = new ShadowButt("\uf079", "");
            actionButt -> setToolTip(tr("Terminer le tour"));
            rightBarLayout -> addWidget(actionButt, 4, 3, 1, 1);
            connect(actionButt, SIGNAL(clicked()), this, SLOT(test()));


           


        rightBarBox -> setObjectName("rightBarBox");
        rightBarBox -> setLayout(rightBarLayout);
   

    sceneLayout -> addWidget(arenaBox, 0, 0, 3, 7);
    sceneLayout -> addWidget(rightBarBox, 0, 7, 3, 1);
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
        
        menuOuterLayout -> addWidget(menuBox, 0, 0, 1, 1);
        menuOuter -> setLayout(menuOuterLayout);

    popupLayout -> addWidget(menuOuter);
    popupBox -> setLayout(popupLayout);

    popupOuterLayout -> addWidget(popupShadow, 0, 0, 3, 3);
    popupOuterLayout -> addWidget(popupBox, 1, 1, 1, 1);
    popupOuter -> setLayout(popupOuterLayout);
    
    overLayout -> addWidget(sceneBox, 0, 0);
    overLayout -> addWidget(popupOuter, 0, 0);

    // key shortcut
    shortcut = new QShortcut(QKeySequence("Escape"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(openQuit()));

    this -> setLayout(overLayout);


}

    
Field::~Field (){

            delete quitno;
            delete quitya;
            delete quitLabel;
        delete shortcut;

        delete quitLayout;
        delete quitBox;

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


            delete statsButt;
            delete chatButt;

            delete sideToolLayout;
            delete sideTool;

            delete stats;
            delete chat;

            delete fullCard;
            
            delete sidebar;
            delete side;

            delete actionButt;
            delete lifeAdv;
            delete menuButt;
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
    
        delete sceneLayout;
    delete sceneBox;
    
    delete overLayout;
}


void Field::init(){
	fullCard -> setVisible(false);
    stats -> setVisible(true);
}


void Field::emitIntroStack (){
    emit introStack();
}

void Field::openQuit (){
    menuBox -> setVisible(false);
    quitBox -> setVisible(true);
    quitno -> setFocus();
}

void Field::closeQuit (){
    quitBox -> setVisible(false);
    menuBox -> setVisible(true);
    back -> setFocus();
}

void Field::openMenu (){
    popupOuter -> setVisible(true);
    menuButt -> setEnabled(false);
    back -> setFocus();
}

void Field::closeMenu (){
    quitBox -> setVisible(false);
    menuBox -> setVisible(true);
    popupOuter -> setVisible(false);
    menuButt -> setEnabled(true);
    menuButt -> setFocus();
}


void Field::previewClicked(){

    if (lockPreview){

        lockPreview = false;
        cardOut();
    }
}

void Field::cardRightClicked(int x){
	std::cout << x << " Right Clicked \n";

    if (
        (! fieldStack -> at(x) -> isDeck() ) &&
        (! fieldStack -> at(x) -> isFuse() ) &&
        (! fieldStack -> at(x) -> isGrave() )
    ){
        if (lockPreview){

            lockPreview = false;
            cardHover();

        } else {

            cardHover();
            lockPreview = true;
        }
    }
}

void Field::cardClicked(int x){
    std::cout << x << " clicked \n"; 
}

void Field::cardEntered(int x){
    std::cout << x << " entered \n";
    
    cardHover();
}

void Field::cardLeaved(int x){
    std::cout << x << " leaved \n";

    cardOut();
}

void Field::cardHover (){

    fullCard -> setTitle("Dragon Blanc aux Yeux Bleus");
    fullCard -> setPic("img/cards/001/LOB-EN001-Blue-EyesWhiteDragon2ndart.jpg");
    fullCard -> setDesc(
        "Ce dragon légendaire est un puissant "
        "moteur de destruction. Rares sont ceux qui ont survécus à cette "
        "surpuissante créature quasiment invincible pour en parler."
    );
    fullCard -> setStat("3000","2500");

    if (!lockPreview){
        sideTool -> setVisible(false);
        currentSide -> setVisible(false);
        fullCard -> setVisible(true);
    }
}

void Field::cardOut (){

    if (!lockPreview){
        fullCard -> setVisible(false);
        currentSide -> setVisible(true);
        sideTool -> setVisible(true);
    }
}




void Field::setStats(){

    currentSide -> setVisible(false);
    stats -> setVisible(true);
    currentSide = stats;
}

void Field::setChat(){
    
    currentSide -> setVisible(false);
    chat -> setVisible(true);
    currentSide = chat;
}

void Field::sendMsg(QString str){

    if(str.startsWith("#"))
    {
        transmettre(str);
        QStringRef * decoupe = new QStringRef(&str,1,str.length()-1);
        chat->addText(decoupe->toString());
    }
    else
        chat -> addText(str);
}



void Field::setCarte(QString img, int x){
    fieldStack -> at(x) -> setPic(img);
}

void Field::poseCarte(int x){
    fieldStack -> at(x) -> posePic();
}

void Field::maskCarte(int x){
    fieldStack -> at(x) -> maskPic();
}

void Field::rmCarte(int x){
    fieldStack -> at(x) -> rmPic();
}








void Field::test (){

    fieldStack -> at(3) -> posePic();
    fieldStack -> at(3) -> rmPic();
    
    fieldStack -> at(3) -> setPic("img/cards/001/LOB-EN125-GaiatheDragonChampion.jpg");
    fieldStack -> at(79) -> setPic("img/cards/001/LOB-EN125-GaiatheDragonChampion.jpg");


    fieldStack -> at(77) -> posePic();

    fieldStack -> at(10) -> maskPic();

}
