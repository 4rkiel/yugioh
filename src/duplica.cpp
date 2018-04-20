#include "../inc/duplica.h"

/******************************************************************************

	Widget permettant d'afficher le contenu complet d'une carte,

	en lien avec le survol de l'image sur le plateau de jeu

******************************************************************************/

Duplica::Duplica(){

    gffect = new QGraphicsDropShadowEffect;
    gffect -> setBlurRadius(5);
    gffect -> setYOffset(5);
    gffect -> setXOffset(0);
    gffect -> setColor(QColor(0,0,0,150));

    setGraphicsEffect(gffect);

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QSizePolicy sp = sizePolicy();
    sp.setRetainSizeWhenHidden(true);
    setSizePolicy(sp);

    QFont font = this -> font();
    font.setPointSize(10);

           
    layout = new QGridLayout;
    layout -> setContentsMargins(10,10,10,10);

        // Titre Box
    
        titleBox = new QWidget;
        titleBox -> setObjectName("replicaTitleBox");
        titleBox -> setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

        titleLayout = new QHBoxLayout;
        titleLayout -> setContentsMargins(10,5,10,5);

            // Titre
           
            title = new QLabel;
            title -> setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
            title -> setWordWrap(true);
			title -> setFont(font);
            title -> setObjectName("replicaTitle");

            titleLayout -> addWidget(title);
        
            attr = new QLabel;
            attr -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
            attr -> setObjectName("replicaAttr");
            attr -> setMinimumHeight(30);
            attr -> setMaximumHeight(30);
            attr -> setMinimumWidth(30);
            attr -> setMaximumWidth(30);
                  
            titleLayout -> addWidget(attr);




        effect = new QGraphicsDropShadowEffect;
        effect -> setBlurRadius(5);
        effect -> setYOffset(2);
        effect -> setXOffset(2);
        effect -> setColor(QColor(0,0,0,50));

        titleBox -> setGraphicsEffect(effect);


        titleBox -> setLayout(titleLayout);
        
        layout-> addWidget(titleBox, 0, 0, 1, 1);

        
        // Sous titre

        typeBox = new QWidget;
        typeBox -> setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        typeLayout = new QHBoxLayout;
        typeLayout -> setMargin(0);
        typeLayout -> setSpacing(0);
        typeLayout -> setAlignment(Qt::AlignRight);


        typeBox -> setLayout(typeLayout);
        layout -> addWidget(typeBox, 1, 0, 1, 1);


        
        // Image

        QWidget * picBox = new QWidget;
        picBox -> setStyleSheet("background: rgba(100,100,100,100)");
        picBox -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        QGridLayout * picLayout = new QGridLayout;
        picLayout -> setMargin(0);
        picLayout -> setSpacing(0);

        pic = new QLabel;
        pic -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        pic -> setObjectName("replicaPic");
        pic -> setMinimumHeight(100);
        pic -> setMinimumWidth(100);
        
//        pic -> setMinimumHeight(pic -> width());
//        pic -> setMaximumHeight(pic -> width());
        
        picLayout -> addWidget(pic);
        picBox -> setLayout(picLayout);
        layout -> addWidget(picBox, 2, 0, 5, 1);
        
        

        // Description Box
        
        descBox = new QScrollArea;
        descBox -> setFrameShape(QFrame::NoFrame);
        descBox -> setWidgetResizable(true);
        descBox -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        descBox -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        descBox -> setFocusPolicy(Qt::NoFocus);
        
        descBox -> setObjectName("replicaDesc");
        descLayout = new QVBoxLayout;
        descLayout -> setContentsMargins(10, 10, 10, 10);
        
 
            // Type

            type = new QLabel;
            type -> setFont(font);
            type -> setAlignment(Qt::AlignLeft);
            type -> setStyleSheet(
                "border: none;"
                "background: transparent;"
            );
            
            descLayout-> addWidget(type);
                   

            // Description 

            desc = new QLabel;
            desc -> setContentsMargins(0, 0, 0, 10);
            desc -> setStyleSheet(
                "border: none;"
                "background: transparent;"
            );
            desc -> setWordWrap(true);
            desc -> setFont(font);
            
            descLayout -> addWidget(desc);

            descLayout -> addStretch(1);

            // Atk/Def

            atk = new QLabel;
            atk -> setFont(font);
            atk -> setAlignment(Qt::AlignRight);
            atk -> setStyleSheet(
                "border: none;"
                "border-top: 1px solid #795548;"
                "background: transparent;"
            );
           
            descLayout -> addWidget(atk);

        descBox -> setLayout(descLayout);

        layout -> addWidget(descBox,8,0,2,1);


    setLayout(layout);
}


Duplica::~Duplica(){

    delete gffect;

        delete atk;
        delete desc;
        delete type;
    delete descLayout;
    delete descBox;
    
    delete pic;

    while (auto item = typeLayout->takeAt(0)) {
      delete item->widget();
    }

    delete typeLayout;
    delete typeBox;

    delete title;
    delete attr;
    delete effect;
    delete titleLayout;
    delete titleBox;
    
    delete layout;
}


