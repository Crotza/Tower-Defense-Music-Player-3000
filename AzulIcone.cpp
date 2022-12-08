#include "Game.h"
#include "AzulIcone.h"
#include "AzulTorre.h"

extern Game * game;

AzulIcone::AzulIcone(QGraphicsPixmapItem *parent) : QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/images/azulIcone.png"));                    // Importa o png do icone
}

void AzulIcone::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!game->build){                                               // Se estiver no modo de construcao,
        game->build = new AzulTorre();                              // Cria uma nova torre e
        game->setCursor(QString(":/images/azulTorre.png"));         // Importa o png da torre
    }
}
