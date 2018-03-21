#include "essai.h"
#include "noyau.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Essai w;
    w.show();

    return a.exec();
}
