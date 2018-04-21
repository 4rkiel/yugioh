#include "../inc/field.h"

/******************************************************************************

Widget implémentant le plateau de jeu

Initialisé lors du lancement d'une partie

******************************************************************************/

Field::Field () {

    readLangage();
    miniPopSave = false;
    popSave = false;

	lockTick = false;

    lockPreview = true;
	previewed = -1;

    retained = -1;

    maxPhase = 20 * 10;

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

            lifeBox = new QWidget;
            lifeBox -> setObjectName("lifeBox");
            lifeBox -> setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            lifeLayout = new QGridLayout;
            lifeLayout -> setSpacing(0);
            lifeLayout -> setMargin(0);
            lifeLayout -> setContentsMargins(0,0,0,0);
        
            baseLife = "8000";
            int bl = baseLife.toInt();

            lifeSlf = new QLabel;
            lifeSlf -> setObjectName("lifeLabel");
            lifeSlf -> setText(baseLife);
            lifeSlf -> setAlignment(Qt::AlignCenter); 
            lifeLayout -> addWidget(lifeSlf, 0,0,1,1);
            
            icoSlf = new QLabel;
            icoSlf -> setText(tr("Vous"));
            icoSlf -> setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
            lifeLayout -> addWidget(icoSlf, 0,1,1,1);

            progressSlf = new QProgressBar;
            progressSlf -> setRange(0,bl);
            progressSlf -> setInvertedAppearance(true);
            progressSlf -> setOrientation(Qt::Horizontal);
            progressSlf -> setTextVisible(false);
            progressSlf -> setValue(bl);
            lifeLayout -> addWidget(progressSlf, 1,0,1,2);
           
            //
            
            icoLife = new QLabel;
            icoLife -> setObjectName("phaseBox");
            icoLife -> setText(tr("Tour\n0"));
            icoLife -> setAlignment(Qt::AlignCenter);
            lifeLayout -> addWidget(icoLife, 0,2,1,2);

            
            progressLeft = new QProgressBar;
            progressLeft -> setObjectName("phaseLeft");
            progressLeft -> setRange(0,maxPhase);
            progressLeft -> setInvertedAppearance(true);
            progressLeft -> setOrientation(Qt::Horizontal);
            progressLeft -> setTextVisible(false);
            progressLeft -> setValue(0);
            progressLeft -> setMaximumWidth(50);
            lifeLayout -> addWidget(progressLeft, 1,2,1,1);


            progressRight = new QProgressBar;
            progressRight -> setObjectName("phaseRight");
            progressRight -> setRange(0,maxPhase);
            progressRight -> setOrientation(Qt::Horizontal);
            progressRight -> setTextVisible(false);
            progressRight -> setValue(0);
            progressRight -> setMaximumWidth(50);
            lifeLayout -> addWidget(progressRight, 1,3,1,1);

            //
            
            progressAdv = new QProgressBar;
            progressAdv -> setRange(0,bl);
            progressAdv -> setOrientation(Qt::Horizontal);
            progressAdv -> setTextVisible(false);
            progressAdv -> setValue(bl);
            lifeLayout -> addWidget(progressAdv, 1,4,1,2);


            icoAdv = new QLabel;
            icoAdv -> setText(tr("Adversaire"));
            icoAdv -> setAlignment(Qt::AlignVCenter|Qt::AlignRight);
            lifeLayout -> addWidget(icoAdv, 0,4,1,1);

            lifeAdv = new QLabel;
            lifeAdv -> setObjectName("lifeLabel");
            lifeAdv -> setText(baseLife);
            lifeAdv -> setAlignment(Qt::AlignCenter);
            lifeLayout -> addWidget(lifeAdv, 0,5,1,1);

            lifeLayout -> setColumnStretch(0,5);
            lifeLayout -> setColumnStretch(1,20);
            lifeLayout -> setColumnStretch(2,1);
            lifeLayout -> setColumnStretch(3,1);
            lifeLayout -> setColumnStretch(4,20);
            lifeLayout -> setColumnStretch(5,5);


            lifeBox -> setLayout(lifeLayout);
            infoLayout -> addWidget(lifeBox);

            


            // Quit Button
            
            menuButt = new FlatButt("\uf00d", "");
            menuButt -> setToolTip(tr("Quitter la partie"));
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

    popup = new Popup();

    connect(popup, SIGNAL(introStack()), this, SLOT(emitIntroStack()));

    connect(popup, SIGNAL(focusField()), this, SLOT(getsFocus()));
    connect(popup, SIGNAL(moiFocus()), this, SLOT(abandonFocus()));

    connect(menuButt, SIGNAL(clicked()), this, SLOT(openQuit()));



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
                advHand -> setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
                advHand -> setMinimumHeight(10);

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

                advLayout -> setRowStretch(0,1);
                advLayout -> setRowStretch(1,2);
                advLayout -> setRowStretch(2,2);

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


                slfScroll = new QScrollArea;
                slfScroll -> setFrameShape(QFrame::NoFrame);
                slfScroll -> setWidgetResizable(true);
                slfScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                slfScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
                slfScroll -> setFocusPolicy(Qt::NoFocus);
                slfScroll -> setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
                slfScroll -> setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
                slfScroll -> setMinimumHeight(10);


                slfHand = new QWidget;
                slfHand -> setObjectName("slfHand");
                slfHand -> setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
                
                slfHandLayout = new QHBoxLayout;
                slfHandLayout -> setMargin(0);
                slfHandLayout -> setSpacing(0);
                slfHandLayout -> setContentsMargins(0,4,0,0);
      
                    for (int k=14; k<=20; k++){
                        fieldStack -> at(k) = new SlotCard(k);
                        slfHandLayout -> addWidget(fieldStack -> at(k));
                    }
                    
                slfHand -> setLayout(slfHandLayout);
                slfScroll -> setWidget(slfHand);
                slfLayout -> addWidget(slfScroll, 2,0,1,1);

                slfLayout -> setRowStretch(0,2);
                slfLayout -> setRowStretch(1,2);
                slfLayout -> setRowStretch(2,3);
            
            slfBox -> setLayout(slfLayout);
            arenaLayout -> addWidget(slfBox, 1,0,1,1);
            arenaLayout -> setRowStretch(0,5);
            arenaLayout -> setRowStretch(1,7);


            
        minipop = new MiniPopup;
        minipop -> setVisible(false);
        arenaLayout -> addWidget(minipop, 0,0,2,3);
        


        connect(minipop, SIGNAL(sendAtk()), this, SLOT(emitAtk()));
        connect(minipop, SIGNAL(sendDef()), this, SLOT(emitDef()));
        
        connect(minipop, SIGNAL(sendVisi()), this, SLOT(emitVisi()));
        connect(minipop, SIGNAL(sendHide()), this, SLOT(emitHide()));
        connect(minipop, SIGNAL(focusField()), this, SLOT(getsFocus()));
        connect(minipop, SIGNAL(moiFocus()), this, SLOT(abandonFocus()));

        connect(minipop, SIGNAL(chosenOne(std::vector<int>)),
                    this, SLOT(emitChosen(std::vector<int>)));





        arenaBox -> setLayout(arenaLayout);
        






        // Right Bar ..........................................................

        rightBarBox = new QWidget;
        rightBarBox -> setObjectName("rightBarBox");
        
        rightBarLayout = new QGridLayout;
        rightBarLayout -> setSpacing(0);
        rightBarLayout -> setMargin(0);
        rightBarLayout -> setAlignment(Qt::AlignCenter);
        rightBarLayout -> setContentsMargins(10, 10, 10, 10);

            
            // Sidebar
            side = new QWidget;
            side -> setObjectName("sidebar");
            side -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
            sidebar = new QGridLayout;   
            sidebar -> setSpacing(0);
            sidebar -> setMargin(0);
            sidebar -> setContentsMargins(0,0,0,0);

            
                fullCard = new Duplica;
                fullCard -> setVisible(false);
                connect(fullCard, SIGNAL(clicked()), this, SLOT(previewClicked()));
                sidebar -> addWidget(fullCard, 0, 0, 10, 1);

                chat = new Chat;
                sidebar -> addWidget(chat, 0, 0, 10, 1);

                connect(chat, SIGNAL(msgSent(QString)), this, SLOT(sendMsg(QString)));
                connect(chat, SIGNAL(rcvQuit()), this, SLOT(openQuit()));
                connect(chat, SIGNAL(swField()), this, SLOT(switchField()));

            side -> setLayout(sidebar);
            rightBarLayout -> addWidget(side, 0, 0, 1, 1);


           


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
    shortcut->setContext(Qt::WidgetShortcut);
    connect(shortcut, SIGNAL(activated()), this, SLOT(openQuit()));

    setLayout(layout);

}


