#include <optionTab.h>

OptionTab::OptionTab (){

    setObjectName("optionBox");
    setVisible(false);

    optionLayout = new QVBoxLayout;
    optionLayout -> setSpacing(0);
    optionLayout -> setMargin(0);
    optionLayout -> setAlignment(Qt::AlignCenter);

        tabBox = new Widget;
        tabLayout = new QHBoxLayout;
        
            optionButt = new QPushButton;
            tabLayout -> addWidget(optionButt);
  
            accessButt = new QPushButton;
            tabLayout -> addWidget(accessButt);

            aboutButt = new QPushButton;
            tabLayout -> addWidget(aboutButt);
               

        tabBox -> setLayout(tabLayout);

    optionLayout -> addWidget(tabBox);


    optionLabel = new QLabel;
    optionLabel -> setVisible(true);

    optionLayout -> addWidget(optionLabel);

    
    accessLabel = new QLabel;
    accessLabel -> setVisible(false);

    optionLayout -> addWidget(accessLabel);


    aboutLabel = new QLabel;
    aboutLabel -> setVisible(false);

    optionLayout -> addWidget(aboutLabel);




    setLayout(optionLayout);

}


Tab::~Tab (){



}
