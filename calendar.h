//
// Created by Macbook Pro on 28.02.2022.
//

#ifndef GENERATOR_CALENDAR_H
#define GENERATOR_CALENDAR_H

#include <QObject>
#include <utility>


class Calendar : public QObject {
Q_OBJECT
private:
  const std::vector<QString> bellList = std::vector<QString>({"bell_1", "bell_2", "bell_3", "bell_4", "bell_5"});
  const std::vector<QString> dayList = std::vector<QString>({"day_1", "day_2", "day_3", "day_4", "day_5", "day_6"});
  const std::vector<QString> mapDayToName = std::vector<QString>({"SU", "MO", "TU", "WE", "TH", "FR", "SA", "SU" });

  void createEvent(QString& date, QString& start, QString& title, QString& description);

  QString eventsDir;
public:
  explicit Calendar(QString& dir) {
    setEventsDir(dir);
  };

  void generateEvents(QJsonObject&);

  void setEventsDir(QString& dir);
};


#endif //GENERATOR_CALENDAR_H
