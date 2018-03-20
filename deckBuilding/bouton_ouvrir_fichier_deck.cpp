#include "bouton_ouvrir_fichier_deck.h"

bouton_ouvrir_fichier_deck::bouton_ouvrir_fichier_deck()
{

}

void bouton_ouvrir_fichier_deck::selecteur()
{
    using namespace std;
    QString file = QFileDialog::getOpenFileName(this, tr("Select a file to open..."), QDir::homePath(), "pedehef (*.pdf)");
    qDebug() << (file);


    QFile myfile(file);
    if(!myfile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", myfile.errorString());
    }



    myfile.close();
}

