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

  /**
   * Записывает информацию о группах и преподавателях в файл data.json
   * @param data данные из api
   */
  void saveData(QJsonObject& data);

  /**
   * Загружает информацию о группах и преподавателях из файла data.json
   * @return QJsonObject
   */
  QJsonObject loadData();

  /**
   * Существует ли файл data.json
   * @return bool
   */
  bool exist();
};

#endif //GENERATOR_DATA_H
