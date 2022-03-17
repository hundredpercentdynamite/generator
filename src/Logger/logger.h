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
  QFile *logFile = nullptr;
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

  /**
   * Обработчик логов
   * @param type
   * @param context
   * @param msg
   */
  void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

  /**
   * Устанавливает директорию для логов
   * @param dir
   */
  void setLogDir(QString& dir);

  /**
   * Устанавливает файл с текущим логом
   */
  void setLogFile();
};

#endif //GENERATOR_LOGGER_H
