#ifndef THEMAIN
#define THEMAIN

#include <QApplication>
#include <QWidget>
#include <QStackedLayout>

#include <QSettings>

#include <QFontDatabase>
#include <QFont>
#include <QIcon>

#include <QFile>
#include <QTranslator>
#include <QString>
#include <QTextCodec>

#include "../inc/master.h"
#include "../inc/field.h"
#include "../inc/intro.h"
//#include "../inc/choice.h"
//#include "../inc/soloChoice.h"
//#include "../inc/joinChoice.h"
//#include "../inc/hostChoice.h"
//#include "../inc/netChoice.h"
#include "../inc/generique.h"
#include "../inc/buildtab.h"
#include "../inc/optab.h"
#include "../inc/ruletab.h"
#include "../inc/helptab.h"

class Window : public QWidget {

    Q_OBJECT

    public:
    Window(QApplication * a,QTranslator* montranslator,QTranslator* montranslator2);
    ~Window();

    private slots:
    void introStack();
//	void choiceStack();
//    void soloStack();
//	void joinStack();
//	void hostStack();
//	void netStack();

    void masterStack();
//    void fieldStack();
    void buildStack();
    void optStack();
    void ruleStack();
    void helpStack();
    void changeSettings();

    private:
    int currentLayout;
    QApplication * a;
    QTranslator* montranslator;
    QTranslator* montranslator2;
    QStackedLayout * stackedLayout;
    Generique * generique;
    Intro * intro;
//	Choice * choice;
//    SoloChoice * soloChoice;
//	JoinChoice * joinChoice;
//	HostChoice * hostChoice;
//	NetChoice * netChoice;
    Master * master;
    Field * field;
    BuildTab * build;
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

#endif
