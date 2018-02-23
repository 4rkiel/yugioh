#include <optab.h>

OptionTab::OptionTab (){

    setObjectName("optionBox");
    setVisible(false);


    effect = new QGraphicsDropShadowEffect(this);
    effect -> setBlurRadius(5);
    effect -> setXOffset(0);
    effect -> setYOffset(5);
    effect -> setColor(QColor(0,0,0,150));

    setGraphicsEffect(effect);

    
    optionLayout = new QVBoxLayout;
    optionLayout -> setSpacing(0);
    optionLayout -> setMargin(0);

        tabBox = new QWidget;
        tabBox -> setObjectName("optionTab");
        tabLayout = new QHBoxLayout;
        
            tabLayout -> addStretch();
            
            optionButt = new QPushButton;
            optionButt -> setText("Options");
            connect(optionButt, SIGNAL(clicked()), this, SLOT(setOption()));
            tabLayout -> addWidget(optionButt);
            
            accessButt = new QPushButton;
            accessButt -> setText("Accessibilité");
            connect(accessButt, SIGNAL(clicked()), this, SLOT(setAccess()));
            tabLayout -> addWidget(accessButt);

            aboutButt = new QPushButton;
            aboutButt -> setText("A Propos");
            connect(aboutButt, SIGNAL(clicked()), this, SLOT(setAbout()));
            tabLayout -> addWidget(aboutButt);
            
            tabLayout -> addStretch();

            exitButt = new QPushButton;
            exitButt -> setText("Fermer");
            connect(exitButt, SIGNAL(clicked()), this, SLOT(emitClose()));
            tabLayout -> addWidget(exitButt);

            tabLayout -> addStretch();


        tabBox -> setLayout(tabLayout);

    optionLayout -> addWidget(tabBox);
    //optionLayout -> setAlignment(tabBox, Qt::AlignTop);
    //optionLayout -> addStretch();

    optionLabel = new QLabel;
    optionLabel -> setVisible(true);

    optionLayout -> addWidget(optionLabel);

    
    accessLabel = new QLabel;
    accessLabel -> setVisible(false);

    optionLayout -> addWidget(accessLabel);


    aboutLabel = new QLabel;

        QFile file("i18n/fr_FR/about.text");

        QString text = "";
        QString line;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream stream(&file);
            while (!stream.atEnd()){
                line = stream.readLine();
                text = text + line + "\n";
            }
        }
        file.close();

    aboutLabel -> setText(text);
    aboutLabel -> setWordWrap(true);
    aboutLabel -> setTextInteractionFlags(Qt::TextSelectableByMouse);


    aboutScroll = new QScrollArea;
    aboutScroll -> setWidgetResizable(true);
    aboutScroll -> setBackgroundRole(QPalette::Dark);
    aboutScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    aboutScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    aboutScroll -> setWidget(aboutLabel);

    aboutScroll-> setVisible(false);
    
    optionLayout -> addWidget(aboutScroll);




    setLayout(optionLayout);

}


OptionTab::~OptionTab (){

    delete effect;

    delete aboutLabel;
    delete accessLabel;
    delete optionLabel;
   
    delete aboutScroll;

    delete exitButt;
    delete aboutButt;
    delete accessButt;
    delete optionButt;
    
    delete tabLayout;
    delete tabBox;
    delete optionLayout;
}



void OptionTab::paintEvent(QPaintEvent *){
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
};


void OptionTab::setOption (){
    
    aboutScroll -> setVisible(false);
    accessLabel -> setVisible(false);
    optionLabel -> setVisible(true);
}


void OptionTab::setAccess (){
    
    optionLabel -> setVisible(false);
    aboutScroll -> setVisible(false);
    accessLabel -> setVisible(true);
}


void OptionTab::setAbout (){
    
    accessLabel -> setVisible(false);
    optionLabel -> setVisible(false);
    aboutScroll -> setVisible(true);
}


void OptionTab::emitClose (){

    emit closeTab();
}
