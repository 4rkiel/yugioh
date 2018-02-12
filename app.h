#ifndef APP
#define APP

#include <QApplication>
#include <QFrame>

#include <QGridLayout>
#include <QPushButton>
#include <QIcon>
#include <QString>
#include <QLabel>

class App : public QFrame {

    Q_OBJECT
 
    public:
    App();
    ~App();

    public slots:
    void emitNewStack();

    signals:
    void newStack();

    private:
    QPushButton * button;
    QPushButton * quit;
    QLabel * text;

};


#endif
