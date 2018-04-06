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

    setStyleSheet("background: #FDD835");

           
    layout = new QGridLayout;
    layout -> setContentsMargins(10,10,10,10);

        // Titre Box
           
            // Titre
            
            title = new QLabel;
            title -> setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
            title -> setWordWrap(true);
			title -> setFont(font);
            title -> setContentsMargins(10, 10, 10, 10);
            title -> setObjectName("replicaTitle");


            // Titre Picture


        effect = new QGraphicsDropShadowEffect;
        effect -> setBlurRadius(5);
        effect -> setYOffset(2);
        effect -> setXOffset(2);
        effect -> setColor(QColor(0,0,0,50));

        title -> setGraphicsEffect(effect);

        layout-> addWidget(title, 0, 0, 1, 1);

        
        // Sous titre

        
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
        layout -> addWidget(picBox, 1, 0, 5, 1);
        
        

        // Description Box
        
        descBox = new QScrollArea;
        descBox -> setFrameShape(QFrame::NoFrame);
        descBox -> setWidgetResizable(true);
        descBox -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        descBox -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        descBox -> setFocusPolicy(Qt::NoFocus);
        
        descBox -> setObjectName("replicaDesc");
        descBox -> setStyleSheet(
                "border: 3px solid #795548;"
                "background: #FFF59D;"
                );
        descLayout = new QVBoxLayout;
        descLayout -> setContentsMargins(10, 10, 10, 10);
        
        

            // Description 

            desc = new QLabel;
            desc -> setContentsMargins(0, 0, 0, 10);
            desc -> setStyleSheet(
                "border: none;"
                "border-bottom: 1px solid #795548;"
                "background: transparent;"
            );
            desc -> setWordWrap(true);
            desc -> setFont(font);
            
            descLayout-> addWidget(desc);


            // Atk/Def

            atk = new QLabel;
            atk -> setFont(font);
            atk -> setAlignment(Qt::AlignRight);
            atk -> setStyleSheet(
                "border: none;"
                "background: transparent;"
            );
            
            descLayout-> addWidget(atk);

        descBox -> setLayout(descLayout);

        layout -> addWidget(descBox,7,0,2,1);


    setLayout(layout);
}


Duplica::~Duplica(){

    delete gffect;

        delete atk;
        delete desc;
    delete descLayout;
    delete descBox;
    
    delete pic;

    delete effect;
    delete title;
    delete layout;
}


void Duplica::mousePressEvent (QMouseEvent *){
    
    emit clicked();
}


void Duplica::setTitle (QString str){
    
    title -> setText(str);
}

void Duplica::setAttr (int x){

}

void Duplica::setLevel (int x){

}

void Duplica::setPic (QString str){
    
    pic -> setStyleSheet(
        "border-image:url("+ str +");"
    );
}


void Duplica::setType (int x){

}

void Duplica::setDesc (QString str){
    
    desc -> setText(str);
}


void Duplica::setStat (QString strAtk, QString strDef){
    
    atk -> setText("ATK " + strAtk + "/ DEF " + strDef);
}


//void Duplica::resizeEvent (QResizeEvent*){
 
//        pic -> setMinimumHeight(pic -> width());
//        pic -> setMaximumHeight(pic -> width());
//}
