#include <QApplication>
#include <QWidget>
#include <QStackedLayout>

#include <QSettings>

#include <QFontDatabase>
#include <QFont>
#include <QIcon>

#include <QFile>

#include "app.h"
#include "intro.h"
#include "generique.h"
#include "optab.h"

class Window : public QWidget {

    Q_OBJECT

    public:
    Window();
    ~Window();

    private slots:
    void introStack();
    void appStack();
    void optStack();

    private:
    int currentLayout;
    QStackedLayout * stackedLayout;
    Generique * generique;
    Intro * intro;
    App * app;
    OptionTab * opt; 

    void cleanStack();

    protected:
    void closeEvent(QCloseEvent *);
    virtual void readSettings();
    virtual void writeSettings();
};
