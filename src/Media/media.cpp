#include "media.h"
#include <QMediaPlaylist>

QMovie *Media::getBackground(QLabel *label, const QString& path) {
  auto *backgroundImg = new QMovie(path);
  label->setMovie(backgroundImg);
  label->setScaledContents(true);
  return backgroundImg;
}

QMediaPlayer *Media::getMusic(const QString& filePath) {
  auto *playlist = new QMediaPlaylist();
  playlist->addMedia(QUrl(filePath));
  playlist->setPlaybackMode(QMediaPlaylist::Loop);

  auto *music = new QMediaPlayer();
  music->setPlaylist(playlist);
  return music;
}