Field::~Field (){

            delete chat;

            delete fullCard;
            
            delete sidebar;
            delete side;

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
                delete slfScroll;
       
            delete slfLayout;
            delete slfBox;

            delete minipop;

        delete arenaLayout;
        delete arenaBox;

        delete sceneLayout;
    delete sceneBox;

    delete popup;

    delete overLayout;
    
    delete overField;
    delete shortcut;

    delete menuButt;
    delete icoAdv;
    delete lifeAdv;
    delete progressAdv;
    delete icoLife;
    delete progressRight;
    delete progressLeft;
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
                 this, SLOT(cardLeaved())
             );

        }
    }

     SlotCard* temp;
     temp=fieldStack -> at(14);
     temp->setFocus();
//    resizeVictor();

     for (int k=0; k<150; k++){
         if (fieldStack -> at(k) != nullptr){
             connect(fieldStack->at(k), SIGNAL(rcvQuit()), 
                     this, SLOT(openQuit()),Qt::UniqueConnection);
             connect(fieldStack->at(k), SIGNAL(mvUp()), 
                     this, SLOT(moveUp()),Qt::UniqueConnection);
             connect(fieldStack->at(k), SIGNAL(mvDown()), 
                     this, SLOT(moveDown()),Qt::UniqueConnection);
             connect(fieldStack->at(k), SIGNAL(mvLeft()), 
                     this, SLOT(moveLeft()),Qt::UniqueConnection);
             connect(fieldStack->at(k), SIGNAL(mvRight()), 
                     this, SLOT(moveRight()),Qt::UniqueConnection);
             connect(fieldStack->at(k), SIGNAL(swChat()), 
                     this, SLOT(switchChat()),Qt::UniqueConnection);
         }
     }


}



