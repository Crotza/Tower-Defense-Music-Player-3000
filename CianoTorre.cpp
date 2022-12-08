#include <QTimer>

#include "Game.h"
#include "CianoTorre.h"
#include "Projetil.h"

extern Game * game;

CianoTorre::CianoTorre(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/cianoTorre.png"));
    QTimer *timer = new QTimer(this);                               // Relaciona um tempo de cooldown de
    connect(timer,SIGNAL(timeout()),this,SLOT(reconhecerAlvo()));   // tiro com a funcao reconhecerAlvo()
    timer->start(2000);
}

void CianoTorre::atirar()
{
    Projetil *projetil1 = new Projetil();                       // Criando o projetil
    Projetil *projetil2 = new Projetil();
    Projetil *projetil3  = new Projetil();

    projetil1->setPixmap(QPixmap(":/images/cianoBala.png"));    // Importa o png do projetil
    projetil2->setPixmap(QPixmap(":/images/cianoBala.png"));
    projetil3->setPixmap(QPixmap(":/images/cianoBala.png"));

    projetil1->setPos(x()+25,y()+25);                                 // Determina a posicao do projetil
    projetil2->setPos(x()+25,y()+25);
    projetil3->setPos(x()+25,y()+25);

    QLineF ln(QPointF(x()+25, y()+25), destATK);                // Cria uma reta entre o centro da Torre ate o ponto de ataque
    int angle = -1 * ln.angle();                                // Se for uma reta inclinada, determina a sua orientacao

    projetil1->setRotation(angle);                              // Determina o angulo o projetil
    projetil2->setRotation(angle + 10);                         // Determina o angulo do outro projetil, diminuindo, ou aumentando
    projetil3->setRotation(angle - 10);                         // seu angulo e assim resultando na dispersao dos projeteis

    game->scene->addItem(projetil1);                            // Adiciona o projetil na cena
    game->scene->addItem(projetil2);
    game->scene->addItem(projetil3);
}

void CianoTorre::reconhecerAlvo()
{
    Torre::reconhecerAlvo();
}
