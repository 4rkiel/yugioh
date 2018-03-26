#include "../inc/extAdr.h"

ExtAdr::ExtAdr(){
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),SLOT(gotReply(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("https://api.ipify.org?format=json")));
}

void ExtAdr::gotReply(QNetworkReply* networkReply){
    networkReply->deleteLater();
    emit getIP(QHostAddress(QJsonDocument::fromJson(networkReply->readAll()).object().value("ip").toString()).toString());
}

