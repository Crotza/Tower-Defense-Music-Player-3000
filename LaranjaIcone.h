#ifndef LARANJAICONE_H
#define LARANJAICONE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class LaranjaIcone: public QGraphicsPixmapItem
{
public:
    LaranjaIcone(QGraphicsPixmapItem *parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // LARANJAICONE_H
