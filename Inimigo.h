#ifndef INIMIGO_H
#define INIMIGO_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList>
#include <QPointF>

class Inimigo: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Inimigo(QList<QPointF> pontosCaminho, QGraphicsItem *parent=0);
    ~Inimigo();
    void rotacionarPonto(QPointF p);

public slots:
    void moverFrente();

private:
    QList<QPointF> pontos;
    QPointF destino;
    int pontoIndex;
};

#endif // INIMIGO_H
