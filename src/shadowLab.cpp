#include "../inc/shadowLab.h"

/******************************************************************************

	Réimplémentation des QLabel

	Avec ombre

******************************************************************************/

ShadowLab::ShadowLab (){

    setAlignment(Qt::AlignCenter);

    // shadow

    effect = new QGraphicsDropShadowEffect(this);
    effect -> setBlurRadius(5);
    effect -> setYOffset(5);
    effect -> setXOffset(0);
    effect -> setColor(QColor(0,0,0,150));

    setGraphicsEffect(effect);

}



ShadowLab::~ShadowLab (){

    delete effect;
}

