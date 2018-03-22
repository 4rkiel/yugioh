#ifndef TESTEXTERNALADDRESS_H
#define TESTEXTERNALADDRESS_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QHostAddress>
#include <QNetworkReply>

class TestExternalAddress : public QObject
{
    Q_OBJECT

public:
    TestExternalAddress();

private slots:
    void gotReply(QNetworkReply* networkReply);
};

#endif // TESTEXTERNALADDRESS_H