void Duplica::mousePressEvent (QMouseEvent *){
    
    emit clicked();
}


void Duplica::reInit(Carte * card){

    setTitle(card -> nom);
    setPic(card -> image);
    setDesc(card -> description);

    if (card -> genre == 0){
 
        QString attrtxt;
        switch (card -> attribut){
            case 0:
                attrtxt = "LUMIERE";
            break;
            case 1:
                attrtxt = "TENEBRE";
            break;
            case 2:
                attrtxt = "TERRE";
            break;
            case 3:
                attrtxt = "EAU";
            break;
            case 4:
                attrtxt = "FEU";
            break;
            case 5:
                attrtxt = "VENT";
            break;
            case 6:
                attrtxt = "DIVIN";
            break;
        }

        setAttr(attrtxt);

        setLevel(card -> niveau);

        setType(card -> type, card -> sous_type);

        setStat(QString::number(card -> atk), QString::number(card -> def));

        setColor(card -> sous_type);


    } else if (card -> genre == 1){

       setAttr("SPELL"); 

       setSpellType(card -> sous_type);
        
       hideType();

       hideStat();

       setSpellColor();


    } else {

        setAttr("TRAP");

        setTrapType(card -> sous_type);

        hideType();

        hideStat();

        setTrapColor();
    }

}


void Duplica::setTitle (QString str){
    
    title -> setText(str);
}


void Duplica::setAttr (QString str){
   
    attr -> setStyleSheet(
        "border-image:url(\"img/img_attr/"+str+".png\");"
    );
}


void Duplica::setSpellColor (){

    titleBox -> setStyleSheet( "#replicaTitleBox {"
        "background: #00897B;"
        "border-left: 3px solid #80CBC4;"
        "border-top: 3px solid #80CBC4;"
    "}");

    descBox -> setStyleSheet(
        "border: 3px solid #004D40;"
        "background: #80CBC4;"
    );

    setStyleSheet("background: #00897B");
}


void Duplica::setTrapColor (){

    titleBox -> setStyleSheet( "#replicaTitleBox {"
        "background: #FDD835;"
        "border-left: 3px solid #ffff88;"
        "border-top: 3px solid #ffff88;"
    "}");

    descBox -> setStyleSheet(
        "border: 3px solid #795548;"
        "background: #FFF59D;"
    );

    setStyleSheet("background: #FDD835");

}


void Duplica::setColor (int x){
    // Monster

	switch (x){

        case 0: // Effect
        case 3: // Toon

            titleBox -> setStyleSheet( "#replicaTitleBox {"
                "background: #8D6E63;"
                "border-left: 3px solid #A1887F;"
                "border-top: 3px solid #A1887F;"
            "}");
        
            descBox -> setStyleSheet(
                "border: 3px solid #795548;"
                "background: #BCAAA4;"
            );

            setStyleSheet("background: #8D6E63");


        break;
        case 1: // Normal

            titleBox -> setStyleSheet( "#replicaTitleBox {"
                "background: #FDD835;"
                "border-left: 3px solid #ffff88;"
                "border-top: 3px solid #ffff88;"
            "}");
        
            descBox -> setStyleSheet(
                "border: 3px solid #795548;"
                "background: #FFF59D;"
            );

            setStyleSheet("background: #FDD835");
       

        break;
        case 2: // Fusion

            titleBox -> setStyleSheet( "#replicaTitleBox {"
                "background: #B39DDB;"
                "border-left: 3px solid #EDE7F6;"
                "border-top: 3px solid #EDE7F6;"
            "}");
        
            descBox -> setStyleSheet(
                "border: 3px solid #9575CD;"
                "background: #D1C4E9;"
            );

            setStyleSheet("background: #B39DDB");


        break;
        case 4: // Rituel

            titleBox -> setStyleSheet( "#replicaTitleBox {"
                "background: #64B5F6;"
                "border-left: 3px solid #BBDEFB;"
                "border-top: 3px solid #BBDEFB;"
            "}");
        
            descBox -> setStyleSheet(
                "border: 3px solid #2196F3;"
                "background: #90CAF9;"
            );

            setStyleSheet("background: #64B5F6");


        break;
    }
}


void Duplica::setLevel (int x){

    while (auto item = typeLayout->takeAt(0)) {
        delete item->widget();
    }

    for (int k=0; k<x; k++){
    
        QLabel * typeLabel = new QLabel;
     
        typeLabel -> setStyleSheet(
            "border-image:url(\"img/img_attr/Level.png\");"
        );

        typeLabel -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        typeLabel -> setObjectName("replicaAttr");
        typeLabel -> setMinimumHeight(20);
        typeLabel -> setMaximumHeight(20);
        typeLabel -> setMinimumWidth(20);
        typeLabel -> setMaximumWidth(20);
        typeLayout -> addWidget(typeLabel);
    }
}


