#ifndef MEDIA_H
#define MEDIA_H

#include <QMovie>
#include <QLabel>
#include <QMediaPlayer>

class Media {
public:
  Media() = default;

  ~Media() = default;

  /**
   * Устанавливает в label фоновое изображение и возвращает его
   * @param label - лейбл
   * @param path - путь до изображения
   * @return QMovie - воспроизводимое фоновое изображение
   */
  static QMovie *getBackground(QLabel *label, const QString& path);

  /**
   * Создаёт медиаплеер с плейлистом из одного музыкального файла и возвращает его
   * @param filePath - путь до музыкального файла
   * @return QMediaPlayer
   */
  static QMediaPlayer *getMusic(const QString& filePath);
};

#endif // MEDIA_H
