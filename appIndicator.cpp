#include "appIndicator.h"

AppIndicator::AppIndicator (){

    setAlignment(Qt::AlignCenter);

    // shadow

    effect = new QGraphicsDropShadowEffect(this);
    effect -> setBlurRadius(5);
    effect -> setYOffset(5);
    effect -> setXOffset(0);
    effect -> setColor(QColor(0,0,0,150));

    setGraphicsEffect(effect);

}



AppIndicator::~AppIndicator (){

    delete effect;
}

