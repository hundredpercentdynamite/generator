//
// Created by Macbook Pro on 08.03.2022.
//
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QStringList>
#include <QFile>
#include <QUuid>
#include <QDateTime>
#include <utility>
#include <QDesktopServices>
#include "calendar.h"
#include "vector"

QString toIcsDate(QDateTime& date) {
  QStringList dateAndTime = date.toString(Qt::ISODate).split("T");
  QStringList dateList = dateAndTime[0].split("-");
  QStringList timeList = dateAndTime[1].split(":");
  QString ics = dateList.join("") + "T" + timeList.join("");

  return ics;
}

QString toIsoDate(QString& date, QString& time) {
  QStringList startDate = date.split(".");
  QStringList timeList = time.split(":");
  QString iso = "20" + startDate[2] + "-" + startDate[1] + "-" + startDate[0] + "T" + time + ":" + "00";

  return iso;
}

QString getUntil(QDateTime& date) {
  QDate qDate = date.date();
  int month = qDate.month();
  QDate until;
  QTime endOfDay(23, 59, 0);
  if (month > 8) {
    until = QDate(qDate.year(), 12, 31);
  } else {
    until = QDate(qDate.year(), 06, 15);
  }
  QDateTime dateTime(until, endOfDay);
  return toIcsDate(dateTime);
}

void Calendar::setEventsDir(QString& dir) {
  this->eventsDir = dir;
}

void Calendar::generateEvents(QJsonObject& data) {
  QJsonObject schedule = data["schedule"].toObject();
  QJsonObject schedule_header = data["schedule_header"].toObject();
  for (const QString& currBell: this->bellList) {
    QJsonObject bell = schedule.value(currBell).toObject();
    QString start = bell["header"].toObject().value("start_lesson").toString();
    for (const QString& currDay: this->dayList) {
      QString date = schedule_header[currDay].toObject().value("date").toString();
      QJsonArray lessons = bell[currDay].toObject().value("lessons").toArray();
      if (!lessons.isEmpty()) {
        for (QJsonValue currLesson: lessons) {
          QString subject_name = currLesson.toObject().value("subject_name").toString();
          QString room_name = currLesson.toObject().value("room_name").toString();
          QString type = currLesson.toObject().value("type").toString();
          QString teacher = currLesson.toObject().value("teachers").toArray().at(0).toObject().value("name").toString();
          QString title = subject_name + ' ' + room_name;
          QString description = type + " / " + teacher;
          this->createEvent(date, start, title, description);
        }
      }
    }
  }
  QDesktopServices::openUrl(QUrl::fromLocalFile(this->eventsDir.length() > 0 ? this->eventsDir : "./"));
}

void Calendar::createEvent(QString& date, QString& start, QString& title, QString& description) {
  QString uuid = QUuid::createUuid().toString(QUuid::WithoutBraces);
  QString name = title + "_" + date + "_" + uuid + ".ics";
  QString fileName = this->eventsDir.length() > 0 ? this->eventsDir + "/" + name : name;
  auto *event = new QFile(fileName);

  if (!event->open(QIODevice::WriteOnly)) {
    qWarning("Couldn't open event file.");
    return;
  }
  QString isoStartDate = toIsoDate(date, start);
  QDateTime qStartDate = QDateTime::fromString(isoStartDate, Qt::ISODate);
  QDateTime qEndDate = qStartDate.addSecs(5700);
  QString icsStartDate = toIcsDate(qStartDate);
  QString icsEndDate = toIcsDate(qEndDate);
  QDateTime timestamp = QDateTime::currentDateTime();
  QString icsTimestamp = toIcsDate(timestamp) + "Z";
  QString until = getUntil(timestamp);
  QString dayOfWeak = mapDayToName[qStartDate.date().dayOfWeek()];

  QTextStream outputStream(event);
  outputStream << "BEGIN:VCALENDAR" << '\n';
  outputStream << "VERSION:2.0" << '\n';
  outputStream << "PRODID:-//Kleymenov.//Generator//EN" << '\n';
  outputStream << "CALSCALE:GREGORIAN" << '\n';
  outputStream << "BEGIN:VTIMEZONE" << '\n';
  outputStream << "TZID:Europe/Moscow" << '\n';
  outputStream << "BEGIN:STANDARD" << '\n';
  outputStream << "TZOFFSETFROM:+023017" << '\n';
  outputStream << "DTSTART:20010101T000000" << '\n';
  outputStream << "TZNAME:GMT+3" << '\n';
  outputStream << "TZOFFSETTO:+023017" << '\n';
  outputStream << "END:STANDARD" << '\n';
  outputStream << "END:VTIMEZONE" << '\n';
  outputStream << "BEGIN:VEVENT" << '\n';
  outputStream << "TRANSP:OPAQUE" << '\n';
  outputStream << "DTEND;TZID=Europe/Moscow:" << icsEndDate << '\n';
  outputStream << "X-APPLE-TRAVEL-ADVISORY-BEHAVIOR:AUTOMATIC" << '\n';
  outputStream << "UID:" << uuid.toUpper() << '\n';
  outputStream << "DTSTAMP:" << icsTimestamp << '\n';
  outputStream << "LOCATION:" << description << '\n';
  outputStream << "SEQUENCE:1" << '\n';
  outputStream << "SUMMARY:" << title << '\n';
  outputStream << "LAST-MODIFIED:" << icsTimestamp << '\n';
  outputStream << "DTSTART;TZID=Europe/Moscow:" << icsStartDate << '\n';
  outputStream << "CREATED:" << icsTimestamp << '\n';
  outputStream << "RRULE:FREQ=WEEKLY;INTERVAL=2;UNTIL=" << until << ";BYDAY=" << dayOfWeak << ";WKST=SU" << '\n';
  outputStream << "END:VEVENT" << '\n';
  outputStream << "END:VCALENDAR";
  outputStream.flush();
  event->close();
};