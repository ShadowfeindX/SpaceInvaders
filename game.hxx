#ifndef GAME_HXX
#define GAME_HXX

#include <enemy.hxx>
#include <player.hxx>

#include <QGraphicsView>
#include <QGraphicsScene>

class Game : public QGraphicsView
{
    Q_OBJECT

public:
    Game(QWidget *parent = 0);
    ~Game();

public slots:

private:
    int score;
    QGraphicsScene * scene;
    Player * player;
    QVector<Enemy *> enemies;
};

#endif // GAME_HXX
