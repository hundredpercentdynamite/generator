//
// Created by Macbook Pro on 16.02.2022.
//

#ifndef GENERATOR_FILES_H
#define GENERATOR_FILES_H

#include <QFile>

class Files : public QObject {
Q_OBJECT

public:
  Files() = default;

  explicit Files(const QString& fileName) {
    dataFile = new QFile(fileName);
  }

  void saveData(QJsonObject& data);

  QJsonObject loadData();

  bool exist();

private:
  QFile *dataFile;
};

#endif //GENERATOR_FILES_H
