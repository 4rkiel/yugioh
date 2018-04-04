#include "../inc/field.h"

/******************************************************************************

Widget implémentant le plateau de jeu

Initialisé lors du lancement d'une partie

******************************************************************************/

Field::Field () {

    lockPreview = false;

    retained = -1;


    layout = new QGridLayout;
    layout -> setSpacing(0);
    layout -> setMargin(0);


        infoBox = new QWidget;
        infoBox -> setObjectName("infoBox");
        infoBox -> setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

        iffect = new QGraphicsDropShadowEffect;
        iffect -> setBlurRadius(5);
        iffect -> setXOffset(0);
        iffect -> setYOffset(5);
        iffect -> setColor(QColor(0,0,0,150));

        infoBox -> setGraphicsEffect(iffect);
        
        infoLayout = new QHBoxLayout;
        infoLayout -> setContentsMargins(0,0,0,0);
        infoLayout -> setSpacing(0);
        infoLayout -> setMargin(0);
       

            // Info

//            infoLayout -> addStretch(3);

            lifeBox = new QWidget;
            lifeBox -> setObjectName("lifeBox");
            lifeBox -> setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            lifeLayout = new QHBoxLayout;

            lifeLayout -> setSpacing(0);
            lifeLayout -> setMargin(0);
        
            QSettings settings;
            baseLife = settings.value("lifePoints", "8000").toString();
            int bl = baseLife.toInt();

            lifeSlf = new QLabel;
            lifeSlf -> setText(baseLife);
            lifeLayout -> addWidget(lifeSlf);
            
            icoSlf = new QLabel;
            icoSlf -> setFont(QFont("Font Awesome 5 Free", 12));
            icoSlf -> setText("\uf103");
            lifeLayout -> addWidget(icoSlf);


            progressSlf = new QProgressBar;
            progressSlf -> setRange(0,bl);
            progressSlf -> setInvertedAppearance(true);
            progressSlf -> setOrientation(Qt::Horizontal);
            progressSlf -> setTextVisible(false);
            progressSlf -> setValue(bl);
            lifeLayout -> addWidget(progressSlf);
           

            icoLife = new QLabel;
            icoLife -> setFont(QFont("Font Awesome 5 Free", 12));
            icoLife -> setText("\uf0e7");
            lifeLayout -> addWidget(icoLife);


//            infoLayout -> addStretch(1);

            progressAdv = new QProgressBar;
            progressAdv -> setRange(0,bl);
            progressAdv -> setOrientation(Qt::Horizontal);
            progressAdv -> setTextVisible(false);
            progressAdv -> setValue(bl);
            lifeLayout -> addWidget(progressAdv);


            icoAdv = new QLabel;
            icoAdv -> setFont(QFont("Font Awesome 5 Free", 12));
            icoAdv -> setText("\uf102");
            lifeLayout -> addWidget(icoAdv);

            lifeAdv = new QLabel;
            lifeAdv -> setText(baseLife);
            lifeLayout -> addWidget(lifeAdv);

            lifeBox -> setLayout(lifeLayout);
            infoLayout -> addWidget(lifeBox);

            


            // Quit Button
            
            menuButt = new FlatButt("\uf0c9", "");
            menuButt -> setToolTip("Menu");
            menuButt -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
            infoLayout -> addWidget(menuButt);


        infoBox -> setLayout(infoLayout);



///////////////////////////

    overField = new QWidget; 
    overField -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    overLayout = new QGridLayout;
    overLayout -> setSpacing(0);
    overLayout -> setMargin(0);



    // Popup Menu

    popup = new Popup;

    connect(popup, SIGNAL(introStack()), this, SLOT(emitIntroStack()));
    connect(popup, SIGNAL(sendAtk()), this, SLOT(emitAtk()));
    connect(popup, SIGNAL(sendDef()), this, SLOT(emitDef()));

    connect(menuButt, SIGNAL(clicked()), popup, SLOT(openMenu()));



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
        






        // Right Bar ..........................................................

        rightBarBox = new QWidget;
        rightBarBox -> setObjectName("rightBarBox");
        
        rightBarLayout = new QGridLayout;
        rightBarLayout -> setSpacing(0);
        rightBarLayout -> setMargin(0);
        rightBarLayout -> setAlignment(Qt::AlignCenter);
        rightBarLayout -> setContentsMargins(10, 10, 10, 0);

          
    /*
            QSpacerItem * spacerRightTop = new QSpacerItem(5,1,
                QSizePolicy::Preferred,QSizePolicy::Expanding);
            rightBarLayout -> addItem(spacerRightTop, 1, 0);
    */            
            
            // Sidebar

            side = new QWidget;
            side -> setObjectName("sidebar");
            side -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            sidebar = new QGridLayout;   
            sidebar -> setSpacing(0);
            sidebar -> setMargin(0);
            sidebar -> setContentsMargins(0,0,0,0);

                sideTool = new QWidget;
                sideTool -> setObjectName("sideSelector");
                sideTool -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

                sideToolLayout = new QGridLayout;
                sideToolLayout -> setMargin(0);
                sideToolLayout -> setSpacing(0);
                sideToolLayout -> setContentsMargins(0,0,0,0);

                    statsButt = new FlatButt("\uf277","");
                    statsButt -> setToolTip(tr("Informations du Duel"));
                    statsButt -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
                    connect(statsButt, SIGNAL(clicked()), this, SLOT(setStats()));
                    sideToolLayout -> addWidget(statsButt, 0, 0);
                    
                    chatButt = new FlatButt("\uf086","");
                    chatButt -> setToolTip(tr("Chat et Historique"));
                    chatButt -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
                    connect(chatButt, SIGNAL(clicked()), this, SLOT(setChat()));
                    sideToolLayout -> addWidget(chatButt, 0, 1);

                    currentButt = statsButt;
                    currentButt -> setProperty("down", true);

                sideTool -> setVisible(false);
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

            side -> setLayout(sidebar);
            rightBarLayout -> addWidget(side, 2, 0, 1, 5);


            actionButt = new ShadowButt("\uf079", "");
            actionButt -> setToolTip(tr("Terminer le tour"));
            rightBarLayout -> addWidget(actionButt, 4, 3, 1, 1);
            connect(actionButt, SIGNAL(clicked()), this, SLOT(test()));


           


        rightBarBox -> setLayout(rightBarLayout);


    sceneLayout -> addWidget(arenaBox, 0, 0, 3, 7);
    sceneLayout -> addWidget(rightBarBox, 0, 7, 3, 1);
    sceneBox -> setLayout(sceneLayout);


    overLayout -> addWidget(sceneBox, 0, 0);

    overField -> setLayout(overLayout);


    layout -> addWidget(overField, 1, 0, 4, 3);
    layout -> addWidget(infoBox, 0,0,1,3);
    layout -> addWidget(popup, 0, 0, 5, 3);

    //key shortcut
    shortcut = new QShortcut(QKeySequence("Escape"), this);
    connect(shortcut, SIGNAL(activated()), popup, SLOT(openMenu()));

    setLayout(layout);

}


