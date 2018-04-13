#ifndef MONSERVEUR_H
#define MONSERVEUR_H
#include <QApplication>
#include <QFrame>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QGraphicsDropShadowEffect>

#include <QPushButton>
#include <QString>
#include <QShortcut>
#include <sstream>
#include <QUdpSocket>
#include <iostream>
#include <QHostInfo>
#include <QString>

#include <QObject>

class MonServeur : public QObject
{
    Q_OBJECT
public:
    explicit MonServeur(QObject *parent = 0);
    ~MonServeur();
    QHostAddress* adresse_hote;
    quint16* port_hote;
private:
    QUdpSocket* socket;
    QHostAddress* adresse_serveur;

signals:

public slots:
    void readyRead();
};

#endif // MONSERVEUR_H
