/*#include "essai.h"
#include "noyau.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

       QNetworkAccessManager networkManager;

       QUrl url("https://api.ipify.org");
       //the query used to add the parameter "format=json" to the request
       QUrlQuery query;
       query.addQueryItem("format", "json");
       //set the query on the url
       url.setQuery(query);

       //make a *get* request using the above url
       QNetworkReply* reply = networkManager.get(QNetworkRequest(url));

       QObject::connect(reply, &QNetworkReply::finished,
                        [&](){
           if(reply->error() != QNetworkReply::NoError) {
               //failure
               qDebug() << "error: " << reply->error();
           } else { //success
               //parse the json reply to extract the IP address
               QJsonObject jsonObject= QJsonDocument::fromJson(reply->readAll()).object();
               QHostAddress ip(jsonObject["ip"].toString());
               //do whatever you want with the ip
               qDebug() << "external ip: " << ip;
           }
           //delete reply later to prevent memory leak
           reply->deleteLater();
           a.quit();
       });
       return a.exec();

}*/

#include "essai.h"
#include "noyau.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Essai w;
    w.show();

    return a.exec();
}