/* Popup functions */

void Field::emitIntroStack (){
    emit introStack();
}

void Field::openChoosePosi (){
    std::cout << "OPENCHOOSEPOSI\n";
    minipop -> openPosi();
    miniSave();
}

void Field::emitAtk (){
    emit sendAtk();
}

void Field::emitDef (){
    emit sendDef();
}


void Field::openChooseMagi (){
    minipop -> openMagi();
    miniSave();
}

void Field::emitHide (){
    emit sendHide();
}

void Field::emitVisi (){
    emit sendVisi();
}

void Field::openSee (std::vector <Carte *> * str){
    minipop -> openSee(str);
    miniSave();
}

void Field::openChoose (int x, std::vector <Carte *> * str){
    
    std::cout << "yoooooooooooo\n";
    
    minipop -> openChoose(x, str);
    miniSave();
}

void Field::openChooseLocked (int x, std::vector <Carte *> * str){
    minipop -> openChooseLocked(x, str);
    miniSave();
}

void Field::openWin (){
    
    if (lockTick){
        
        popup -> openWin();
	    relockTick();
        maxiSave();
    }
}


void Field::openLost (){
    
    if (lockTick){
    
        popup -> openLost();
	    relockTick();
        maxiSave();
    }
}


void Field::openQuit (){

    if (lockTick){
        
        popup -> openQuit();
    
    } else {
        
        popup -> openEnd();
    }

    maxiSave();
}


void Field::miniSave (){
    
    miniPopSave = true;
}


void Field::maxiSave (){

    popSave = true;
}


void Field::miniReopen(){
    
    if (miniPopSave && popSave){
        
        minipop -> setVisible(true);
        popSave = false;

    } else if (miniPopSave){
        
        miniPopSave = false;

    } else if (popSave){
    
        minipop -> setVisible(false);
        popSave = false;
    }
}

void Field::emitChosen (std::vector <int> sam){
    emit chosenOne(sam);
}



