#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include "Inimigo.h"
#include "Chefao.h"
#include "Game.h"

#include <QDebug>

extern Game * game;

Inimigo::Inimigo(QList<QPointF> pontosCaminho, QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/inimigo.png"));             // Importa o png do inimigo

    pontos = pontosCaminho;                     // Determinam os pontos do caminho a ser percorrido
    pontoIndex = 0;                             // Index de cada ponto
    destino = pontos[0];                        // O destino vai ser o ponto respectivo
    rotacionarPonto(destino);                   // Rotaciona a orientacao do inimigo para o proximo ponto da lista

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moverFrente()));       // Conecta o metodo de 'moverFrente' com uma funcao de tempo, para loop
    timer->start(50);
}

Inimigo::~Inimigo(){
    qInfo() << "Inimigo deletado";
}

void Inimigo::rotacionarPonto(QPointF p)
{
    QLineF ln(pos(), p);                        // Rotaciona a orientacao do inimigo para o proximo ponto da lista, passado como argumento
    setRotation(-1 * ln.angle());               // Possui essa multiplicacao por -1 para ser calculado no sentido horario
}

void Inimigo::moverFrente()
{
    QLineF ln(pos(), destino);                  // Cria uma linha entre a posicao atual e o destino, ou seja, proximo ponto
    if(ln.length() < 5){                        // Se estiver perto o suficiente,
        pontoIndex++;                           // Incrementa o index da lista de ponto
        if(pontoIndex >= pontos.size()){        // Sendo esse index maior do que o tamanho da lista de pontos totais,
            return;                             // Retorna e nao altera
        }
        destino = pontos[pontoIndex];           // Se nao, define como 'destino' o proximo ponto da lista
        rotacionarPonto(destino);               // Rotaciona na direcao desse ponto
    }

    int STEPSIZE = 5;                                           // Para mover na direcao certa, caminha nesse tamanho determinado em 'STEPSIZE'
    double theta = rotation();                                  // E utliizia esse metodo 'rotation()' para entao calcular o respectivo angulo:

    double dy = STEPSIZE * qSin(qDegreesToRadians(theta));      // Calcula a distancia vertical por meio do seno do angulo e o seu tamanho
    double dx = STEPSIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);                         // Define sua posicao com os valores calculados acima

    if(this->pos().x() >= 800 || this->pos().y() >= 600){       // Quando os inimigos atravessarem determinada coordenada, ou seja, saem da tela,
        game->vida->diminuirVida();                                 // Diminuir a vida
        scene()->removeItem(this);                                  // Remover da cena
        delete this;                                                // Deletar sua alocacao
    }
}
