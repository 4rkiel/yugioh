#include "optab.h"

OptionTab::OptionTab (){

    layout = new QGridLayout;
    
    optEffect = new QGraphicsDropShadowEffect(this);
    optEffect -> setBlurRadius(5);
    optEffect -> setXOffset(0);
    optEffect -> setYOffset(5);
    optEffect -> setColor(QColor(0,0,0,150));

    setGraphicsEffect(optEffect);

        // Tab

        tabBox = new QWidget;
        tabBox -> setObjectName("optionTab");
        tabLayout = new QGridLayout;
        tabLayout -> setSpacing(0);
        tabLayout -> setMargin(0);
  
            exitButt = new ShadowButt("\uf00d", "");
            exitButt -> setToolTip("Fermer les paramètres");
            connect(exitButt, SIGNAL(clicked()), this, SLOT(emitClose()));
            
            tabLayout -> addWidget(exitButt, 0, 4, 1, 1);



            optionButt = new QPushButton;
            optionButt -> setText("Options");
            optionButt -> setProperty("down", true);
            connect(optionButt, SIGNAL(clicked()), this, SLOT(setOption()));
            tabLayout -> addWidget(optionButt, 0, 0, 1, 1);
            currButt = optionButt;

            accessButt = new QPushButton;
            accessButt -> setText("Accessibilité");
            accessButt -> setProperty("down", false);
            connect(accessButt, SIGNAL(clicked()), this, SLOT(setAccess()));
            tabLayout -> addWidget(accessButt, 0, 1, 1, 1);

            aboutButt = new QPushButton;
            aboutButt -> setText("A Propos");
            aboutButt -> setProperty("down", false);
            connect(aboutButt, SIGNAL(clicked()), this, SLOT(setAbout()));
            tabLayout -> addWidget(aboutButt, 0, 2, 1, 1);

            tabLayout -> addItem(new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Preferred),0,3);

        tabBox -> setLayout(tabLayout);


    layout -> addWidget(tabBox, 0, 0, 1, 1);





        // Label Box

        optBox = new QWidget;
        
        optionLayout = new QStackedLayout;
        optionLayout -> setSpacing(0);
        optionLayout -> setMargin(0);


            optionLabel = new QLabel;

            optionLayout -> addWidget(optionLabel);

            
            accessLabel = new QLabel;

            optionLayout -> addWidget(accessLabel);


            aboutScroll = new QScrollArea;
            aboutScroll -> setFrameShape(QFrame::NoFrame);
            aboutScroll -> setWidgetResizable(true);
            aboutScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            aboutScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
 

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
                aboutLabel->setTextFormat(Qt::RichText);
                aboutLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
                aboutLabel->setOpenExternalLinks(true);

                aboutScroll -> setWidget(aboutLabel);

            
            optionLayout -> addWidget(aboutScroll);


        optionLayout -> setCurrentWidget(optionLabel);
        optBox -> setLayout(optionLayout);

    layout -> addWidget(optBox, 1, 0, 1, 2);

    setLayout(layout);
}


OptionTab::~OptionTab (){

    delete optEffect;

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

    delete optBox;

    delete layout;
}


void OptionTab::setOption (){

    currButt -> setProperty("down", false);
    optionButt -> setProperty("down", true);

    updateStyle(optionButt);

    optionLayout -> setCurrentWidget(optionLabel);
}


void OptionTab::setAccess (){
 
    currButt -> setProperty("down", false);
    accessButt -> setProperty("down", true);
   
    updateStyle(accessButt);
    
    optionLayout -> setCurrentWidget(accessLabel);
}


void OptionTab::setAbout (){
 
    currButt -> setProperty("down", false);
    aboutButt -> setProperty("down", true);

    updateStyle(aboutButt);

    optionLayout -> setCurrentWidget(aboutScroll);
}


void OptionTab::updateStyle (QPushButton * b){
    
    currButt -> style() -> unpolish(currButt);
    currButt -> style() -> polish(currButt);
    
    b -> style() -> unpolish(b);
    b -> style() -> polish(b);

    currButt = b;
}


void OptionTab::emitClose (){

    emit introStack();
}


