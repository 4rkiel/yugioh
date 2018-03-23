#include "../inc/main.h"

/******************************************************************************

	Fonction Main et Class Window 

	Permet de gérer les contenus affichés à l'utilisateur

******************************************************************************/

Window::Window (QApplication * q) {

    a = q;

    currentLayout = 0;
    
    readSizeSettings();
    readConfSettings();


    stackedLayout = new QStackedLayout;

    generique = new Generique;
    connect(generique, SIGNAL(introStack()), this, SLOT(introStack()));
    
    stackedLayout -> addWidget(generique);
    setLayout(stackedLayout);
    
}

    
Window::~Window (){

    switch (currentLayout){
        case 0 :
            delete generique;
            break;

        case 1 :
            delete intro;
            break;

        case 2 :
            delete field;
            break;

        case 3:
            delete build;
            break;

        case 4 :
            delete rule;
            break;

        case 5 :
            delete opt;
            break;

        case 6 :
            delete help;
            break;

		case 7:
			delete choice;
			break;

        case 8:
            delete joinChoice;
            break;

        case 9:
            delete hostChoice;
            break;

        case 10:
            delete netChoice;
            break;

        case 11:
            delete soloChoice;
            break;
    }

    delete stackedLayout;

    writeSettings();
}


void Window::introStack (){

    intro = new Intro;
    connect(intro, SIGNAL(choiceStack()), this, SLOT(choiceStack()));
    connect(intro, SIGNAL(buildStack()), this, SLOT(buildStack()));
    connect(intro, SIGNAL(ruleStack()), this, SLOT(ruleStack()));
    connect(intro, SIGNAL(optStack()), this, SLOT(optStack()));
    connect(intro, SIGNAL(helpStack()), this, SLOT(helpStack()));

    stackedLayout -> addWidget(intro);
    stackedLayout -> setCurrentWidget(intro);

    cleanStack();

    intro -> init();
    currentLayout = 1;
}

void Window::fieldStack (){

    field = new Field;
    connect(field, SIGNAL(introStack()), this, SLOT(introStack()));

    stackedLayout -> addWidget(field);
    stackedLayout -> setCurrentWidget(field);

    cleanStack();

    currentLayout = 2;
}


void Window::buildStack (){

    build = new BuildTab;
    connect(build, SIGNAL(introStack()), this, SLOT(introStack()));

    stackedLayout -> addWidget(build);
    stackedLayout -> setCurrentWidget(build);

    cleanStack();

    build -> init();
    currentLayout = 3;
}


void Window::ruleStack (){

    rule = new RuleTab;
    connect(rule, SIGNAL(introStack()), this, SLOT(introStack()));

    stackedLayout -> addWidget(rule);
    stackedLayout -> setCurrentWidget(rule);

    cleanStack();

    rule -> init();
    currentLayout = 4;
}


void Window::optStack (){

    opt = new OptionTab;
    connect(opt, SIGNAL(introStack()), this, SLOT(introStack()));
    connect(opt, SIGNAL(newSettings()), this, SLOT(changeSettings()));
    stackedLayout -> addWidget(opt);
    stackedLayout -> setCurrentWidget(opt);

    cleanStack();

    opt -> init();
    currentLayout = 5;
}


void Window::helpStack (){

    help = new HelpTab;
    connect(help, SIGNAL(introStack()), this, SLOT(introStack()));
    stackedLayout -> addWidget(help);
    stackedLayout -> setCurrentWidget(help);

    cleanStack();

    help -> init();
    currentLayout = 6;
}


void Window::choiceStack (){
	
	choice = new Choice;
	
    connect(choice, SIGNAL(introStack()), this, SLOT(introStack()));
    connect(choice, SIGNAL(joinStack()), this, SLOT(joinStack()));
    connect(choice, SIGNAL(hostStack()), this, SLOT(hostStack()));
    connect(choice, SIGNAL(netStack()), this, SLOT(netStack()));
    connect(choice, SIGNAL(soloStack()), this, SLOT(soloStack()));
	
	stackedLayout -> addWidget(choice);
	stackedLayout -> setCurrentWidget(choice);

	cleanStack();

	currentLayout = 7;
}


void Window::joinStack (){

    joinChoice = new JoinChoice;

    connect(joinChoice, SIGNAL(choiceStack()), this, SLOT(choiceStack()));

    stackedLayout -> addWidget(joinChoice);
    stackedLayout -> setCurrentWidget(joinChoice);

    cleanStack();
    
    currentLayout = 8;
}


