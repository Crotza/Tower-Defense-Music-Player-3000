#ifndef TORRE_H
#define TORRE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QObject>

class Torre: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Torre(QGraphicsItem *parent=0);
    double distPara(QGraphicsItem *item);
    virtual void atirar() = 0;

public slots:
    void reconhecerAlvo();

protected:
    QGraphicsPolygonItem *areaATK;
    QPointF destATK;
    bool temAlvo;
};

#endif // TORRE_H
