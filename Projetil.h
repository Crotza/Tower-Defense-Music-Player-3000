#ifndef PROJETIL_H
#define PROJETIL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Projetil: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Projetil(QGraphicsItem *parent=0);
    ~Projetil();

public slots:
    void mover();
    //getters e setters
    double getMaxRange();
    double getDistPercorrida();
    void setMaxRange(double range);
    void setDistPercorrida(double dist);

private:
    double maxRange;
    double distPercorrida;
};

#endif // PROJETIL_H
