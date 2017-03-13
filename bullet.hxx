#ifndef BULLET_HXX
#define BULLET_HXX

#include <QBrush>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QMediaPlayer>

class Bullet :
        public QObject,
        public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Bullet(QGraphicsItem * parent = 0);

signals:
    void canCollide(Bullet *);

public slots:
    void timerEvent(QTimerEvent *);
};

#endif // BULLET_HXX
