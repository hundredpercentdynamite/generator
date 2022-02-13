#include "media.h"
#include <QMediaPlaylist>

QMovie* Media::getBackground(QLabel* label, QString& path) {
    QMovie* backgroundImg = new QMovie(path);
    label->setMovie(backgroundImg);
    label->setScaledContents(true);
    backgroundImg->start();
    return backgroundImg;
}

QMediaPlayer* Media::getMusic() {
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/music.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);

    return music;
}
