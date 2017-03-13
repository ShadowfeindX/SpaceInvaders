#include "enemy.hxx"
#include <QTimer>
#include <QBrush>
Enemy::Enemy(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent)
{
    this->setPixmap(QPixmap(":/images/Enemy.png"));
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    audio.setNotifyInterval(500);
    audio.setMedia
            (QMediaContent
             (QUrl
              ("qrc:/sounds/bullet.wav")));
    audio.setPosition(9200);
    connect(&audio,&QMediaPlayer::positionChanged,
            [this] (qint64 position)
    {
        if (position >= 10000)
        {
//            audio.pause();
//            audio.setPosition(2000);
            audio.setMuted(true);
        }
    });
    startTimer(125);
}

void Enemy::setRandPos()
{
    this->setPos
            ( rand() % 700 + 50
              , -1 * (rand() % 600 + 50)
              );
}

void Enemy::timerEvent(QTimerEvent *)
{
    this->setY(y() + 10);
    this->setX
            (this->x() +
             rand() % 100 - 50);
    if (y() > 500 &&
        y() < 600)
    {
        emit inCollisionArea();
    }
    if (y() > 650 ||
        x() < -50 ||
        x() > 800)
    {
        this->setRandPos();
    }
}

QMediaPlayer * Enemy::getAudio()
{
    return &audio;
}
