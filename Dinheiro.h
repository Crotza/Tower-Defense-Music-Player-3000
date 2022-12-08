#ifndef DINHEIRO_H
#define DINHEIRO_H

#include <QGraphicsTextItem>

class Dinheiro: public QGraphicsTextItem
{
public:
    Dinheiro(QGraphicsItem *parent=0);
    void aumentaDinheiro(float valor);
    void diminuirDinheiro(float valor);
    float getDinheiro();
    void setDinheiro(float d);

private:
    float dinheiro;
};

#endif // DINHEIRO_H
