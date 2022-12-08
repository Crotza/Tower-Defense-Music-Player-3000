#ifndef AMARELOTORRE_H
#define AMARELOTORRE_H

#include "Torre.h"

class AmareloTorre: public Torre
{
    Q_OBJECT
public:
    AmareloTorre(QGraphicsItem *parent=0);
    void atirar();

public:
    void reconhecerAlvo();
};

#endif // AMARELOTORRE_H