void Window::hostStack (){

    hostChoice = new HostChoice;

    connect(hostChoice, SIGNAL(choiceStack()), this, SLOT(choiceStack()));

    stackedLayout -> addWidget(hostChoice);
    stackedLayout -> setCurrentWidget(hostChoice);

    cleanStack();
    
    currentLayout = 9;
}


void Window::netStack (){

    netChoice = new NetChoice;

    connect(netChoice, SIGNAL(choiceStack()), this, SLOT(choiceStack()));

    stackedLayout -> addWidget(netChoice);
    stackedLayout -> setCurrentWidget(netChoice);

    cleanStack();
    
    currentLayout = 10;
}


void Window::soloStack (){

    soloChoice = new SoloChoice;

    connect(soloChoice, SIGNAL(choiceStack()), this, SLOT(choiceStack()));

    stackedLayout -> addWidget(soloChoice);
    stackedLayout -> setCurrentWidget(soloChoice);

    cleanStack();
    
    currentLayout = 11;
}


void Window::changeSettings(){
    readConfSettings();

    if (currentLayout == 4){
        rule -> reInit();
    } else if (currentLayout == 5){
        opt -> reInit();
    }
}


void Window::cleanStack (){

    switch (currentLayout){
    
        case 0:
            
            stackedLayout -> removeWidget(generique);
            delete generique;
            
            break;

        case 1:
 
            stackedLayout -> removeWidget(intro);
            delete intro;
            
            break;

        case 2:
 
            stackedLayout -> removeWidget(field);
            delete field;
            
            break;

        case 3:

            stackedLayout -> removeWidget(build);
            delete build;

            break;

        case 4:
 
            stackedLayout -> removeWidget(rule);
            delete rule;
            
            break;

        case 5:
 
            stackedLayout -> removeWidget(opt);
            delete opt;
            
            break;

        case 6:
 
            stackedLayout -> removeWidget(help);
            delete help;
            
            break;

		case 7:

			stackedLayout -> removeWidget(choice);
			delete choice;

			break;

		case 8:

			stackedLayout -> removeWidget(joinChoice);
			delete joinChoice;

			break;

		case 9:

			stackedLayout -> removeWidget(hostChoice);
			delete hostChoice;

			break;

		case 10:

			stackedLayout -> removeWidget(netChoice);
			delete netChoice;

			break;

		case 11:

			stackedLayout -> removeWidget(soloChoice);
			delete soloChoice;

			break;

    }
}




/*****************************************************************************/

void Window::readSizeSettings (){

    QSettings settings;

    // Window Position

    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);

}


void Window::readConfSettings (){

    QSettings settings;
    
    // Load new font file
    
    int id = QFontDatabase::addApplicationFont("font/Roboto-Thin.ttf");

    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont roboto;
    roboto.setFamily(family);
    
    if (settings.value("large", false).toBool()){
        roboto.setPointSize(14);
    } else {
        roboto.setPointSize(12);
    }

    QApplication::setFont(roboto);

    QFontDatabase::addApplicationFont("font/FontAwesomeSolid.otf"); 


    // Load new qss file
   
    QFile file;
    file.setFileName("style/stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    file.close();

    if (settings.value("achroma", false).toBool() &&
            settings.value("contraste", false).toBool()){
    
        file.setFileName("style/stylesheet.qss");
        file.open(QFile::ReadOnly);
        styleSheet = styleSheet + QLatin1String(file.readAll());
        file.close();

        file.setFileName("style/dys.qss");
        file.open(QFile::ReadOnly);
        styleSheet = styleSheet + QLatin1String(file.readAll());
        file.close();

    } else if (settings.value("achroma", false).toBool()){

        file.setFileName("style/dys.qss");
        file.open(QFile::ReadOnly);
        styleSheet = styleSheet + QLatin1String(file.readAll());
        file.close();

    } else if (settings.value("contraste", false).toBool()){

        file.setFileName("style/stylesheet.qss");
        file.open(QFile::ReadOnly);
        styleSheet = styleSheet + QLatin1String(file.readAll());
        file.close();
    }
    
    a -> setStyleSheet(styleSheet);

}


void Window::closeEvent (QCloseEvent *){
    writeSettings();
}


void Window::writeSettings (){
    
    QSettings settings;
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}



/*****************************************************************************/

int main(int argc, char *argv[]) {

    // Set Application

    QApplication app(argc, argv);
    app.setOrganizationName("Yu-Gi-Home");
    app.setOrganizationDomain("Yu.Gi.Oh");
    app.setApplicationName("Yu-Gi-Oh");


    // Load main widget

    Window w(&app);

    w.setWindowTitle("Trading Card Game");
    w.setWindowIcon(QIcon("img/icon.svg"));

    w.show();

    return app.exec();
}
