#ifndef VIDA_H
#define VIDA_H

#include <QGraphicsTextItem>

class Vida: public QGraphicsTextItem
{
public:
    Vida(QGraphicsItem *parent=0);
    void diminuirVida();
    int getVida();
    void setVida(int v);

private:
    int vida;
};

#endif // VIDA_H
