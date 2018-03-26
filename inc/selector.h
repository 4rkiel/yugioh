#ifndef SELECTOR
#define SELECTOR

#include <QStackedWidget>
#include <QGridLayout>

#include "../inc/choice.h"
#include "../inc/soloChoice.h"
#include "../inc/joinChoice.h"
#include "../inc/hostChoice.h"
#include "../inc/netChoice.h"

class Selector : public QFrame {

Q_OBJECT

public:
    
    Selector();
    ~Selector();


public slots:

    void emitIntro();
    void emitGame(int);
    void choiceStack();
    void soloStack();
    void joinStack();
    void hostStack();
    void netStack();


signals:

    void introStack();
    void gameStack(int);

private:

    void clean();

    int mode;

    QStackedWidget * stacked;
    QGridLayout * layout;

    Choice * choice;
    SoloChoice * soloChoice;
    JoinChoice * joinChoice;
    HostChoice * hostChoice;
    NetChoice * netChoice;
};

#endif