/* Focus */
void Field::getsFocus(){

    miniReopen();

    SlotCard* temp;
    for (int k=0; k<150; k++){
        if (fieldStack -> at(k) != nullptr){
            temp= fieldStack -> at(k);
            temp->setFocusPolicy(Qt::StrongFocus);
        }
    }
    chat->input->setFocusPolicy(Qt::StrongFocus);
    menuButt->setFocusPolicy(Qt::StrongFocus);
    temp=fieldStack -> at(14);
    temp->setFocus();
}

void Field::abandonFocus(){
    SlotCard* temp;
    for (int k=0; k<150; k++){
        if (fieldStack -> at(k) != nullptr){
            temp= fieldStack -> at(k);
            temp->setFocusPolicy(Qt::NoFocus);
        }
    }
    chat->input->setFocusPolicy(Qt::NoFocus);
    menuButt->setFocusPolicy(Qt::NoFocus);
}



/* Lock Preview */

void Field::previewClicked(){

    if (!lockPreview){

        fieldStack -> at(previewed) -> setProperty("down", false);
        fieldStack -> at(previewed) -> style() -> unpolish(fieldStack -> at(previewed));
        fieldStack -> at(previewed) -> style() -> polish(fieldStack -> at(previewed));
 
        lockPreview = true;
		previewed = -1;
        cardOut();
    }
}

void Field::cardRightClicked(int x){

    SlotCard * that = fieldStack -> at(x);
    
    if (
        (! that -> isDeck() ) &&
        (! that -> isFuse() ) &&
        (! that -> isGrave() )
    ){


        if (lockPreview && !(that -> isHand() && that -> isAdv() ) ){
            
            emit askPreview(x);            
           
            fieldStack -> at(x) -> setProperty("down", true);
            fieldStack -> at(x) -> style() -> unpolish(fieldStack -> at(x));
            fieldStack -> at(x) -> style() -> polish(fieldStack -> at(x));
            
            lockPreview = false;
			previewed = x;

        } else if (previewed != -1) {

            fieldStack -> at(previewed) -> setProperty("down", false);
            fieldStack -> at(previewed) -> style() -> unpolish(fieldStack -> at(previewed));
            fieldStack -> at(previewed) -> style() -> polish(fieldStack -> at(previewed));
 
            lockPreview = true;
			previewed = -1;
        }
    }
}


void Field::cardHover (Carte * card){

    fullCard -> reInit(card);
    chat -> setVisible(false);
    fullCard -> setVisible(true);
}


void Field::cardOut (){

    if (lockPreview){
        fullCard -> setVisible(false);
        chat -> setVisible(true);
    }
}



/* Field Actions */

void Field::cardDoubleClicked(int x){
    
    emit doubleClicked(x);
}

void Field::cardClicked(int x){

    SlotCard * that = fieldStack -> at(x);

    if (
		! that -> isAdv() && 
        ! that -> isHand() && 
        ! that -> isDeck() && 
        ! that -> isGrave() && 
        ! that -> isFuse() &&
		! that -> isField() &&
		! that -> isMagic()
	){

        retained = x;

    } else if (
	
		retained != -1 &&
		that -> isAdv() &&
        ! that -> isHand() && 
        ! that -> isDeck() &&
        ! that -> isGrave() &&
        ! that -> isFuse() &&
		! that -> isField() &&
		! that -> isMagic()
        
	){
   
        emit monstClick(retained, x);
        retained = -1;
        
    }
}

void Field::cardEntered(int x){
    
    if (lockPreview){
    	emit askPreview(x);
    }
}

void Field::cardLeaved(){

    cardOut();
}



/* SideBar */

void Field::sendMsg (QString str){

    if(str.startsWith("þ")){
        transmettre(str);
        QStringRef * decoupe = new QStringRef(&str,1,str.length()-1);
        chat->addText(decoupe->toString(), 2);
    } else {
        chat -> addText(str, 1);
    }
}

void Field::sendInfo (QString str){
    chat -> addText(str, 0);
}


/* Info */

void Field::setProgress (){

	if (lockTick){
	
		progressRight -> setValue((progressRight -> value() + 1)%maxPhase);
    	progressLeft -> setValue((progressLeft -> value() + 1)%maxPhase);
	
    	progressLeft -> repaint();
    	progressRight -> repaint();
	}
}


