#ifndef PLAYER_HXX
#define PLAYER_HXX

#include <bullet.hxx>

#include <QGraphicsSceneEvent>
#include <QKeyEvent>
//#include <QMediaPlayer>


class Player :
        public QObject,
        public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ~Player() {}
    explicit Player(QGraphicsItem *parent = 0);
    int getHealth() const;
    void setHealth(int value);
    int getAmmo() const;
    void setAmmo(int value);

signals:
    void hit(int);
    void fire(int);
    void reload(int);
    void bulletCollide(Bullet *);

public slots:
    int decreaseHealth();
    void mouseMoveEvent(QGraphicsSceneMouseEvent * e);
    void mousePressEvent(QGraphicsSceneMouseEvent *);

private:
    int ammo;
    int health;
    QMediaPlayer audio;
    QVector<Bullet *> bullets;
};

#endif // PLAYER_HXX
