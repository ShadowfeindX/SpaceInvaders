#include "bullet.hxx"
#include <QTimerEvent>
#include <QDebug>

Bullet::Bullet(QGraphicsItem * parent) :
    QGraphicsRectItem(0)
{
    this->setRect(0,0,2,30);
    this->setBrush
            (QBrush
             (QColor
              (0,255,0)));
}

void Bullet::timerEvent(QTimerEvent * e)
{
    if (this->scene())
    {
        this->setY(this->y()-rect().height());
        if (y() < -10*rect().height())
        {
            killTimer(e->timerId());
            this->scene()->removeItem(this);
        } emit canCollide(this);
    } else killTimer(e->timerId());
}
