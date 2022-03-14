//
// Created by Macbook Pro on 16.02.2022.
//

#ifndef GENERATOR_DATA_H
#define GENERATOR_DATA_H

#include <QFile>

class Data : public QObject {
Q_OBJECT

public:
  Data() = default;

  explicit Data(const QString& fileName) {
    dataFile = new QFile(fileName);
  }

  void saveData(QJsonObject& data);

  QJsonObject loadData();

  bool exist();

private:
  QFile *dataFile{};
};

#endif //GENERATOR_DATA_H
