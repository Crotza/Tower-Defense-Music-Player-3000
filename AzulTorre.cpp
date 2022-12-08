#include <QTimer>

#include "Game.h"
#include "AzulTorre.h"
#include "Projetil.h"

extern Game * game;

AzulTorre::AzulTorre(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/azulTorre.png"));
    QTimer *timer = new QTimer(this);                                   // Relaciona um tempo de cooldown de
    connect(timer, SIGNAL(timeout()), this, SLOT(reconhecerAlvo()));    // tiro com a funcao reconhecerAlvo()
    timer->start(1000);
}

void AzulTorre::atirar()
{
    Projetil *projetil = new Projetil();                        // Cria o projetil

    projetil->setPixmap(QPixmap(":/images/azulBala.png"));      // Importa o png do projetil

    projetil->setPos(x()+25, y()+25);                           // Determina a posicao do projetil

    QLineF ln(QPointF(x()+25, y()+25), destATK);                // Cria uma reta entre o centro da Torre ate o ponto de ataque
    int angle = -1 * ln.angle();                                // Se for uma reta inclinada, determina a sua orientacao

    projetil->setRotation(angle);                               // Determina o angulo o projetil

    game->scene->addItem(projetil);                             // Adiciona o projetil na cena
}

void AzulTorre::reconhecerAlvo()
{
    Torre::reconhecerAlvo();
}