void Field::unlockTick(){
	lockTick = true;
}


void Field::relockTick (){

	lockTick = false;

    progressRight -> reset();
    progressLeft -> reset();

    progressLeft -> repaint();
    progressRight -> repaint();
}

void Field::resetProgress (){

    progressRight -> reset();
    progressLeft -> reset();

    progressLeft -> repaint();
    progressRight -> repaint();
}




void Field::setTour (int x){
	icoLife -> setText(tr("Tour") + "\n" + QString::number(x));
}



void Field::initLife(int x){
	
	progressSlf -> setRange(0,x);
	progressAdv -> setRange(0,x);
	progressSlf -> setValue(x);
	progressAdv -> setValue(x);
	
	lifeSlf -> setText(QString::number(x));
	lifeAdv -> setText(QString::number(x));
}


void Field::setLife(int x, bool me){

	std::cout << x << " Life \n";
	if (me){
		
		lifeSlf -> setText(QString::number(x));
		progressSlf -> setValue(x);

	} else {
		
		lifeAdv -> setText(QString::number(x));
		progressAdv -> setValue(x);
	}
}



/* Card placements */

void Field::setCarte(QString img, int x){

    dealWithHand(x);

    fieldStack -> at(x) -> setPic(img);
}

void Field::poseCarte(int x){
    
    fieldStack -> at(x) -> posePic();
}

void Field::maskCarte(int x){
    
    dealWithHand(x);
        
    fieldStack -> at(x) -> maskPic();
}

void Field::rmCarte(int x){
    fieldStack -> at(x) -> rmPic();
}

void Field::switchCarte(int x){
	fieldStack -> at(x) -> turn();
}


void Field::reveal(QString str, int x){
	fieldStack -> at(x) -> reveal(str);
}


void Field::dealWithHand(int k){

    if (fieldStack -> at(k) == nullptr){
        
        fieldStack -> at(k) = new SlotCard(k);
        
        if (k >= 14 && k < 75){
            slfHandLayout -> addWidget(fieldStack -> at(k));

            connect(
                fieldStack -> at(k), SIGNAL(leftClick(int)),
                this, SLOT(cardClicked(int))
            );

            connect(
                fieldStack -> at(k), SIGNAL(rightClick(int)),
                this, SLOT(cardRightClicked(int))
            );

            connect(
                fieldStack -> at(k), SIGNAL(doubleClick(int)),
                this, SLOT(cardDoubleClicked(int))
            );

            connect(
                fieldStack -> at(k), SIGNAL(entered(int)),
                this, SLOT(cardEntered(int))
            );

            connect(
                fieldStack -> at(k), SIGNAL(leaved(int)),
                this, SLOT(cardLeaved())
            );

            connect(
                fieldStack->at(k), SIGNAL(rcvQuit()), 
                this, SLOT(openQuit())
            );

//            resizeVictor();
            for (int k=0; k<150; k++){
                if (fieldStack -> at(k) != nullptr){
                    connect(fieldStack->at(k), SIGNAL(rcvQuit()), 
                            this, SLOT(openQuit()),Qt::UniqueConnection);
                    connect(fieldStack->at(k), SIGNAL(mvUp()), this, SLOT(moveUp()),Qt::UniqueConnection);
                    connect(fieldStack->at(k), SIGNAL(mvDown()), this, SLOT(moveDown()),Qt::UniqueConnection);
                    connect(fieldStack->at(k), SIGNAL(mvLeft()), this, SLOT(moveLeft()),Qt::UniqueConnection);
                    connect(fieldStack->at(k), SIGNAL(mvRight()), this, SLOT(moveRight()),Qt::UniqueConnection);
                    connect(fieldStack->at(k), SIGNAL(swChat()), this, SLOT(switchChat()),Qt::UniqueConnection);
                }
            }

        }
    }

}

