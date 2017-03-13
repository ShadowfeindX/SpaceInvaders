#include "game.hxx"
#include <QDebug>

Game::Game(QWidget *parent)
    : QGraphicsView(parent)
{
    score = 0;
    this->setFixedSize(800,600);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->scene = new QGraphicsScene(0,0,width(),height(),this);
    this->player = new Player;
    this->enemies.reserve(20);
    for (int i = 0; i < 20; ++i)
    {
        Enemy * e = new Enemy;
        e->setRandPos();
        this->enemies.push_back(e);
        this->scene->addItem(e);
    }
    QGraphicsSimpleTextItem * scoreText =
            this->scene->addSimpleText
            (QString("Score: ") +
             QString::number(0)
             ,QFont("times",16));
    scoreText->setPos(0,0);
    scoreText->topLevelItem();
    QGraphicsSimpleTextItem * healthText =
            this->scene->addSimpleText
            (QString("Health: ") +
             QString::number(10)
             ,QFont("times",16));
    healthText->setPos(0,50);
    QGraphicsSimpleTextItem * ammoText =
            this->scene->addSimpleText
            (QString("Ammo: ") +
             QString::number(10)
             ,QFont("times", 16));
    ammoText->setPos(0,100);
    auto updateAmmo = [ammoText] (int ammo)
    {
        ammoText->setText
                (QString("Ammo: ") +
                 QString::number(ammo));
    };
    for (Enemy * e : enemies)
    {
        connect(e, &Enemy::inCollisionArea,
                [e, this] ()
        {
            if (e->collidesWithItem(player))
            {
                player->decreaseHealth();
                e->setRandPos();
            }
        });
        connect(e, &Enemy::hit,
                [e, scoreText, this] ()
        {
            scoreText->setText
                    (QString("Score: ") +
                     QString::number(score));
        });
    }
    connect(player, &Player::fire, updateAmmo);
    connect(player, &Player::reload, updateAmmo);
    connect(player, &Player::hit,
            [healthText] (int health)
    {
        healthText->setText
                (QString("Health: ") +
                 QString::number(health));
    });
    connect(player, &Player::bulletCollide,
            [this] (Bullet * bullet)
    {
        for (Enemy * enemy : enemies)
        {
            if (bullet->collidesWithItem(enemy))
            {
                score++;
                enemy->setRandPos();
                scene->removeItem(bullet);
                if (enemy->getAudio()->state() == 1)
                {
                    enemy->getAudio()->pause();
                    enemy->getAudio()->setPosition(9200);
                    enemy->getAudio()->setMuted(false);
                } enemy->getAudio()->play();
                emit enemy->hit();
                break;
            }
        }
    });
    this->player->setPos(375,550);
    this->scene->addItem(player);
    this->player->grabMouse();
    this->setScene(scene);
}

Game::~Game()
{
}
