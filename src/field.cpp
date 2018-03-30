#include "../inc/field.h"

/******************************************************************************

	Widget implémentant le plateau de jeu

	Initialisé lors du lancement d'une partie

******************************************************************************/

Field::Field () {

    lockPreview = false;

    retained = -1;

    overLayout = new QGridLayout;
    overLayout -> setSpacing(0);
    overLayout -> setMargin(0);

  

    // Popup Menu

    popup = new Popup;
   
    connect(popup, SIGNAL(introStack()), this, SLOT(emitIntroStack()));
    connect(popup, SIGNAL(sendAtk()), this, SLOT(emitAtk()));
    connect(popup, SIGNAL(sendDef()), this, SLOT(emitDef()));



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
            connect(menuButt, SIGNAL(clicked()), popup, SLOT(openMenu()));
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


    overLayout -> addWidget(sceneBox, 0, 0);
    overLayout -> addWidget(popup, 0, 0);

    this -> setLayout(overLayout);


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

    delete popup;

    delete overLayout;
}


void Field::init(){
	fullCard -> setVisible(false);
    stats -> setVisible(true);
}


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

void Field::cardDoubleClicked(int x){
    std::cout << x << " Double clicked \n"; 
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
