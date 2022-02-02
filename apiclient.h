#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkDiskCache>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>



class ApiClient
{
public:
    ApiClient();
    explicit ApiClient(const QString& base);
    ~ApiClient() = default;

    void loadGroups(int) const;


    QNetworkAccessManager* manager;
    QNetworkDiskCache* cache;
    QString BASE = "";
};

#endif // APICLIENT_H
