#ifndef MEDIA_H
#define MEDIA_H
#include <QMovie>
#include <QLabel>
#include <QMediaPlayer>

class Media
{
public:
    Media() = default;
    static QMovie* getBackground(QLabel*, const QString&);
    static QMediaPlayer* getMusic(const QString&);
};

#endif // MEDIA_H
