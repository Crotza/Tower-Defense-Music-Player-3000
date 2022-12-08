#ifndef AZULICONE_H
#define AZULICONE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class AzulIcone: public QGraphicsPixmapItem
{
public:
    AzulIcone(QGraphicsPixmapItem *parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // AZULICONE_H
