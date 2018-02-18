#ifndef APP
#define APP

#include <QApplication>
#include <QFrame>

#include <QGridLayout>
#include <QWidget>
#include <QVBoxLayout>

#include <QPushButton>
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
    QGridLayout * overLayout;
    QWidget * sceneBox;
    QGridLayout * sceneLayout;
    
    QWidget * leftBarBox;
    QVBoxLayout * leftBarLayout;
    
    QWidget * arenaBox;
    QGridLayout * arenaLayout;
    
    QWidget * rightBarBox;
    QVBoxLayout * rightBarLayout;


    QLabel * lifeAdv;
    QLabel * lifeSlf;
    QPushButton * menu;
};


#endif