Field::~Field (){

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

    delete popup;

    delete overLayout;
    
    delete overField;

    delete menuButt;
    delete icoAdv;
    delete lifeAdv;
    delete progressAdv;
    delete icoLife;
    delete icoSlf;
    delete lifeSlf;
    delete progressSlf;

    delete lifeLayout;
    delete lifeBox;

    delete infoLayout;
    delete iffect;
    delete infoBox;
    
    delete layout;

}


void Field::init(){
    fullCard -> setVisible(false);
    stats -> setVisible(true);
    sideTool -> setVisible(true);
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
                 ptr, SIGNAL(doubleClick(int)),
                 this, SLOT(cardDoubleClicked(int))
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
}


/* Popup functions */

void Field::emitIntroStack (){
    emit introStack();
}

void Field::openChoosePosi (){
    popup -> openPosi();
}

void Field::emitAtk (){
    emit sendAtk();
}

void Field::emitDef (){
    emit sendDef();
}


/* Lock Preview */

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



/* Field Actions */

void Field::cardDoubleClicked(int x){
    std::cout << x << " Double clicked \n"; 
    emit doubleClicked(x);
}

void Field::cardClicked(int x){
    std::cout << x << " clicked \n";

    SlotCard * that = fieldStack -> at(x);

    if (retained == x){
        
        retained = -1;

    } else if (retained == -1){

        if (
            ! that -> isAdv() && 
            ! that -> isDeck() && 
            ! that -> isGrave() && 
            ! that -> isFuse() 
        ){
            retained = x;
        }

    } else {

        if (
            ! that -> isDeck() &&
            ! that -> isGrave() &&
            ! that -> isFuse()
        ){
            std::cout << "biclicked: " << retained << " " << x << "\n";
            emit biClick(retained, x);
            retained = -1;
        }
    }
}

void Field::cardEntered(int x){
    std::cout << x << " entered \n";

    cardHover();
}

void Field::cardLeaved(int x){
    std::cout << x << " leaved \n";

    cardOut();
}




/* SideBar */

void Field::setRightBox (QWidget * w, QWidget * b){

    currentSide -> setVisible(false);
    currentButt -> setProperty("down", false);
    w -> setVisible(true);
    b -> setProperty("down", true);

    currentButt -> style() -> unpolish(currentButt);
    currentButt -> style() -> polish(currentButt);

    b -> style() -> unpolish(b);
    b -> style() -> polish(b);


    currentButt = b;
    currentSide = w;
}


void Field::setStats (){
    
    setRightBox(stats, statsButt);
}

void Field::setChat (){

    setRightBox(chat, chatButt);
}


void Field::setProgress (){
    stats -> incProgress();
}

void Field::sendMsg (QString str){

    if(str.startsWith("þ")){
        transmettre(str);
        QStringRef * decoupe = new QStringRef(&str,1,str.length()-1);
        chat->addText(decoupe->toString(), 2);
    } else {
        chat -> addText(str, 1);
    }
}

void Field::setTour (int x){
    stats -> setTour(x);
}

void Field::setPhase (int x){
    stats -> setPhase(x);
}


/* Card placements */

void Field::setCarte(QString img, int x){
    fieldStack -> at(x) -> setPic(img);
    std::cout << "WOW : " << img.toStdString() << " at " << x << std::endl;
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




/* Change Life */








void Field::test (){

    fieldStack -> at(79) -> setPic("img/cards/001/LOB-EN125-GaiatheDragonChampion.jpg");
    fieldStack -> at(3) -> posePic();
    fieldStack -> at(10) -> maskPic();

    setPhase(1);
    setTour(1);

    QString lfe = "4000";
    lifeAdv -> setText(lfe);
    lifeSlf -> setText(lfe);

    progressAdv -> setValue(lfe.toInt());
    progressSlf -> setValue(lfe.toInt());
}