void Duplica::setSpellType(int attr){

    while (auto item = typeLayout->takeAt(0)) {
        delete item->widget();
    }

    QLabel * genreLabel = new QLabel;
 
    QFont font = this -> font();
    font.setPointSize(10);
    
    genreLabel -> setText(tr("Carte Magie"));
    genreLabel -> setFont(font);

    typeLayout -> addWidget(genreLabel);


    if (attr > 0){
    
        QString attrtxt;

        switch (attr){
            
            case 1:
                attrtxt = "";
            break;
            case 2:
                attrtxt = "";
            break;
            case 3:
                attrtxt = "";
            break;
            case 4:
                attrtxt = "";
            break;
            case 5:
                attrtxt = "";
            break;
        }


        QLabel * typeLabel = new QLabel;

        typeLabel -> setStyleSheet(
            "border-image:url(\"img/img_attr/"+ attrtxt +".png\");"
        );

        typeLabel -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        typeLabel -> setObjectName("replicaAttr");
        typeLabel -> setMinimumHeight(20);
        typeLabel -> setMaximumHeight(20);
        typeLabel -> setMinimumWidth(20);
        typeLabel -> setMaximumWidth(20);
        
        typeLayout -> addWidget(typeLabel);
    }
}


void Duplica::setTrapType(int attr){

    while (auto item = typeLayout->takeAt(0)) {
        delete item->widget();
    }

    QLabel * genreLabel = new QLabel;

    QFont font = this -> font();
    font.setPointSize(10);
    
    genreLabel -> setText(tr("Carte Piège"));
    genreLabel -> setFont(font);

    typeLayout -> addWidget(genreLabel);


    if (attr > 0){
    
        QString attrtxt;

        switch (attr){
            
            case 1:
                attrtxt = "";
            break;
            case 2:
                attrtxt = "";
            break;
        }


        QLabel * typeLabel = new QLabel;

        typeLabel -> setStyleSheet(
            "border-image:url(\"img/img_attr/"+ attrtxt +".png\");"
        );

        typeLabel -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        typeLabel -> setObjectName("replicaAttr");
        typeLabel -> setMinimumHeight(20);
        typeLabel -> setMaximumHeight(20);
        typeLabel -> setMinimumWidth(20);
        typeLabel -> setMaximumWidth(20);
        
        typeLayout -> addWidget(typeLabel);
    }
}


void Duplica::setPic (QString str){
    
    pic -> setStyleSheet(
        "border-image:url("+ str +");"
    );
}


void Duplica::setType (int x, int y){

	QString typetxt;

	switch (x){
		case 0:
			typetxt = "Aqua";
		break;
		case 1:
			typetxt = "Bête";
		break;
		case 2:
			typetxt = "Bête-Ailée";
		break;
		case 3:
			typetxt = "Bête-Divine";
		break;
		case 4:
			typetxt = "Bête-Guerrier";
		break;
		case 5:
			typetxt = "Démon";
		break;
		case 6:
			typetxt = "Dinosaure";
		break;
		case 7:
			typetxt = "Dragon";
		break;
		case 8:
			typetxt = "Elfe";
		break;
		case 9:
			typetxt = "Guerrier";
		break;
		case 10:
			typetxt = "Insecte";
		break;
		case 11:
			typetxt = "Machine";
		break;
		case 12:
			typetxt = "Magicien";
		break;
		case 13:
			typetxt = "Plante";
		break;
		case 14:
			typetxt = "Poisson";
		break;
		case 15:
			typetxt = "Pyro";
		break;
		case 16:
			typetxt = "Rocher";
		break;
		case 17:
			typetxt = "Reptile";
		break;
		case 18:
			typetxt = "Serpent de mer";
		break;
		case 19:
			typetxt = "Tonnerre";
		break;
		case 20:
			typetxt = "Wyrm";
		break;
		case 21:
			typetxt = "Zombie";
		break;

}

    switch(y){

        case 0:
            typetxt = typetxt + " / Effet";
        break;
        case 1:
        break;
        case 2:
            typetxt = typetxt + " / Fusion";
        break;
        case 3:
            typetxt = typetxt + " / Toon";
        break;
        case 4:
            typetxt = typetxt + " / Rituel";
        break;
    }
    

    type -> setText("[ " + typetxt + " ]");
	type -> setVisible(true);
}


void Duplica::hideType (){
	type -> setVisible(false);
}


void Duplica::setDesc (QString str){
    desc -> setText(str);
}


void Duplica::setStat (QString strAtk, QString strDef){
    
    atk -> setText("ATK " + strAtk + "/ DEF " + strDef);
	atk -> setVisible(true);
}


void Duplica::hideStat (){
	atk -> setVisible(false);
}

