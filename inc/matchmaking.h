#ifndef MATCHMAKING_H
#define MATCHMAKING_H

#include <QObject>
#include <QString>
#include <QShortcut>
#include <sstream>
#include <QUdpSocket>
#include <iostream>

class Matchmaking : public QObject
{
    Q_OBJECT
public:
    Matchmaking(QObject *parent = 0);
    ~Matchmaking();

signals:
    void sendIP(QString);
    void createHost(QString);

public slots:
    void readyRead();

private:
    QUdpSocket *socket;
    QHostAddress* adresse_bind;
};

#endif // MATCHMAKING_H
