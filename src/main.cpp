#include "../inc/main.h"

/******************************************************************************

	Fonction Main et Class Window 

	Permet de gérer les contenus affichés à l'utilisateur

******************************************************************************/

Window::Window (QApplication * q, QTranslator * montr, QTranslator * montr2) {

    a = q;
    montranslator = montr;
    montranslator2 = montr2;

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
            delete master;
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
    }

    delete stackedLayout;

    writeSettings();
}


void Window::introStack (){

    intro = new Intro;
    connect(intro, SIGNAL(masterStack()), this, SLOT(masterStack()));
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

void Window::masterStack (){

    master = new Master;
    connect(master, SIGNAL(introStack()), this, SLOT(introStack()));

    stackedLayout -> addWidget(master);
    stackedLayout -> setCurrentWidget(master);

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
 
            stackedLayout -> removeWidget(master);
            delete master;
            
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
    
    int id;
    
    if (settings.value("dyslexie", false).toBool()){
        id = QFontDatabase::addApplicationFont("font/OpenDyslexic-Regular.otf");
    } else {
        id = QFontDatabase::addApplicationFont("font/Roboto-Thin.ttf");
    }

    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font;
    font.setFamily(family);
    
    if (settings.value("large", false).toBool()){
        font.setPointSize(14);
    } else {
        font.setPointSize(11);
    }

    QApplication::setFont(font);

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

    //trad
    QString val = settings.value("langage", QLocale::system().name()).toString();

    montranslator->load("qt_"+val, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a->installTranslator(montranslator);

    montranslator2->load("i18n/"+val+"/yugi_"+val);
    a->installTranslator(montranslator2);



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


    // trad de depart
    QSettings settings;
    QString val = settings.value("langage", QLocale::system().name()).toString();

    QTranslator qtTranslator;
    qtTranslator.load("qt_"+val, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    QTranslator YugiTranslator;
    YugiTranslator.load("i18n/"+val+"/yugi_"+val);
    app.installTranslator(&YugiTranslator);

    // set UTF8

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    // Load main widget

    Window w(&app,&qtTranslator,&YugiTranslator);

    w.setWindowTitle("Trading Card Game");
    w.setWindowIcon(QIcon("img/icon.svg"));

    w.show();

    return app.exec();
}
