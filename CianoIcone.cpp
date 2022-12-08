#include "Game.h"
#include "CianoTorre.h"
#include "CianoIcone.h"

extern Game * game;

CianoIcone::CianoIcone(QGraphicsPixmapItem *parent) : QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/images/cianoIcone.png"));                               // Importa o png do icone
}

void CianoIcone::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!game->build){                                                           // Se estiver no modo de construcao,
        game->build = new CianoTorre();                                         // Cria uma nova torre e
        game->setCursor(QString(":/images/cianoTorre.png"));                    // Importa o png da torre
    }
}
