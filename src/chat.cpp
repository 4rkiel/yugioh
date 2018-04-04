#include "../inc/chat.h"
#include <QScrollBar>
/******************************************************************************

	Widget permettant d'afficher le contenu du chat

******************************************************************************/

Chat::Chat(){

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSizePolicy sp = sizePolicy();
    sp.setRetainSizeWhenHidden(true);
    setSizePolicy(sp);

    layout = new QGridLayout;
    layout -> setContentsMargins(0,0,0,0);


        title = new QLabel;
		title -> setObjectName("sideTitle");
        title -> setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        title -> setText(tr("Chat"));

    layout -> addWidget(title, 0, 0, 1, 4);


        labelBox = new QScrollArea;
        labelBox -> setFrameShape(QFrame::NoFrame);
        labelBox -> setWidgetResizable(true);
        labelBox -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        labelBox -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        labelBox -> setFocusPolicy(Qt::NoFocus);

            labInner = new QWidget;
            labLayout = new QVBoxLayout;
            labLayout -> setMargin(0);
            labLayout -> setSpacing(0);
            layout -> setContentsMargins(0,0,0,0);

            label = new QLabel;
            
            labLayout -> addStretch();
			labLayout -> addWidget(label);

			labInner -> setLayout(labLayout);
        
        labelBox -> setWidget(labInner);

    layout -> addWidget(labelBox, 1, 0, 3, 4);


        input = new QLineEdit;

    layout -> addWidget(input, 4, 0, 1, 3);

        
        send = new ShadowButt("\uf1d8","");

    layout -> addWidget(send, 4, 3, 1, 1);

    connect(send, SIGNAL(clicked()), this, SLOT(sendMsg()));
    connect(input, SIGNAL(returnPressed()), this, SLOT(sendMsg()));
    
    QScrollBar * scrollbar = labelBox -> verticalScrollBar();
    connect(scrollbar, SIGNAL(rangeChanged(int,int)), 
            this, SLOT(moveScrollBarToBottom(int, int)));


    setLayout(layout);
}


Chat::~Chat(){

    delete title;
    delete label;
    delete labLayout;
    delete labInner;
    delete labelBox;
    delete input;
    delete send;
    delete layout;
}


void Chat::addText(QString str, int /* what */){

    // 0 histo
    // 1 self
    // 2 adv

    QString time = QTime::currentTime().toString("hh:mm");
    QString tmp = label -> text();
    tmp.append("\n\n" + time + " : " + str);
    label -> setText(tmp);
}

void Chat::sendMsg(){

	bool check = false;
	for (int i=0; i < input -> text().length(); i++){
		QChar c = input -> text()[i];

        if (c != ' ' && c != '\n' && c != '\r'){
			check = true;
		}
	}

	if (check){
        if(!input->text().startsWith("þ"))
        emit msgSent("þ"+input -> text());
	}

	input -> setText("");    
}


void Chat::moveScrollBarToBottom(int min, int max){
    Q_UNUSED(min);
    labelBox -> verticalScrollBar()->setValue(max);
}
