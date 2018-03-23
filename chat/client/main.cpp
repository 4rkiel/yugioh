#include <QApplication>
#include "FenClient.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    FenClient fenetre;
    fenetre.show();

    return app.exec();
}
