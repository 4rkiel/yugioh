#ifndef SHADOWLAB
#define SHADOWLAB

#include <QGraphicsDropShadowEffect>
#include <QColor>

#include <QLabel>


class ShadowLab : public QLabel {

Q_OBJECT

public: 
    ShadowLab();
    ~ShadowLab();

private:
    QGraphicsDropShadowEffect * effect;

};


#endif
