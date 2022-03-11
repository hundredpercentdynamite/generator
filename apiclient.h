#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkDiskCache>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>


class ApiClient : public QObject {
Q_OBJECT

signals:

  void dataLoaded(QJsonObject&);
  void scheduleLoaded(QJsonObject&);

  void error(QJsonObject&);

public:
  ApiClient();

  explicit ApiClient(const QString& base);

  void loadData(int);
  void loadScheduleByTeacher(int, QString&);
  void loadScheduleByGroup(int, QString&);

  QNetworkAccessManager *manager;
  QNetworkDiskCache *cache;
  QString BASE = "";
  bool isLoading = false;
};

#endif // APICLIENT_H
