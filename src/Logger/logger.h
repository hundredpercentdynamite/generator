#ifndef GENERATOR_LOGGER_H
#define GENERATOR_LOGGER_H
#include <QObject>
#include <QtMessageHandler>
#include <QString>
#include <QFile>
#include <QDateTime>

class Logger : public QObject {
  Q_OBJECT
private:
  QString logDir;
  QFile* logFile = nullptr;
  const QString logName = "log-";
public:
  explicit Logger(QString& dir) {
    setLogDir(dir);
    setLogFile();
  };
  ~Logger() override {
    this->logFile->close();
    delete this->logFile;
  }
  void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
  void setLogDir(QString& dir);
  void setLogFile();
};
#endif //GENERATOR_LOGGER_H
