#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QMediaPlayer>
#include <QAudioOutput>

#include "Torre.h"
#include "Score.h"
#include "Vida.h"
#include "Dinheiro.h"

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    //metodos
    Game();
    void setCursor(QString filename);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event) override;
    void criarInimigo(int qtdInimigo);
    void criarChefao();
    void criarCaminho();
    void carregaSave();

    //atributos
    QGraphicsScene *scene;
    QGraphicsPixmapItem *cursor;
    Torre *build;

    QMediaPlayer *music;
    QAudioOutput *audioOutput;
    QMediaPlayer *sfx;

    QTimer *spawnTimer;
    int inimigosSpawnados;
    int maxInimigo;
    int fase;

    QList<QPointF> pontosCaminho;
    QList<QPointF> pontosCaminho2;
    QList<QPointF> pontosCaminhoChefao;
    QList<QPointF> pontosCaminhoChefao2;
    QList<QPointF> containerCompra;

    Score *score;
    Vida *vida;
    Dinheiro *dinheiro;

    bool acabouFase = true;
    QTimer *delayFase;

public slots:
    void spawnInimigo();
    void spawnChefao();
    void gerarNovaFase();
    void controleFase();

signals:
    void acabouFaseSignal();

};

#endif // GAME_H
