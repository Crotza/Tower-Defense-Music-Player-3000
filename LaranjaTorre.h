#ifndef LARANJATORRE_H
#define LARANJATORRE_H

#include "Torre.h"

class LaranjaTorre: public Torre
{
    Q_OBJECT
public:
    LaranjaTorre(QGraphicsItem *parent=0);
    void atirar();

public:
    void reconhecerAlvo();
};

#endif // LARANJATORRE_H
