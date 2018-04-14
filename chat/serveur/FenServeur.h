#ifndef HEADER_FENSERVEUR
#define HEADER_FENSERVEUR

#include <QtGui>
#include <QtNetwork>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class FenServeur : public QWidget
{
    Q_OBJECT

    public:
        FenServeur();
        void envoyerATous(const QString &message);

    private slots:
        void nouvelleConnexion();
        void donneesRecues();
        void deconnexionClient();

    private:
        QLabel *etatServeur;
        QPushButton *boutonQuitter;

        QTcpServer *serveur;
        QList<QTcpSocket *> clients;
        quint16 tailleMessage;
};

#endif
