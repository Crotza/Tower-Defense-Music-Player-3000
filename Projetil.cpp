#include <QGraphicsItem>
#include <QList>
#include <QPixmap>
#include <QTimer>
#include <qmath.h>

#include "Game.h"
#include "Projetil.h"
#include "Inimigo.h"
#include "Chefao.h"

#include <QDebug>

extern Game * game;

Projetil::Projetil(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/bala.png"));                // Importa o png generico do projetil

    QTimer *moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(mover()));     // Conecta o metodo de 'mover' com uma funcao de tempo, para loop de movimentacao
    moveTimer->start(50);

    maxRange = 100;             // Distancia de ataque maxima
    distPercorrida = 0;         // Distancia percorrida pelo projetil
}

Projetil::~Projetil(){
    qInfo() << "Projetil deletado";
}
void Projetil::mover()
{
    if(this->pos().x() >= 800 || this->pos().y() >= 600){   // Caso o projétil saia da cena, deletá-lo
        delete this;
    }
    //colisao com inimigo
    QList<QGraphicsItem *> colliding_items = collidingItems();              // Abstrai uma lista de itens colidindo com o projetil
    for(size_t i = 0, n = colliding_items.size(); i < n; i++){              // Para cada item dessa lista,
        Chefao *chefao = dynamic_cast<Chefao *>(colliding_items[i]);            // Compara se a colisao esta sendo feita com um tipo 'Chefao'
        Inimigo *inimigo = dynamic_cast<Inimigo *>(colliding_items[i]);         // Compara se a colisao esta sendo feita com um tipo 'Inimigo'

        if(chefao){                                                            // Se e Chefao,
            game->score->aumentaScore();                                            // Aumenta o score quando acertar o Chefao
            game->dinheiro->aumentaDinheiro(1500);                                  // Aumenta o dinheiro quando eliminar
            chefao->diminuirVida();                                        // Diminui a sua vida

            if(chefao->getVida() <= 0){
                scene()->removeItem(colliding_items[i]);                        // Remove o Chefao da cena, se estiver sem vida
                scene()->removeItem(this);
                delete colliding_items[i];                                      // Deleta sua alocacao
                delete this;
                return;
            }

            scene()->removeItem(this);                                          // Remove o projetil da cena
            delete this;                                                        // Deleta sua alocacao
            return;
        }

        if(inimigo){                                                            // Se e inimigo,
            game->score->aumentaScore();                                            // Aumenta o score quando eliminar inimigo
            game->dinheiro->aumentaDinheiro(10);                                    // Aumenta o dinheiro quando eliminar o inimigo

            scene()->removeItem(colliding_items[i]);                                // Remove o inimigo da cena
            scene()->removeItem(this);                                              // Remove o projetil da cena

            delete colliding_items[i];                                      // Deleta sua alocacao
            delete this;
            return;
        }
    }

    int STEPSIZE = 30;                                          // Para mover na direcao certa, caminha nesse tamanho determinado em 'STEPSIZE'
    double theta = rotation();                                  // E utliizia esse metodo 'rotation()' para entao calcular o respectivo angulo:

    double dy = STEPSIZE * qSin(qDegreesToRadians(theta));      // Calcula a distancia vertical por meio do seno do angulo e o seu tamanho
    double dx = STEPSIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);                        // Define sua posicao com os valores calculados acima
}

double Projetil::getMaxRange(){
    return maxRange;
}

double Projetil::getDistPercorrida(){
    return distPercorrida;
}

void Projetil::setMaxRange(double range){
    maxRange = range;
}

void Projetil::setDistPercorrida(double dist){
    distPercorrida = dist;
}
