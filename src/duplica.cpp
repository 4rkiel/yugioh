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


    QFont font = this -> font();
    font.setPointSize(10);

    setStyleSheet("background: #FDD835");

           
    layout = new QGridLayout;
    layout -> setContentsMargins(10,10,10,10);

        // Titre Box
           
            // Titre
            
            title = new QLabel;
            title -> setText("Dragon Blanc aux Yeux Bleus");
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

        pic = new QLabel;
        pic -> setObjectName("replicaPic");
        pic -> setStyleSheet(
            "border-image:url("
                "img/cards/001/LOB-EN001-Blue-EyesWhiteDragon2ndart.jpg"
            ");"
        );
        
        pic -> setMinimumHeight(pic -> width());
        pic -> setMaximumHeight(pic -> width());
        
        layout -> addWidget(pic, 1, 0, 2, 1);
        
        

        // Description Box
        
        descBox = new QWidget;
        descBox -> setObjectName("replicaDesc");
        descBox -> setStyleSheet(
                "border: 3px solid #795548;"
                "background: #FFF59D;"
                );
        descLayout = new QVBoxLayout;
        descLayout -> setContentsMargins(10, 10, 10, 10);
        

            // Description 

            desc = new QLabel(
                "Ce dragon légendaire est un puissant "
                "moteur de destruction. Rares sont ceux qui ont survécus à cette "
                "surpuissante créature quasiment invincible pour en parler."
            );
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

            atk = new QLabel("ATK 3000 / DEF 2500");
            atk -> setFont(font);
            atk -> setAlignment(Qt::AlignRight);
            atk -> setStyleSheet(
                "border: none;"
                "background: transparent;"
            );
            
            descLayout-> addWidget(atk);

        descBox -> setLayout(descLayout);

        layout -> addWidget(descBox,3,0,2,1);


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


void Duplica::resizeEvent (QResizeEvent*){
 
        pic -> setMinimumHeight(pic -> width());
        pic -> setMaximumHeight(pic -> width());
}
