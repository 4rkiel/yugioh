#include "main.h"
#include "intro.h"
#include "app.h"


Window::Window () : QWidget () {

    stackedLayout = new QStackedLayout;
    currentLayout = 0;

    intro = new Intro;
    stackedLayout->addWidget(intro);
    connect(intro, SIGNAL(newStack()), this, SLOT(changeStacked()));
    
    app = new App;
    stackedLayout->addWidget(app);
    connect(app, SIGNAL(newStack()), this, SLOT(changeStacked()));

    this -> setLayout(stackedLayout);


}

    
Window::~Window (){

    delete intro;
    delete app;
    delete stackedLayout;
}


void Window::changeStacked (){

    currentLayout = (currentLayout + 1)%2;

    switch (currentLayout){
        case 0:
            
            stackedLayout -> setCurrentWidget(intro);
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


    // Load new qss file
    
    QFile file("style/stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    app.setStyleSheet(styleSheet);


    // Load main widget

    Window w;
//    w.resize(500, 400);
    w.setWindowTitle("BGE - Best Game Ever");
    w.setWindowIcon(QIcon("nyancat.png"));

    w.show();


    return app.exec();
}
