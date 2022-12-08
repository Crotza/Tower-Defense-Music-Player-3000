#include <QTimer>

#include "Game.h"
#include "AmareloTorre.h"
#include "Projetil.h"

extern Game * game;

AmareloTorre::AmareloTorre(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/amareloTorre.png"));
    QTimer *timer = new QTimer(this);                                   // Relaciona um tempo de cooldown de
    connect(timer, SIGNAL(timeout()), this, SLOT(reconhecerAlvo()));    // tiro com a funcao reconhecerAlvo()
    timer->start(1000);
}

void AmareloTorre::atirar()
{
    Projetil *projetil = new Projetil();                        // Cria o projetil
    Projetil *projetilEspecial = new Projetil();                // Cria o projetil especial

    projetil->setPixmap(QPixmap(":/images/amareloBala.png"));           // Importa o png do projetil
    projetilEspecial->setPixmap(QPixmap(":/images/amareloBala.png"));

    projetil->setPos(x()+25, y()+25);                                   // Determina a posicao do projetil
    projetilEspecial->setPos(x()+25, y()+25);

    QLineF ln(QPointF(x()+25, y()+25), destATK);                // Cria uma reta entre o centro da Torre ate o ponto de ataque
    int angle = -1 * ln.angle();                                // Se for uma reta inclinada, determina a sua orientacao

    projetil->setRotation(angle + 5);                           // Determina o angulo o projetil
    projetilEspecial->setRotation(angle - 5);

    game->scene->addItem(projetil);                             // Adiciona o projetil na cena
    game->scene->addItem(projetilEspecial);                     // Adiciona o projetil especial na cena
}

void AmareloTorre::reconhecerAlvo()
{
    Torre::reconhecerAlvo();
}
