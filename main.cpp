#include "main.h"
#include "intro.h"
#include "app.h"


Window::Window () : QWidget () {

    stackedLayout = new QStackedLayout;
    currentLayout = 0;

    generique = new Generique;
    stackedLayout -> addWidget(generique);
    connect(generique, SIGNAL(introStack()), this, SLOT(primoStack()));

    intro = new Intro;
    stackedLayout -> addWidget(intro);
    connect(intro, SIGNAL(newStack()), this, SLOT(changeStacked()));


    app = new App;
    stackedLayout -> addWidget(app);
    connect(app, SIGNAL(newStack()), this, SLOT(changeStacked()));

    setLayout(stackedLayout);
}

    
Window::~Window (){

    delete app;
    delete intro;
    delete generique;

    delete stackedLayout;
}


void Window::primoStack (){

    stackedLayout -> setCurrentWidget(intro);
    intro -> init();

}


void Window::changeStacked (){

    currentLayout = (currentLayout + 1) % 2;

    switch (currentLayout){
        case 0:
            
            stackedLayout -> setCurrentWidget(intro);
            intro -> init();
            
            break;

        case 1:

            stackedLayout -> setCurrentWidget(app);
            break;
    }
}



int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    // Load new font file
    
    int id = QFontDatabase::addApplicationFont("font/Roboto-Thin.ttf");

    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont roboto(family, 14);
    QApplication::setFont(roboto);

//    QFontDatabase::addApplicationFont("font/FontAwesome.otf"); 
    QFontDatabase::addApplicationFont("font/FontAwesomeSolid.otf"); 


    // Load new qss file
    
    QFile file("style/stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    app.setStyleSheet(styleSheet);


    // Load main widget

    Window w;
    w.resize(500, 700);
    w.setWindowTitle("Trading Card Game");
    w.setWindowIcon(QIcon("card.svg"));

    w.show();


    return app.exec();
}
