#include "../inc/buildtab.h"

BuildTab::BuildTab (){

    layout = new QGridLayout;
    layout -> setSpacing(0);
    layout -> setMargin(0);
    
    helpEffect = new QGraphicsDropShadowEffect(this);
    helpEffect -> setBlurRadius(5);
    helpEffect -> setXOffset(0);
    helpEffect -> setYOffset(5);
    helpEffect -> setColor(QColor(0,0,0,150));

    setGraphicsEffect(helpEffect);

        // Tab box ............................................................

        tabBox = new QWidget;
        tabBox -> setObjectName("buildTab");
        tabLayout = new QGridLayout;
        tabLayout -> setSpacing(0);
        tabLayout -> setMargin(0);
  
            exitButt = new ShadowButt("\uf00d", "");
            exitButt -> setToolTip("Fermer l'aide");
            connect(exitButt, SIGNAL(clicked()), this, SLOT(emitClose()));
            
            tabLayout -> addWidget(exitButt, 0, 4, 1, 1);


            helpButt = new QPushButton;
            helpButt -> setText("Aide");
            helpButt -> setProperty("down", true);
            connect(helpButt, SIGNAL(clicked()), this, SLOT(setHelp()));

            tabLayout -> addWidget(helpButt, 0, 0, 1, 1);
            

            aboutButt = new QPushButton;
            aboutButt -> setText("A Propos");
            aboutButt -> setProperty("down", false);
            connect(aboutButt, SIGNAL(clicked()), this, SLOT(setAbout()));

            tabLayout -> addWidget(aboutButt, 0, 1, 1, 1);
            

            QSpacerItem * spacerButt = new QSpacerItem(1,1,
                    QSizePolicy::Expanding,QSizePolicy::Preferred);
            
            tabLayout -> addItem(spacerButt, 0, 2);

        tabBox -> setLayout(tabLayout);


    layout -> addWidget(tabBox, 0, 0, 1, 1);



        // Label Box ..........................................................

        helpBox = new QWidget;
        helpBox -> setObjectName("helpBox");
        
        helpLayout = new QStackedLayout;
        helpLayout -> setSpacing(0);
        helpLayout -> setMargin(0);


            // Help ...........................................................

            helpScroll = new QScrollArea;
            helpScroll -> setFrameShape(QFrame::NoFrame);
            helpScroll -> setWidgetResizable(true);
            helpScroll -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            helpScroll -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            helpScroll -> setFocusPolicy(Qt::NoFocus);

                helpLabel = new QLabel;

                    QFile hfile("i18n/fr_FR/help.text");

                    QString htext = "";
                    QString hline;
                    if (hfile.open(QIODevice::ReadOnly | QIODevice::Text)){
                        QTextStream hstream(&hfile);
                        while (!hstream.atEnd()){
                            hline = hstream.readLine();
                            htext = htext + hline + "\n";
                        }
                    }
                    hfile.close();

                helpLabel -> setText(htext);
                helpLabel -> setWordWrap(true);
                helpLabel -> setTextInteractionFlags(Qt::TextSelectableByMouse);
                helpLabel->setTextFormat(Qt::RichText);
                helpLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
                helpLabel->setOpenExternalLinks(true);

                helpScroll -> setWidget(helpLabel);

            helpLayout -> addWidget(helpScroll);

           


            // About ..........................................................

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

            helpLayout -> addWidget(aboutScroll);


        helpLayout -> setCurrentWidget(helpScroll);
        helpBox -> setLayout(helpLayout);

    layout -> addWidget(helpBox, 1, 0, 1, 2);

    setLayout(layout);

}


BuildTab::~BuildTab (){
    

    delete aboutLabel;
    delete aboutScroll;

    delete helpLabel;
    delete helpScroll;

        delete exitButt;
        delete aboutButt;
        delete helpButt;
    
    delete helpLayout;
    delete helpBox;
    delete tabLayout;
    delete tabBox;
    
    delete helpEffect;
    
    delete layout;
}


void BuildTab::init (){

    currButt = helpButt;
    helpButt -> setFocus();
}

void BuildTab::reInit (){

    updateStyle(currButt);
}


void BuildTab::setHelp (){

    updateStyle(helpButt);

    helpLayout -> setCurrentWidget(helpScroll);
}


void BuildTab::setAbout (){

    updateStyle(aboutButt);

    helpLayout -> setCurrentWidget(aboutScroll);
}


void BuildTab::updateStyle (QPushButton * b){
     
    currButt -> setProperty("down", false);
    b -> setProperty("down", true);

    currButt -> style() -> unpolish(currButt);
    currButt -> style() -> polish(currButt);
    
    b -> style() -> unpolish(b);
    b -> style() -> polish(b);

    currButt = b;
}


void BuildTab::emitClose (){

    emit introStack();
}


