#include "apiclient.h"
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QObject>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkDiskCache>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

ApiClient::ApiClient()
{
    this->BASE = "https://login.misis.ru";
    this->manager = new QNetworkAccessManager();
    this->cache = new QNetworkDiskCache();
    this->cache->setCacheDirectory(QDir::currentPath() + "/cache");
    this->manager->setCache(this->cache);
}

ApiClient::ApiClient(const QString& base)
{
    this->BASE = base;
    this->manager = new QNetworkAccessManager();
    this->cache = new QNetworkDiskCache();
}

void ApiClient::loadGroups(int filiation) const
{
    QUrl url(this->BASE + "method/filiation_info.get");
    QNetworkRequest request(url);
    request.setRawHeader("Accept", "application/json");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
    QJsonObject body;
    body["filiation_id"] = filiation;
    QJsonDocument json(body);
    QByteArray raw_body = json.toJson();

    QNetworkReply *reply = manager->post(request, raw_body);

    QObject::connect(reply, &QNetworkReply::finished, [=](){
        if(reply->error() == QNetworkReply::NoError){
            QString contents = QString::fromUtf8(reply->readAll());
            qDebug() << contents;
        }
        else{
            QString err = reply->errorString();
            qDebug() << err;
        }
        reply->deleteLater();
    });
}