void Field::moveUp(){
    if(QString(qApp->focusObject()->metaObject()->className())=="SlotCard"){
        for (int k=0; k<150; k++){
            if (fieldStack -> at(k) != nullptr){
                if(fieldStack->at(k)==static_cast<SlotCard*>(qApp->focusObject())){
                    if(k<=6)
                        fieldStack -> at(75+k) -> setFocus();
                    if(k>=7 && k<=13)
                        fieldStack -> at(k-7) -> setFocus();
                    if(k>=89 && k<=150){
                        if(fieldStack -> at(14+(k-89)) != nullptr)
                            fieldStack -> at(14+(k-89)) -> setFocus();
                        else
                            fieldStack -> at(20) ->setFocus();
                        slfScroll->horizontalScrollBar()->setValue(0);
                    }
                    if(k>=75 && k<=88)
                        fieldStack -> at(k+7) -> setFocus();
                    if(k>=14 && k<=20){
                        fieldStack -> at(k-7) -> setFocus();
                    }
                    if(k>=21&&k<=74){
                        fieldStack -> at(13) -> setFocus();
                    }

                    return;

                }
            }
        }
    }
}

void Field::moveDown(){
    if(QString(qApp->focusObject()->metaObject()->className())=="SlotCard"){
        for (int k=0; k<150; k++){
            if (fieldStack -> at(k) != nullptr){
                if(fieldStack->at(k)==static_cast<SlotCard*>(qApp->focusObject())){
                    if(k<=6)
                        fieldStack -> at(k+7) -> setFocus();
                    if(k>=7 && k<=13){
                        fieldStack -> at(k+7) -> setFocus();
                        slfScroll->horizontalScrollBar()->setValue(0);
                    }
                    if(k>=14 && k<=20){
                        fieldStack -> at(89+(k-14)) -> setFocus();
                    }
                    if(k>20){
                        fieldStack -> at(95) -> setFocus();
                    }
                    if(k>=75 && k<=81)
                        fieldStack -> at(k-75) -> setFocus();
                    if(k>=82 && k<=88)
                        fieldStack -> at(k-7) -> setFocus();
                    if(k>=89 && k<=95)
                        fieldStack -> at(k-7) -> setFocus();
                    if(k>=96)
                        fieldStack -> at(88) -> setFocus();
                    return;

                }
            }
        }
    }
}



int Field::plusDroite_Self(){
    for (int k=20; k<75; k++){
        if(fieldStack->at(k) == nullptr)
            return k-1;
    }
    return 1;
}

void Field::moveLeft(){
    if(langage!="ar_SA"){
        if(QString(qApp->focusObject()->metaObject()->className())=="SlotCard"){
            for (int k=0; k<150; k++){
                if (fieldStack -> at(k) != nullptr){
                    if(fieldStack->at(k)==static_cast<SlotCard*>(qApp->focusObject())){
                        if( (k>=1 && k<=6) || (k>=8 && k<=13) || (k>=83 && k<=88) || (k>=76 && k<=81) )
                            fieldStack -> at(k-1) -> setFocus();
                        if( (k==0) || (k==7) || (k==75) || (k==82)  )
                            fieldStack -> at(k+6) -> setFocus();
                        if(k==14){
                            fieldStack -> at(plusDroite_Self()) -> setFocus();
                            slfScroll->horizontalScrollBar()->setValue(slfScroll->horizontalScrollBar()->maximum());
                        }
                        if(k==89)
                            fieldStack -> at(95) -> setFocus();
                        if(k>=15 && k<75){
                            fieldStack -> at(k-1) -> setFocus();
                            slfScroll->horizontalScrollBar()->setValue(slfScroll->horizontalScrollBar()->value() - fieldStack -> at(14) ->width());
                        }
                        if(k>=90 && k<=150){
                            fieldStack -> at(k-1) -> setFocus();
                        }
                        return;

                    }
                }
            }
        }
    }
    else{
        if(QString(qApp->focusObject()->metaObject()->className())=="SlotCard"){
            for (int k=0; k<150; k++){
                if (fieldStack -> at(k) != nullptr){
                    if(fieldStack->at(k)==static_cast<SlotCard*>(qApp->focusObject())){
                        if( (k>=0 && k<=5) || (k>=7 && k<=12) || (k>=82 && k<=87) || (k>=75 && k<=80) )
                            fieldStack -> at(k+1) -> setFocus();
                        if( (k==6) || (k==13) || (k==81) || (k==88) || (k==95)  )
                            fieldStack -> at(k-6) -> setFocus();
                        if(k>=14 && k<=75){
                            if(fieldStack->at(k+1) != nullptr){
                                fieldStack -> at(k+1) ->setFocus();
                                slfScroll->horizontalScrollBar()->setValue(slfScroll->horizontalScrollBar()->value() + fieldStack -> at(14) ->width());
                            }
                            else{
                                fieldStack -> at(14) ->setFocus();
                                slfScroll->horizontalScrollBar()->setValue(0);
                            }

                        }
                        if(k>=89 && k<=94){
                            fieldStack -> at(k+1) -> setFocus();
                        }
                        return;

                    }
                }
            }
        }
    }
}

