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
  void loadData(int);
  void loadScheduleByTeacher(int, QString&);
  void loadScheduleByGroup(int, QString&);
  void setBase(QString&);
  bool isLoading = false;
};

#endif // APICLIENT_H
