#include <QTextStream>
#include "logger.h"
#include <iostream>

void Logger::messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
  QTextStream out(this->logFile);
  out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");

  switch (type) {
    case QtInfoMsg:
      out << "INF ";
      break;
    case QtDebugMsg:
      out << "DBG ";
      break;
    case QtWarningMsg:
      out << "WRN ";
      break;
    case QtCriticalMsg:
      out << "CRT ";
      break;
    case QtFatalMsg:
      out << "FTL ";
      break;
  }

  out << context.category << ": " << msg << '\n';
  out.flush();
}

void Logger::setLogDir(QString& dir) {
  this->logDir = dir;
}

void Logger::setLogFile() {
  QString timestamp = QDateTime::currentDateTime().toLocalTime().toString("yyyy-MM-dd");
  QString fileName = logName + timestamp + ".log";
  QString path = this->logDir.length() > 0 ? this->logDir + "/" + fileName : fileName;
  this->logFile = new QFile(path);
  if (!this->logFile->open(QIODevice::WriteOnly)) {
    qWarning("Couldn't open journal file.");
    delete this->logFile;
    this->logFile = nullptr;
    return;
  }
}
