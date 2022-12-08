#include <QFont>
#include "Dinheiro.h"

Dinheiro::Dinheiro(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    dinheiro = 1500;                                                     // Inicializa o Dinheiro

    setPlainText(QString("Dinheiro: ") + QString::number(dinheiro));        // Exibe o texto 'Score: 0' na tela
    setDefaultTextColor(QColor(255, 215, 0));                               // Cor
    setFont(QFont("times", 16));                                            // Fonte e tamanho
}

void Dinheiro::aumentaDinheiro(float valor)
{
    dinheiro += valor;
    setPlainText(QString("Dinheiro: ") + QString::number(dinheiro));      // Dinheiro: 1, 2, 3, ...
}

void Dinheiro::diminuirDinheiro(float valor)
{
    dinheiro -= valor;
    setPlainText(QString("Dinheiro: ") + QString::number(dinheiro));      // Dinheiro: 5, 4, 3, ...
}

float Dinheiro::getDinheiro()
{
    return dinheiro;
}

void Dinheiro::setDinheiro(float d)
{
    dinheiro = d;
}
