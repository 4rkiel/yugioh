#include "main.h"
#include "intro.h"
#include "app.h"

Window::Window () : QWidget () {

    readSettings();

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

    currentLayout = 2;
}


void Window::optStack (){

    opt = new OptionTab;
    connect(opt, SIGNAL(introStack()), this, SLOT(introStack()));

    stackedLayout -> addWidget(opt);
    stackedLayout -> setCurrentWidget(opt);

    cleanStack();

    currentLayout = 5;
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

        case 5:
 
            stackedLayout -> removeWidget(opt);
            delete opt;
            
            break;
    }
}


/*****************************************************************************/

void Window::readSettings (){
    QSettings settings;
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}


void Window::closeEvent (QCloseEvent *){
    writeSettings();
}


void Window::writeSettings (){
    
    /* Save postion/size of main window */
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

    // Load new font file
    
    int id = QFontDatabase::addApplicationFont("font/Roboto-Thin.ttf");

    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont roboto(family, 14);
    QApplication::setFont(roboto);

    QFontDatabase::addApplicationFont("font/FontAwesomeSolid.otf"); 


    // Load new qss file
    
    QFile file("style/stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    app.setStyleSheet(styleSheet);


    // Load main widget

    Window w;

    //w.resize(500, 700);
    w.setWindowTitle("Trading Card Game");
    w.setWindowIcon(QIcon("card.svg"));

    w.show();

    return app.exec();
}
