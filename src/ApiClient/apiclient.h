#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkDiskCache>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>


class ApiClient : public QObject {
Q_OBJECT

signals:

  void dataLoaded(QJsonObject&);

  void scheduleLoaded(QJsonObject&);

  void error(QString&);

private:
  QString BASE = "";
  QNetworkAccessManager *manager;
  QNetworkDiskCache *cache;
public:
  ApiClient();

  explicit ApiClient(QString& base);

  ~ApiClient() override {
    delete this->manager;
    delete this->cache;
  };

  /**
   * Загрузка информации о группах и преподавателях
   * @param filiationId - id филиала
   */
  void loadData(int filiationId);

  /**
   * Загрузка расписания для преподавателя
   * @param teacherId - id преподавателя
   * @param mondayDate - дата ближайшего понедельника
   */
  void loadScheduleByTeacher(int teacherId, QString& mondayDate);

  /**
   * Загрузка расписания для группы
   * @param groupId - id группы
   * @param mondayDate - дата ближайшего понедельника
   */
  void loadScheduleByGroup(int groupId, QString& mondayDate);

  /**
   * Установка корня api
   * @param base - корень api
   */
  void setBase(QString& base);
};

#endif // APICLIENT_H
