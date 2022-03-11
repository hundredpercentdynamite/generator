//
// Created by Macbook Pro on 28.02.2022.
//

#ifndef GENERATOR_CALENDAR_H
#define GENERATOR_CALENDAR_H

#include <QObject>

//
// BEGIN:VCALENDAR
// VERSION:2.0
// PRODID:-//Apple Inc.//macOS 12.0.1//EN
// CALSCALE:GREGORIAN
// BEGIN:VTIMEZONE
// TZID:Europe/Moscow
// BEGIN:STANDARD
// TZOFFSETFROM:+023017
// DTSTART:20010101T000000
// TZNAME:GMT+3
// TZOFFSETTO:+023017
// END:STANDARD
// END:VTIMEZONE
// BEGIN:VEVENT
// TRANSP:OPAQUE
// DTEND;TZID=Europe/Moscow:20220228T100000
// X-APPLE-TRAVEL-ADVISORY-BEHAVIOR:AUTOMATIC
// UID:27D53124-9BD3-4F45-AB04-FBF35AA282F9
// DTSTAMP:20220228T193632Z
// LOCATION:Место или видеовызов
// URL;VALUE=URI:https://ya.ru
// SEQUENCE:1
// SUMMARY:Заголовок
// LAST-MODIFIED:20220228T193618Z
// DTSTART;TZID=Europe/Moscow:20220228T090000
// CREATED:20220228T193426Z
// RRULE:FREQ=WEEKLY;INTERVAL=2;UNTIL=20220630T205959Z;BYDAY=MO;WKST=SU
// END:VEVENT
// END:VCALENDAR


class Calendar : public QObject {
Q_OBJECT
private:
  const std::vector<QString> bellList = std::vector<QString>({"bell_1", "bell_2", "bell_3", "bell_4", "bell_5"});
  const std::vector<QString> dayList = std::vector<QString>({"day_1", "day_2", "day_3", "day_4", "day_5", "day_6"});
  const std::map<QString, QString> mapDayToName = std::map<QString, QString>({
                                                                                 {"day_1", "MO"},
                                                                                 {"day_2", "TU"},
                                                                                 {"day_3", "WE"},
                                                                                 {"day_4", "TH"},
                                                                                 {"day_5", "FR"},
                                                                                 {"day_6", "SA"}
                                                                             });

public:
  void generateEvents(QJsonObject&);

};


#endif //GENERATOR_CALENDAR_H
