//
// Created by Macbook Pro on 08.03.2022.
//
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QStringList>
#include "calendar.h"
#include "vector"

QString formatStartDate (QString& date, QString& time) {
  QStringList startDate = date.split(".");
  QStringList timeList = time.split(":");
  QString start = "20" + date[2] + date[1] + date[0] + "T" + timeList[0] + timeList[1] + "00";

  return start;
}


void Calendar::generateEvents(QJsonObject& data) {
  QJsonObject schedule = data["schedule"].toObject();
  QJsonObject schedule_header = data["schedule_header"].toObject();
  for(QString currBell : this->bellList) {
    QJsonObject bell = schedule.value(currBell).toObject();
    QString start = bell["header"].toObject().value("start_lesson").toString();
    QString end = bell["header"].toObject().value("end_lesson").toString();
    for(QString currDay : this->dayList) {
        QString date = schedule_header[currDay].toObject().value("date").toString();
        QJsonArray lessons = bell[currDay].toObject().value("lessons").toArray();
        if (!lessons.isEmpty()) {
          for(QJsonValue currLesson : lessons) {
            QString subject_name = currLesson.toObject().value("subject_name").toString();
            QString room_name = currLesson.toObject().value("room_name").toString();
            QString type = currLesson.toObject().value("type").toString();
            QString teacher = currLesson.toObject().value("teachers").toArray().at(0).toObject().value("name").toString();
            QString startDate = formatStartDate(date, start);
//              const event = {
//                start: startDate,
//                  startOutputType:"local",
//                    duration: { hours: 1, minutes: 35 },
//                title: subject_name + ' ' + room_name,
//                  description: type + '\n' + teachers[0].name,
//                    busyStatus: 'BUSY',
//                    recurrenceRule: `FREQ=WEEKLY;BYDAY=${mapDayToName[currDay]};INTERVAL=2;UNTIL=20211231T210000Z`
//              }
//              ics.createEvent(event, (error, value) => {
//                fs.writeFileSync(`${__dirname}/lower/${subject_name}_${type}_${date}_${start}.ics`, value);
//              });
          })
        }
    }
  }
}