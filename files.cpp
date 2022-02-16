#include "files.h"
#include <QJsonDocument>
#include <QJsonObject>

bool Files::exist() {
  return dataFile->exists();
}

void Files::saveData(QJsonObject& data) {
  QJsonDocument jsonDocument(data);
  QByteArray json = jsonDocument.toJson();
  if (!dataFile->open(QIODevice::WriteOnly)) {
    qWarning("Couldn't open save file.");
    return;
  }
  dataFile->write(json);
  dataFile->close();
}

QJsonObject Files::loadData() {
  if (!dataFile->open(QIODevice::ReadOnly)) {
    qWarning("Couldn't open save file.");
    QJsonObject empty;
    return empty;
  }

  QByteArray data = dataFile->readAll();
  QJsonDocument jsonDocument(QJsonDocument::fromJson(data));

  return jsonDocument.object();
}