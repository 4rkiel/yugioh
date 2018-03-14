#include <QApplication>
#include <QWidget>
#include <QStackedLayout>

#include <QSettings>

#include <QFontDatabase>
#include <QFont>
#include <QIcon>

#include <QFile>

#include "../inc/field.h"
#include "../inc/intro.h"
#include "../inc/generique.h"
#include "../inc/optab.h"
#include "../inc/ruletab.h"
#include "../inc/helptab.h"

class Window : public QWidget {

    Q_OBJECT

    public:
    Window(QApplication * a);
    ~Window();

    private slots:
    void introStack();
    void fieldStack();
    void optStack();
    void ruleStack();
    void helpStack();
    void changeSettings();

    private:
    int currentLayout;
    QApplication * a;
    QStackedLayout * stackedLayout;
    Generique * generique;
    Intro * intro;
    Field * field;
    OptionTab * opt; 
    RuleTab * rule;
    HelpTab * help;

    void cleanStack();

    protected:
    void closeEvent(QCloseEvent *);
    virtual void readSizeSettings();
    virtual void readConfSettings();
    virtual void writeSettings();
};
