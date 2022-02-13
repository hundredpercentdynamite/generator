#ifndef MEDIA_H
#define MEDIA_H
#include <QMovie>
#include <QLabel>
#include <QMediaPlayer>

class Media
{
public:
    Media() = default;
    static QMovie* getBackground(QLabel*, QString&);
    static QMediaPlayer* getMusic();
};

#endif // MEDIA_H