void Field::moveRight(){
    if(langage!="ar_SA"){
        if(QString(qApp->focusObject()->metaObject()->className())=="SlotCard"){
            for (int k=0; k<150; k++){
                if (fieldStack -> at(k) != nullptr){
                    if(fieldStack->at(k)==static_cast<SlotCard*>(qApp->focusObject())){
                        if( (k>=0 && k<=5) || (k>=7 && k<=12) || (k>=82 && k<=87) || (k>=75 && k<=80) )
                            fieldStack -> at(k+1) -> setFocus();
                        if( (k==6) || (k==13) || (k==81) || (k==88) || (k==95)  )
                            fieldStack -> at(k-6) -> setFocus();
                        if(k>=14 && k<=75){
                            if(fieldStack->at(k+1) != nullptr){
                                fieldStack -> at(k+1) ->setFocus();
                                slfScroll->horizontalScrollBar()->setValue(slfScroll->horizontalScrollBar()->value() + fieldStack -> at(14) ->width());
                            }
                            else{
                                fieldStack -> at(14) ->setFocus();
                                slfScroll->horizontalScrollBar()->setValue(0);
                            }

                        }
                        if(k>=89 && k<=94){
                            fieldStack -> at(k+1) -> setFocus();
                        }
                        return;

                    }
                }
            }
        }
    }
    else{
        if(QString(qApp->focusObject()->metaObject()->className())=="SlotCard"){
            for (int k=0; k<150; k++){
                if (fieldStack -> at(k) != nullptr){
                    if(fieldStack->at(k)==static_cast<SlotCard*>(qApp->focusObject())){
                        if( (k>=1 && k<=6) || (k>=8 && k<=13) || (k>=83 && k<=88) || (k>=76 && k<=81) )
                            fieldStack -> at(k-1) -> setFocus();
                        if( (k==0) || (k==7) || (k==75) || (k==82)  )
                            fieldStack -> at(k+6) -> setFocus();
                        if(k==14){
                            fieldStack -> at(plusDroite_Self()) -> setFocus();
                            slfScroll->horizontalScrollBar()->setValue(slfScroll->horizontalScrollBar()->maximum());
                        }
                        if(k==89)
                            fieldStack -> at(95) -> setFocus();
                        if(k>=15 && k<75){
                            fieldStack -> at(k-1) -> setFocus();
                            slfScroll->horizontalScrollBar()->setValue(slfScroll->horizontalScrollBar()->value() - fieldStack -> at(14) ->width());
                        }
                        if(k>=90 && k<=150){
                            fieldStack -> at(k-1) -> setFocus();
                        }
                        return;

                    }
                }
            }
        }
    }
}

void Field::switchChat(){
    chat->goFocus();
}

void Field::switchField(){
    fieldStack->at(14)->setFocus();
    slfScroll->horizontalScrollBar()->setValue(0);
}

void Field::readLangage(){
    QSettings settings;
    langage = settings.value("langage", QLocale::system().name()).toString();
}

/*
void Field::resizeEvent(QResizeEvent* event){
    
    QWidget::resizeEvent(event);

    resizeVictor();
}


void Field::resizeVictor(){

	int x = (fieldStack -> at(0) -> width());

	for(int k=14; k<75; k++){
		if ( fieldStack -> at(k) != nullptr){

			fieldStack -> at(k) -> setMinimumWidth(x);
			fieldStack -> at(k) -> resize(x, fieldStack -> at(k) -> height());

		}
	}

//        slfHand -> repaint(); 
//        slfHand -> update(); 
}

*/
