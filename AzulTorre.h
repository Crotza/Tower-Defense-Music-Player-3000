#ifndef AZULTORRE_H
#define AZULTORRE_H

#include "Torre.h"

class AzulTorre: public Torre
{
    Q_OBJECT
public:
    AzulTorre(QGraphicsItem *parent=0);
    void atirar();
public:
    void reconhecerAlvo();
};

#endif // AZULTORRE_H
