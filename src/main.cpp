#include "../inc/main.h"

Window::Window () {

    readSizeSettings();
    readConfSettings();


    stackedLayout = new QStackedLayout;

    generique = new Generique;
    connect(generique, SIGNAL(introStack()), this, SLOT(introStack()));
    
    stackedLayout -> addWidget(generique);
    setLayout(stackedLayout);
    
    currentLayout = 0;
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
            delete app;
            break;
        
        case 4 :
            delete rule;
            break;

        case 5 :
            delete opt;
            break;
    }

    delete stackedLayout;

    writeSettings();
}


void Window::introStack (){

    intro = new Intro;
    connect(intro, SIGNAL(appStack()), this, SLOT(appStack()));
    connect(intro, SIGNAL(ruleStack()), this, SLOT(ruleStack()));
    connect(intro, SIGNAL(optStack()), this, SLOT(optStack()));

    stackedLayout -> addWidget(intro);
    stackedLayout -> setCurrentWidget(intro);

    cleanStack();

    intro -> init();
    currentLayout = 1;
}


void Window::appStack (){

    app = new App;
    connect(app, SIGNAL(introStack()), this, SLOT(introStack()));

    stackedLayout -> addWidget(app);
    stackedLayout -> setCurrentWidget(app);

    cleanStack();

    app -> init();
    currentLayout = 2;
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


void Window::changeSettings(){
    readConfSettings();
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
 
            stackedLayout -> removeWidget(app);
            delete app;
            
            break;

        case 4:
 
            stackedLayout -> removeWidget(rule);
            delete rule;
            
            break;

        case 5:
 
            stackedLayout -> removeWidget(opt);
            delete opt;
            
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
    
    setStyleSheet(styleSheet);

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

    Window w;

    w.setWindowTitle("Trading Card Game");
    w.setWindowIcon(QIcon("img/card.svg"));

    w.show();

    return app.exec();
}
