#include <QApplication>
#include <AiTrainer.h>

int main()
{
    QApplication a();
    AiTrainer * trainer = new AiTrainer();
    trainer->train_ai();
    delete trainer;
    return 1;
}
