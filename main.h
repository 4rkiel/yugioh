#include <QApplication>
#include <QWidget>
#include <QStackedLayout>

#include <QFontDatabase>
#include <QFont>
#include <QIcon>

#include <QFile>

#include "app.h"
#include "intro.h"

class Window : public QWidget {

    Q_OBJECT

    public:
    Window();
    ~Window();

    private slots:
    void changeStacked();

    private:
    QStackedLayout * stackedLayout;
    Intro * intro;
    App * app;
    int currentLayout;

};
