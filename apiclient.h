#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkDiskCache>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>



class ApiClient: public QObject
{
    Q_OBJECT
signals:
    void dataLoaded();
    void error();
public:
    ApiClient();
    explicit ApiClient(const QString& base);
    ~ApiClient() = default;

    void loadData(int);

    QNetworkAccessManager* manager;
    QNetworkDiskCache* cache;
    QString BASE = "";
    bool isLoading = false;
    QJsonObject data;
};

#endif // APICLIENT_H
