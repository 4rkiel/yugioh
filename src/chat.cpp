#include "../inc/chat.h"
#include <QScrollBar>
/******************************************************************************

	Widget permettant d'afficher le contenu du chat

******************************************************************************/

Chat::Chat(){

    last = -1;

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSizePolicy sp = sizePolicy();
    sp.setRetainSizeWhenHidden(true);
    setSizePolicy(sp);

    layout = new QGridLayout;
    layout -> setContentsMargins(0,0,0,0);

        label = new QTextEdit;

        label -> setReadOnly(true);
        label -> setAcceptRichText(true);
        label -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        label -> setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        label -> setWordWrapMode(QTextOption::WrapAnywhere);
        label -> setLineWrapMode(QTextEdit::WidgetWidth);
        label -> setFocusPolicy(Qt::NoFocus);

        layout -> addWidget(label, 1, 0, 3, 4);


        input = new QLineEdit;

    layout -> addWidget(input, 4, 0, 1, 3);

        
        send = new DarkButt("\uf1d8","");

    layout -> addWidget(send, 4, 3, 1, 1);

    connect(send, SIGNAL(clicked()), this, SLOT(sendMsg()));
    connect(input, SIGNAL(returnPressed()), this, SLOT(sendMsg()));
    
    QScrollBar * scrollbar = label -> verticalScrollBar();
    connect(scrollbar, SIGNAL(rangeChanged(int,int)), 
            this, SLOT(moveScrollBarToBottom(int, int)));

    shortcut = new QShortcut(QKeySequence("Escape"), this);
    shortcut->setContext(Qt::WidgetWithChildrenShortcut);
    connect(shortcut, SIGNAL(activated()), this, SLOT(openQuit()));


    setLayout(layout);


    label -> insertHtml(
        "<h4>"+ tr("Informations") +"</h4>"
    );

    last = 0;

}


Chat::~Chat(){

    delete label;
//    delete labLayout;
//    delete labInner;
//    delete labelBox;
    delete input;
    delete send;
    delete layout;
}


void Chat::addText(QString str, int x){

    label -> moveCursor (QTextCursor::End);
    
    if (x != last){

        last = x; 
        
        switch (x){

            case 0:

                label -> insertHtml(
                    "<br/>"
                    "<h4>"+ tr("Informations") +"</h4>"
                );
                
                break;

            case 1:

                label -> insertHtml(
                    "<br/>"
                    "<h4>"+ tr("Adversaire") +"</h4>"
                );
                
                break;

            case 2:

                label -> insertHtml(
                    "<br/>"
                    "<h4>"+ tr("Vous") +"</h4>"
                );
                
                break;
        }
    }


    label -> insertHtml("<br/><br/>");
    
    QString time = QTime::currentTime().toString("hh:mm");

    label -> insertHtml(
        "<p><i style=\"color: #546E7A \">"+ time +" : </i>" + str + "</p>");
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
        if(!input->text().startsWith("þ")){
            emit msgSent("þ"+input -> text());
        }
	}

    input -> setText("");
    input -> setFocus();
}


void Chat::moveScrollBarToBottom(int min, int max){
    Q_UNUSED(min);
    label -> verticalScrollBar()->setValue(max);
}

void Chat::openQuit(){
    emit rcvQuit();
}

void Chat::goFocus(){
    send -> setFocus();
}
