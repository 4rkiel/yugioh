#ifndef TESTEXTERNALADDRESS_H
#define TESTEXTERNALADDRESS_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QHostAddress>
#include <QNetworkReply>
#include <QString>

class ExtAdr : public QObject
{
    Q_OBJECT

public:
    ExtAdr();

signals:
	void getIP(QString str);

private slots:
    void gotReply(QNetworkReply* networkReply);
};

#endif // TESTEXTERNALADDRESS_H
