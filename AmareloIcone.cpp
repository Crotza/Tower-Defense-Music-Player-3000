#include "Game.h"
#include "AmareloIcone.h"
#include "AmareloTorre.h"

extern Game * game;

AmareloIcone::AmareloIcone(QGraphicsPixmapItem *parent) : QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/images/amareloIcone.png"));                    // Importa o png do icone
}

void AmareloIcone::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!game->build){                                               // Se estiver no modo de construcao,
        game->build = new AmareloTorre();                              // Cria uma nova torre e
        game->setCursor(QString(":/images/amareloTorre.png"));         // Importa o png da torre
    }
}
