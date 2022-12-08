#include <QFont>
#include "Score.h"

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    score = 0;                                                      // Inicializa o Score

    setPlainText(QString("Score: ") + QString::number(score));      // Exibe o texto 'Score: 0' na tela
    setDefaultTextColor(Qt::black);                                  // Cor
    setFont(QFont("times", 16));                                    // Fonte e tamanho
    setZValue(3);
}

void Score::aumentaScore()
{
    score++;
    setPlainText(QString("Score: ") + QString::number(score));      // Score: 1, 2, 3, ...
}

int Score::getScore()
{
    return score;
}

void Score::setScore(int s)
{
    score = s;
}
