#include <QCoreApplication>
#include "./monserveur.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MonServeur s;

    return a.exec();
}

