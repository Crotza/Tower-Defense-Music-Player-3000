#include "Game.h"
#include "LaranjaTorre.h"
#include "LaranjaIcone.h"

extern Game * game;

LaranjaIcone::LaranjaIcone(QGraphicsPixmapItem *parent) : QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/images/laranjaIcone.png"));                            // Importa o png do icone
}

void LaranjaIcone::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!game->build){                                                           // Se estiver no modo de construcao,
        game->build = new LaranjaTorre();                                       // Cria uma nova torre e
        game->setCursor(QString(":/images/laranjaTorre.png"));                  // Importa o png da torre
    }
}
