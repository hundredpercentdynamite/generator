#include "data.h"
#include <QJsonDocument>
#include <QJsonObject>

bool Data::exist() {
  return dataFile->exists();
}

void Data::saveData(QJsonObject& data) {
  QJsonDocument jsonDocument(data);
  QByteArray json = jsonDocument.toJson();
  if (!dataFile->open(QIODevice::WriteOnly)) {
    qWarning("Couldn't open save file.");
    return;
  }
  dataFile->write(json);
  dataFile->close();
}

QJsonObject Data::loadData() {
  if (!dataFile->open(QIODevice::ReadOnly)) {
    qWarning("Couldn't open save file.");
    QJsonObject emptyObj;
    return emptyObj;
  }

  QByteArray data = dataFile->readAll();
  QJsonDocument jsonDocument(QJsonDocument::fromJson(data));

  return jsonDocument.object();
}