#ifndef CHEFAO_H
#define CHEFAO_H

#include "Inimigo.h"

class Chefao: public Inimigo
{
    Q_OBJECT
public:
    Chefao(QList<QPointF> pontosCaminho, QGraphicsItem *parent=0);
    ~Chefao();
    void diminuirVida();
    int getVida();

private:
    int vida;

};

#endif // CHEFAO_H
