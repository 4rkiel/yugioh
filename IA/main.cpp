#include <AiTrainer.h>
#include <QApplication>
#include <../inc/ai.h>

int main()
{
    QApplication a();
    AiTrainer * trainer = new AiTrainer();
    trainer->train_ai();
    delete trainer;
    return 1;
}
