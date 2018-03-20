#include "../inc/duplica.h"


Duplica::Duplica(){

    layout = new QVBoxLayout;
    layout->setSizeConstraint(QLayout::SetMinimumSize);

    QFont font = this -> font();
    font.setPointSize(10);


    setStyleSheet("background: yellow;");

        // Titre Box
           
            // Titre
            
            title = new QLabel;
            title -> setText("Dragon Blanc aux Yeux Bleus");
            //title -> setFont(font);
//            title->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

            //title -> setWordWrap(true);

            title -> setContentsMargins(10, 10, 10, 10);
            title -> setStyleSheet(
                "border-left: 3px solid #ffff88;"
                "border-top: 3px solid #ffff88"
            );


            // Titre Picture


        effect = new QGraphicsDropShadowEffect;
        effect -> setBlurRadius(5);
        effect -> setYOffset(2);
        effect -> setXOffset(2);
        effect -> setColor(QColor(0,0,0,50));

        title -> setGraphicsEffect(effect);

        layout-> addWidget(title);

        
        // Sous titre

        
        // Image

        pic = new QLabel("");
        pic -> resize(pic->width(), pic->width());
        pic -> setStyleSheet(
            "border-image: url("
                "img/cards/001/LOB-EN001-Blue-EyesWhiteDragon2ndart.jpg"
            ")"
        );

        layout -> addWidget(pic);
        
        
        
        // Description Box
            
            // Description 

            desc = new QLabel(
                "Ce dragon légendaire est un puissant "
                "moteur de destruction. Rares sont ceux qui ont survécus à cette "
                "surpuissante créature quasiment invincible pour en parler."
            );

            desc -> setWordWrap(true);
            desc -> setFont(font);

            layout-> addWidget(desc);


            // Atk/Def

            atk = new QLabel("ATK 3000 / DEF 2500");

            layout-> addWidget(atk);
            atk -> setFont(font);



    setLayout(layout);
}


Duplica::~Duplica(){

    delete atk;
    delete desc;
    delete pic;

    delete effect;
    delete title;
    delete layout;
}


void Duplica::resizeEvent (QResizeEvent*){

        pic -> resize(pic->width(), pic->width());
        pic -> adjustSize();
}
