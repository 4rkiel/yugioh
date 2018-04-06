#include "../inc/field.h"

/******************************************************************************

Widget implémentant le plateau de jeu

Initialisé lors du lancement d'une partie

******************************************************************************/

Field::Field () {

    lockPreview = false;

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
        
            QSettings settings;
            baseLife = settings.value("lifePoints", "8000").toString();
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
            icoLife -> setText("Tour\n0");
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

    popup = new Popup;

    connect(popup, SIGNAL(introStack()), this, SLOT(emitIntroStack()));
    connect(popup, SIGNAL(sendAtk()), this, SLOT(emitAtk()));
    connect(popup, SIGNAL(sendDef()), this, SLOT(emitDef()));

    connect(menuButt, SIGNAL(clicked()), popup, SLOT(openQuit()));



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
    connect(shortcut, SIGNAL(activated()), popup, SLOT(openQuit()));

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

        } else {

            lockPreview = true;
        }
    }

}


void Field::cardHover (
		QString title, 
		int attr,
		int level,
		QString pic,
		int type,
		QString desc,
		int atk,
		int def
	){

    fullCard -> setTitle(title);
	fullCard -> setAttr(attr);
	fullCard -> setLevel(level);
    fullCard -> setPic(pic);
	fullCard -> setType(type);
    fullCard -> setDesc(desc);
    fullCard -> setStat(QString::number(atk), QString::number(def));

    if (!lockPreview){
        chat -> setVisible(false);
        fullCard -> setVisible(true);
    }
}


void Field::cardOut (){

    if (!lockPreview){
        fullCard -> setVisible(false);
        chat -> setVisible(true);
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

	emit askPreview(x);
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
    progressRight -> setValue((progressRight -> value() + 1)%maxPhase);
    progressLeft -> setValue((progressLeft -> value() + 1)%maxPhase);

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
//    stats -> setTour(x);
}

void Field::setPhase (int x){
//    stats -> setPhase(x);
}



/* Card placements */

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

void Field::switchCarte(int x){
	fieldStack -> at(x) -> turn();
}


