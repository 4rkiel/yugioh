#ifndef APP
#define APP

#include <QApplication>
#include <QFrame>
#include <QWidget>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QStackedLayout>

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
    void openMenu();
    void closeMenu();

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
        QPushButton * menuButt;

    QWidget * popupOuter;
    QGridLayout * popupOuterLayout;
    QPushButton * popupShadow;
    QWidget * popupBox;
    QStackedLayout * popupLayout;
    
        QWidget * menuOuter;
        QGridLayout * menuOuterLayout;

        QWidget * menuBox;
        QVBoxLayout * menuLayout;

        QPushButton * quit;
        QPushButton * back;
};


#endif
