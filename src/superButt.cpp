#include "../inc/superButt.h"

/******************************************************************************

    Réimplémentation des QPushButton qui permet de les actionner en pressant

    la touche Entrée (en plus de fonctionner avec la touche Espace)

******************************************************************************/

SuperButt::SuperButt(){

    setFocusPolicy(Qt::StrongFocus);
    setAutoDefault (false);
    setDefault(true);
}
