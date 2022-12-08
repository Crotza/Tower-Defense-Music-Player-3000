#ifndef AMARELOICONE_H
#define AMARELOICONE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class AmareloIcone: public QGraphicsPixmapItem
{
public:
    AmareloIcone(QGraphicsPixmapItem *parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // AMARELOICONE_H
