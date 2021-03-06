#ifndef GEN
#define GEN

#include <QApplication>
#include <QFrame>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QString>
#include <QLabel>

#include <QPixmap>

#include "../inc/genProgress.h"


class Generique : public QFrame {

    Q_OBJECT
 
    public:
    Generique();
    ~Generique();

    public slots:
    void goToStack();
    void newLabel();

    signals:
    void introStack();

    private:
    QGridLayout * layout;

    QWidget * logoBox;
    QGridLayout * logoLayout;
    QLabel * title;
    QLabel * subTitle;
    QLabel * img;
    
    QWidget * geneBox;
    QVBoxLayout * box;
    int labelCount;
    QLabel * state;
    GenProgress * progress;
};


#endif
