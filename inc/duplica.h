#ifndef DUPLICA
#define DUPLICA

#include <QFrame>

#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsDropShadowEffect>

class Duplica : public QFrame {

Q_OBJECT

public:
    
    Duplica();
    ~Duplica();
    void resizeEvent (QResizeEvent*);

private:

    QVBoxLayout * layout;
    
    QLabel * title;
    QGraphicsDropShadowEffect * effect;
    
    QLabel * pic;
    QLabel * desc;
    QLabel * atk;


};

#endif
