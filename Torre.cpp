#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include <QLineF>
#include <QTimer>
#include <QGraphicsRectItem>

#include "Game.h"
#include "Torre.h"
#include "Projetil.h"
#include "Inimigo.h"

extern Game * game;

#include <QDebug>

Torre::Torre(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    QVector<QPointF> pontos;        // Pontos para definir a regiao de ataque da torre
    pontos << QPoint(1, 0) << QPoint(2, 0) << QPoint(3, 1) << QPoint(3, 2) << QPoint(2, 3) << QPoint(1, 3) << QPoint(0, 2) << QPoint(0, 1);

    int SCALE = 100;
    for (size_t i = 0, n = pontos.size(); i < n; i++){      // Aumenta o tamanho do octogono, caso necessario
        pontos[i] *= SCALE;
    }

    //criar a forma geometrica do range (octogono) dos pontos
    areaATK = new QGraphicsPolygonItem(QPolygonF(pontos),this);     // Criar a forma geometrica do range (octogono) pelos pontos dados
    areaATK->setPen(QPen(Qt::DotLine));
    //areaATK->setZValue(-1);

    //centralizar a forma com a torre
    QPointF poly_center(1.5, 1.5);                      // Centraliza essa forma com a torre
    poly_center *= SCALE;
    poly_center = mapToScene(poly_center);

    QPointF tower_center(x()+25, y()+25);               // Define o centro da torre
    QLineF ln(poly_center, tower_center);               // Determina uma linha entre o centro da forma com a torre
    areaATK->setPos(x()+ln.dx(), y()+ln.dy());          // Define tal como uma Area de Ataque

    destATK = QPointF(0, 0);                    // Determina o destino do ataque
    temAlvo = false;                            // Determina o atributo booleano 'temAlvo' como falso, pois nao tem inimigos na area de ataque
}

double Torre::distPara(QGraphicsItem *item)
{
    QLineF ln(this->pos(),item->pos());         // Linha para determinar a distancia da torre ate o item em colisao com a area de ataque
    return ln.length();
}

void Torre::reconhecerAlvo()
{
    QList<QGraphicsItem *> colliding_Items = areaATK->collidingItems();     // Lista de itens colidindo com a area de ataque

    temAlvo = false;                                                        // Ainda nao possuem colisoes validas, portanto 'false'

    double minDist = 300;                                                   // Inicializa a distancia minima para atacar
    QPointF minPoint = QPointF(0, 0);                                       // Inicializa o menor ponto dos itens em colicsao

    for(size_t i = 0, n = colliding_Items.size(); i < n; i++){              // Percorrendo todos os itens da lista,
        Inimigo *inimigo = dynamic_cast<Inimigo *>(colliding_Items[i]);         // Verifica se tal item e um inimigo
        if(inimigo){                                                            // Se sim,
            double thisDist = distPara(colliding_Items[i]);                         // A distancia atual recebe a distancia para esse item em colisao
            if(thisDist < minDist){                                                 // Se a distancia atual for menor do que a distancia minima
                minDist = thisDist;                                                     // A menor distancia recebe essa distancia minima
                QPointF minPointErrado = colliding_Items[i]->pos();                     // Menor ponto se da pela posicao desse item colidindo
                minPoint = QPointF(minPointErrado.x()+50, minPointErrado.y()+25);
                temAlvo = true;                                                         // Alvo confirmado, muda seu estado para 'true'
            }
        }
    }

    if(temAlvo){                    // Se tiver um alvo,
        destATK = minPoint;             // Destino do ataque se torna esse menor ponto
        atirar();                       // Chama a funcao de atirar
    }
}

