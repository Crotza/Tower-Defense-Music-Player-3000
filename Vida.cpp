#include <QFont>
#include "Vida.h"
#include "Game.h"

Vida::Vida(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    vida = 5;                                                      // Inicializa a Vida

    // mostrar o texto na tela
    setPlainText(QString("Vida: ") + QString::number(vida));        // Exibe o texto 'Vida: 5' na tela
    setDefaultTextColor(Qt::red);                                   // Cor
    setFont(QFont("times", 16));                                    // Fonte e tamanho
}

void Vida::diminuirVida()
{
    if(vida <= 0){
        setPlainText(QString("  VOCÊ\nPERDEU!"));  // Exibe o texto 'VOCE PERDEU!' na tela
        setFont(QFont("times", 10));                                    // Fonte e tamanho
        return;
    }

    vida--;
    setPlainText(QString("Vida: ") + QString::number(vida));        // Vida: 5, 4, 3, ...
}

int Vida::getVida()
{
    return vida;
}

void Vida::setVida(int v)
{
    vida = v;
}

