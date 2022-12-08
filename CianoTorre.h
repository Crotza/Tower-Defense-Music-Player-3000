#ifndef CIANOTORRE_H
#define CIANOTORRE_H

#include "Torre.h"

class CianoTorre: public Torre
{
    Q_OBJECT
public:
    CianoTorre(QGraphicsItem *parent=0);
    void atirar();

public:
    void reconhecerAlvo();
};

#endif // CIANOTORRE_H
