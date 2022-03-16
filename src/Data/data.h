//
// Created by Macbook Pro on 16.02.2022.
//

#ifndef GENERATOR_DATA_H
#define GENERATOR_DATA_H

#include <QFile>

class Data : public QObject {
Q_OBJECT
private:
  QFile *dataFile{};

public:
  Data() = default;

  explicit Data(const QString& fileName) {
    dataFile = new QFile(fileName);
  };
  ~Data() override {
    if (this->dataFile->isOpen()) {
      this->dataFile->close();
    }
    delete this->dataFile;
  };

  void saveData(QJsonObject& data);

  QJsonObject loadData();

  bool exist();
};

#endif //GENERATOR_DATA_H
