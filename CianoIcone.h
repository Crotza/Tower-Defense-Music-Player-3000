#ifndef CIANOICONE_H
#define CIANOICONE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class CianoIcone: public QGraphicsPixmapItem
{
public:
    CianoIcone(QGraphicsPixmapItem *parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CIANOICONE_H
