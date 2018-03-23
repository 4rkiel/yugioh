#include "TestExternalAddress.h"
#include "qdebug.h"

TestExternalAddress::TestExternalAddress()
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),SLOT(gotReply(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("https://api.ipify.org?format=json")));
}

void TestExternalAddress::gotReply(QNetworkReply* networkReply)
{
    networkReply->deleteLater();
    qDebug() <<  QHostAddress(QJsonDocument::fromJson(networkReply->readAll()).object().value("ip").toString());
}
