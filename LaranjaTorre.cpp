#include <QTimer>

#include "Game.h"
#include "LaranjaTorre.h"
#include "Projetil.h"

extern Game * game;

LaranjaTorre::LaranjaTorre(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/laranjaTorre.png"));
    QTimer *timer = new QTimer(this);                               // Relaciona um tempo de cooldown de
    connect(timer,SIGNAL(timeout()),this,SLOT(reconhecerAlvo()));   // tiro com a funcao reconhecerAlvo()
    timer->start(3000);
}

void LaranjaTorre::atirar()
{
    Projetil *projetil1 = new Projetil();                           // Criando o projetil
    Projetil *projetil2 = new Projetil();
    Projetil *projetil3 = new Projetil();
    Projetil *projetil4 = new Projetil();

    projetil1->setPixmap(QPixmap(":/images/laranjaBala.png"));      // Importa o png do projetil
    projetil2->setPixmap(QPixmap(":/images/laranjaBala.png"));
    projetil3->setPixmap(QPixmap(":/images/laranjaBala.png"));
    projetil4->setPixmap(QPixmap(":/images/laranjaBala.png"));

    projetil1->setPos(x()+25,y()+25);                               // Determina a posicao do projetil
    projetil2->setPos(x()+25,y()+25);
    projetil3->setPos(x()+25,y()+25);
    projetil4->setPos(x()+25,y()+25);

    QLineF ln(QPointF(x()+25, y()+25), destATK);                // Cria uma reta entre o centro da Torre ate o ponto de ataque
    int angle = -1 * ln.angle();                                // Se for uma reta inclinada, determina a sua orientacao

    projetil1->setRotation(angle);                              // Determina o angulo o projetil
    projetil2->setRotation(angle + 90);                         // Determina o angulo do outro projetil, diminuindo, ou aumentando
    projetil3->setRotation(angle - 90);                         // seu angulo e assim resultando na dispersao dos projeteis
    projetil3->setRotation(angle + 180);

    game->scene->addItem(projetil1);                            // Adiciona o projetil na cena
    game->scene->addItem(projetil2);
    game->scene->addItem(projetil3);
    game->scene->addItem(projetil4);
}

void LaranjaTorre::reconhecerAlvo()
{
    Torre::reconhecerAlvo();
}
