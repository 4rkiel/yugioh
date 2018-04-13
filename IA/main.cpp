#include <QApplication>
#include <AiTrainer.h>

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    AiTrainer * trainer = new AiTrainer();
    trainer->train_ai();
    delete trainer;
    return 1;
}
