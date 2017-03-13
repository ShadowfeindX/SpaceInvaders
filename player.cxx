#include "player.hxx"
#include <QDebug>

Player::Player(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent)
{
    this->ammo = 10;
    this->health = 10;
    audio.setNotifyInterval(500);
    audio.setMedia
            (QMediaContent
             (QUrl
              ("qrc:/sounds/bullet.wav")));
    connect(&audio,&QMediaPlayer::positionChanged,
            [this] (qint64 position)
    {
        if (position >= 1500)
        {
            audio.setMuted(true);
        }
    });
    this->setPixmap(QPixmap(":/images/Player.png"));
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    this->setAcceptHoverEvents(true);
    bullets.reserve(ammo);
    for (int i = 0; i < ammo; i++)
    {
        Bullet * bullet = new Bullet(this);
        connect(bullet, &Bullet::canCollide
                ,this, &Player::bulletCollide);
        bullets.push_back(bullet);
    }
}

void Player::mouseMoveEvent(QGraphicsSceneMouseEvent * e)
{
    if (e->scenePos().x() > 0 &&
        e->scenePos().x() < 800)
    {
        this->setX
                (e->scenePos().x() -
                 this->pixmap().width() / 2
                 );
    }
}

void Player::mousePressEvent(QGraphicsSceneMouseEvent * e)
{
    if (e->button() == 1 && ammo)
    {
        Bullet * bullet = bullets.at(ammo-1);
        bullet->setPos
                (e->scenePos().x()-5
                 ,this->pos().y()-10);
        this->scene()->addItem(bullet);
        bullet->startTimer(20);
        if(audio.state() == 1)
        {
            audio.setMuted(false);
            audio.stop();
        } audio.play();
        emit fire(--ammo);
    } else if (e->button() == 2)
    {
        int clip = 0;
        for (int i = bullets.length()-1; i > ammo-1; i--)
        {
            if (bullets.at(i)->scene())
            {
                continue;
            }
            else
            {
                clip++;
            }
        }
        audio.stop();
        emit reload(ammo += clip);
    }
}

int Player::getAmmo() const
{
    return ammo;
}

void Player::setAmmo(int value)
{
    ammo = value;
}

int Player::getHealth() const
{
    return health;
}

void Player::setHealth(int value)
{
    health = value;
}

int Player::decreaseHealth()
{
    emit hit(--health);
    if (health)
    {
        return health;
    }
    exit(health);
}
