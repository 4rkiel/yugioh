#include <QApplication>
#include <QWidget>
#include <QStackedLayout>

#include <QFontDatabase>
#include <QFont>
#include <QIcon>

#include <QFile>

#include "app.h"
#include "intro.h"
#include "generique.h"

class Window : public QWidget {

    Q_OBJECT

    public:
    Window();
    ~Window();

    private slots:
    void changeStacked();
    void primoStack();

    private:
    int currentLayout;
    QStackedLayout * stackedLayout;
    Intro * intro;
    App * app;
    Generique * generique;


    protected:
    void closeEvent(QCloseEvent* event);
    virtual void readSettings();
    virtual void writeSettings();

};
