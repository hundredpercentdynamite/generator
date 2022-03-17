#include "apiclient.h"
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkDiskCache>
#include <QNetworkRequest>
#include <QNetworkReply>

ApiClient::ApiClient() {
  this->BASE = "https://login.misis.ru";
  this->manager = new QNetworkAccessManager();
  this->cache = new QNetworkDiskCache();
  this->cache->setCacheDirectory(QDir::currentPath() + "/cache");
  this->manager->setCache(this->cache);
}

ApiClient::ApiClient(QString& base) {
  this->setBase(base);
  this->manager = new QNetworkAccessManager();
  this->cache = new QNetworkDiskCache();
}

void ApiClient::setBase(QString& base) {
  this->BASE = base;
}

void ApiClient::loadData(int filiationId) {
  QUrl url(this->BASE + "method/filiation_info.get");
  QNetworkRequest request(url);
  request.setRawHeader("Accept", "application/json");
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
  QJsonObject body;
  body["filiation_id"] = filiationId;
  QJsonDocument json(body);
  QByteArray raw_body = json.toJson();

  QNetworkReply *reply = manager->post(request, raw_body);

  QObject::connect(reply, &QNetworkReply::finished, [=]() {
    if (reply->error() == QNetworkReply::NoError) {
      QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
      QJsonObject data = response["response"].toObject();
      emit dataLoaded(data);
    } else {
      QString err = reply->errorString();
      emit error(err);
    }
    reply->deleteLater();
  });
}

void ApiClient::loadScheduleByGroup(int groupId, QString& date) {
  QUrl url(this->BASE + "method/schedule.get");
  QNetworkRequest request(url);
  request.setRawHeader("Accept", "application/json");
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
  QJsonObject body;
  body["group"] = groupId;
  body["start_date"] = date;
  QJsonDocument json(body);
  QByteArray raw_body = json.toJson();

  QNetworkReply *reply = manager->post(request, raw_body);
  QObject::connect(reply, &QNetworkReply::finished, [=]() {
    if (reply->error() == QNetworkReply::NoError) {
      QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
      QJsonObject data = response.object();
      emit scheduleLoaded(data);
    } else {
      QString err = reply->errorString();
      emit error(err);
    }
    reply->deleteLater();
  });
}


void ApiClient::loadScheduleByTeacher(int teacherId, QString& mondayDate) {
  QUrl url(this->BASE + "method/schedule.get");
  QNetworkRequest request(url);
  request.setRawHeader("Accept", "application/json");
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
  QJsonObject body;
  body["teacher"] = teacherId;
  body["start_date"] = mondayDate;
  QJsonDocument json(body);
  QByteArray raw_body = json.toJson();

  QNetworkReply *reply = manager->post(request, raw_body);
  QObject::connect(reply, &QNetworkReply::finished, [=]() {
    if (reply->error() == QNetworkReply::NoError) {
      QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
      QJsonObject data = response.object();
      emit scheduleLoaded(data);
    } else {
      QString err = reply->errorString();
      emit error(err);
    }
    reply->deleteLater();
  });
}
