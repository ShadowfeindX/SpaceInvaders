#ifndef ENEMY_HXX
#define ENEMY_HXX

#include <QObject>
#include <QMediaPlayer>
#include <QGraphicsRectItem>

class Enemy :
        public QObject,
        public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Enemy(QGraphicsItem *parent = 0);

    QMediaPlayer * getAudio();

signals:
    void inCollisionArea();
    void hit();

public slots:
    void setRandPos();
    void timerEvent(QTimerEvent *);

private:
    QMediaPlayer audio;
};

#endif // ENEMY_HXX
