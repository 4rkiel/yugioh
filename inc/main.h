#include <QApplication>
#include <QWidget>
#include <QStackedLayout>

#include <QSettings>

#include <QFontDatabase>
#include <QFont>
#include <QIcon>

#include <QFile>

#include "../inc/app.h"
#include "../inc/intro.h"
#include "../inc/generique.h"
#include "../inc/optab.h"
#include "../inc/ruletab.h"

class Window : public QWidget {

    Q_OBJECT

    public:
    Window();
    ~Window();

    private slots:
    void introStack();
    void appStack();
    void optStack();
    void ruleStack();
    void changeSettings();

    private:
    int currentLayout;
    QStackedLayout * stackedLayout;
    Generique * generique;
    Intro * intro;
    App * app;
    OptionTab * opt; 
    RuleTab * rule;

    void cleanStack();

    protected:
    void closeEvent(QCloseEvent *);
    virtual void readSizeSettings();
    virtual void readConfSettings();
    virtual void writeSettings();
};
