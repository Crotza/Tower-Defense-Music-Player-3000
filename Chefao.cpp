#include <QPixmap>

#include "Game.h"
#include "Chefao.h"

#include <QDebug>

extern Game * game;

Chefao::Chefao(QList<QPointF> pontosCaminho, QGraphicsItem *parent) : Inimigo(pontosCaminho, parent)
{
    vida = 100;                                         // Inicializa a vida do Chefao
    setPixmap(QPixmap(":/images/chefao.png"));          // Importa o png do Chefao
}

Chefao::~Chefao()
{
    qInfo() << "CHEFAO DERROTADO!";
}

void Chefao::diminuirVida()
{
    vida = vida - 10;
}

int Chefao::getVida()
{
    return vida;
}
