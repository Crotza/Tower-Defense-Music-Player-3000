#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsLineItem>
#include <QColor>
#include <QMediaPlayer>
#include <QAudioOutput>

#include <fstream>
#include <QCoreApplication>
#include <QMessageBox>

#include "Game.h"
#include "Torre.h"
#include "AzulIcone.h"
#include "AzulTorre.h"
#include "CianoIcone.h"
#include "CianoTorre.h"
#include "AmareloIcone.h"
#include "AmareloTorre.h"
#include "LaranjaIcone.h"
#include "LaranjaTorre.h"
#include "Projetil.h"
#include "Inimigo.h"
#include "Chefao.h"
#include "Dinheiro.h"

Game::Game(): QGraphicsView()
{
    scene = new QGraphicsScene(this);                       // Cria uma Cena
    scene->setSceneRect(0, 0, 800, 600);                    // Determina seu tamanho
    setScene(scene);                                        // Define essa cena criada

    setStyleSheet("background-color: darkseagreen;");       // Determina a Cor do Background do jogo

            music = new QMediaPlayer;
            //music->setLoops(QMediaPlayer::Infinite);
            sfx = new QMediaPlayer;
            music->setLoops(QMediaPlayer::Infinite);
            audioOutput = new QAudioOutput;
            music->setAudioOutput(audioOutput);

            //connect(music, &QMediaPlayer::sourceChanged, music, &QMediaPlayer::play); // Se mudar a musica, começar a tocar ela

            connect(music, &QMediaPlayer::sourceChanged, [this](){
                music->setLoops(QMediaPlayer::Infinite);
                music->play();
                qDebug() << "play";
            });

            //music->setSource(QUrl::fromLocalFile("C:\\Users\\joaop\\Documents\\Tower-Defense-POO\\images\\music.mp3"));
            music->setSource(QUrl("qrc:/songs/music.mp3"));
            sfx->setSource(QUrl("qrc:/songs/wrongbuzzsfx.wav"));
            audioOutput->setVolume(50);
            //music->play();


    cursor = nullptr;                                       // Set no cursor e no modo 'build' como null para futuras aplicacoes
    build = nullptr;
    setMouseTracking(true);                                 // Definir como 'true' para manter o rastreio das coordenadas do mouse

    setFixedSize(800, 600);                                         // Arruma o tamanho da cena
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);           // Desativa as barras de rolagem
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    spawnTimer = new QTimer(this);                                  // Cria o Inimigo
    inimigosSpawnados = 0;                                          // Inicia o atributo em 0, pois ainda não foram spawnados inimigos
    maxInimigo = 0;                                                 // Inicia o limite de inimigos em 0

    pontosCaminho << QPointF(0, 300) << QPointF(800, 300);              // Coordenadas do caminho para ser percorrido pelos inimigos
    pontosCaminho2 << QPointF(0, 345) << QPointF(800, 345);
    pontosCaminhoChefao << QPointF(440, 0) << QPointF(440, 600);        // Coordenadas do caminho para ser percorrido pelo Chefao
    pontosCaminhoChefao2 << QPointF(340, 0) << QPointF(340, 600);

    containerCompra << QPointF(0, 600) << QPointF(800, 600);            // Cria um container inferior para deixar esteticamente mais agradavel

    fase = 1;                                                                   // Inicializa na fase 1
    criarCaminho();                                                             // Cria o caminho onde os inimigos passarão
    connect(this, SIGNAL(acabouFaseSignal()), this, SLOT(gerarNovaFase()));     // Conecta uma funcao para passar de fase

    AzulIcone *azulIC = new AzulIcone();                    // Criam os Icones para as Torres
    CianoIcone *cianoIC = new CianoIcone();
    AmareloIcone *amareloIC = new AmareloIcone();
    LaranjaIcone *laranjaIC = new LaranjaIcone();

    azulIC->setPos(x() + 10, y() + 550);                    // Determina as suas coordenadas
    cianoIC->setPos(x() + 60, y() + 550);
    amareloIC->setPos(x() + 110, y() + 550);
    laranjaIC->setPos(x() + 160, y() + 550);

    scene->addItem(azulIC);                                 // Adiciona na cena
    scene->addItem(cianoIC);
    scene->addItem(amareloIC);
    scene->addItem(laranjaIC);

    score = new Score();                                    // Cria o Score, Vida e Dinheiro
    vida = new Vida();
    dinheiro = new Dinheiro();

    score->setPos(x() + 675, y() + 10);                     // Determina as suas coordenadas
    vida->setPos(x() + 700, y() + 555);
    dinheiro->setPos(x() + 550, y() + 555);

    scene->addItem(score);                                  // Adiciona na cena
    scene->addItem(vida);
    scene->addItem(dinheiro);

    carregaSave();

    delayFase = new QTimer();
    delayFase->setSingleShot(true);
    connect(delayFase, SIGNAL(timeout()), this, SLOT(controleFase()));
    controleFase();                                     // Inicializa a fase
}

void Game::setCursor(QString filename)
{
    if(cursor){                                         // Se o cursor retornar 'true'
        scene->removeItem(cursor);                      // Apago da cena esse cursor
        delete cursor;                                  // E deleto sua alocacao
    }

    cursor = new QGraphicsPixmapItem();                 // Se nao, cria o Cursor
    cursor->setPixmap(QPixmap(filename));               // Importa seu respectivo png
    scene->addItem(cursor);                             // Adiciona na cena
}

void Game::gerarNovaFase()
{
    delayFase->start(2000);                             // Chama a funcao de delay entre fases
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if(cursor){ cursor->setPos(event->pos()); }         // Se o cursor retornar 'true', determina sua posicao como as coordenadas do evento relacionado (click)
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if(build){                                                                                      // Modo de Construção
        QList<QGraphicsItem *> itemsColidindo = cursor->collidingItems();                           // Lista de items colidindo com o cursor
        for(size_t i = 0, n = itemsColidindo.size(); i < n; i++){                                   // Para cada um desses items:
            try{
                QGraphicsPolygonItem *torre = dynamic_cast<QGraphicsPolygonItem *>(itemsColidindo[i]);      // Verifica se e uma torre
                QGraphicsLineItem *caminho = dynamic_cast<QGraphicsLineItem *>(itemsColidindo[i]);          // Verifica se e um caminho ou regiao de compra
                if(torre) throw "torre";                                                                               // Se sim, gera uma exceção
                else if(caminho) throw "caminho";
                else continue;
            }catch(const char *excecao){
                sfx->setAudioOutput(audioOutput);
                sfx->play();
                return;
            }
        }

        if(cursor->pos().x() >= 750) return;                                        // Se for pra fora da tela (esq), retorna

        if(dynamic_cast<AzulTorre*>(build)){                                        // Analisa e determina um preço especifico
            if(dinheiro->getDinheiro() > 50) { dinheiro->diminuirDinheiro(50); }    // para cada tipo de torre
            else return;
        }
        else if(dynamic_cast<CianoTorre*>(build)){
            if(dinheiro->getDinheiro() > 100) { dinheiro->diminuirDinheiro(100); }
            else return;
        }

        else if(dynamic_cast<AmareloTorre*>(build)){
            if(dinheiro->getDinheiro() > 125) { dinheiro->diminuirDinheiro(125); }
            else return;
        }
        else if(dynamic_cast<LaranjaTorre*>(build)){
            if(dinheiro->getDinheiro() > 150) { dinheiro->diminuirDinheiro(150); }
            else return;
        }

        scene->addItem(build);                          // Se nao estiver colidindo, adiciona a torre nas coordenadas do cursor
        build->setPos(event->pos());                    // Define esse evento

        cursor = nullptr;                               // Define como 'nullptr' para sair do modo de construcao
        build = nullptr;
    }

    else { QGraphicsView::mousePressEvent(event); }         // Fora do modo de construcao
}

void Game::keyPressEvent(QKeyEvent *event){                 // Todos os eventos do teclado sao implementados nessa funcao
    QUrl novaMusica = music->source();                      // Comeca a musica igual

    switch(event->key()){                                   // Easter egg de musicas diferentes
        case Qt::Key_A:
            novaMusica = QUrl("qrc:/songs/dream_on.mp3");       // kk
            break;
        case Qt::Key_B:
            novaMusica = QUrl("qrc:/songs/receba.mp3");         // entregue
            break;
        case Qt::Key_N:
            novaMusica = QUrl("qrc:/songs/music.mp3");          // volta ao normal
            break;
    }

    if(event->key() == Qt::Key_F1){                         // Ao apertar F1, o jogo salva em um arquivo .dat as informacoes necessarias
        std::fstream f((QCoreApplication::applicationDirPath() + "/save.dat").toStdString(), std::fstream::out);    // Cria o arquivo de save
        f << vida->getVida() << " " << score->getScore() << " " << dinheiro->getDinheiro() << " " << this->fase << "\n";    // Salva na primeira linha
                                                                                                                            // Vida Score Dinheiro Fase
        QList<QGraphicsItem *> items = this->items();                   // Vetor com todos os itens adicionados na cena
        int qtdTorre = 0;                                               // Numero de Torres adicionadas
            for(size_t i = 0, n = items.size(); i < n; i++){            // Percorre os itens na cena e verifica se e do tipo Torre
                    Torre *torre = dynamic_cast<Torre *>(items[i]);
                    if(torre) { qtdTorre++; }                           // Se sim, incrementa o numero de torres
            }
        f << qtdTorre << "\n";                                          // Salva entao na proxima linha o numero de torres adicionadas

        int tipoTorre;                                                  // Define o tipo da torre, sendo 0: Azul, 1: Ciano, 2: Amarelo, 3: Laranja
        for(size_t i = 0, n = items.size(); i < n; i++){                // Percorre os itens novamente
            Torre *torre = dynamic_cast<Torre *>(items[i]);             // Verificando se e do tipo Torre

            if(dynamic_cast<AzulTorre*>(torre)){ tipoTorre = 0; }           // Se sim, identifica seu tipo
            else if(dynamic_cast<CianoTorre*>(torre)){ tipoTorre = 1; }
            else if(dynamic_cast<AmareloTorre*>(torre)){ tipoTorre = 2; }
            else if(dynamic_cast<LaranjaTorre*>(torre)){ tipoTorre = 3; }

            if(torre) { f << torre->x() << " " << torre->y() << " " << tipoTorre << "\n"; }     // E entao salva as suas coordenadas X, Y e seu tipo
        }
        f.close();                                                          // Fecha o arquivo
    }


    if(novaMusica != music->source()){      // Se a musica atual for igual a que quiser tocar, nem muda (sem isso recomeca)
        music->setSource(novaMusica);
    }
}

void Game::criarInimigo(int qtdInimigo)
{
    inimigosSpawnados = 0;                                                  // Inicializa em 0
    maxInimigo = qtdInimigo;                                                // Numero maximo spawnado deve ser o argumento recebido pelo metodo
    qDebug() << maxInimigo;
    connect(spawnTimer, SIGNAL(timeout()), this, SLOT(spawnInimigo()));     // Conecta o metodo de 'spawnInimigo' com uma funcao de tempo, para loop
    spawnTimer->start(1500);
}

void Game::criarChefao(){
    inimigosSpawnados = 0;                              // 0 inimigos no mapa
    maxInimigo = 1;                                     // Criou o Chefao
    spawnChefao();                                      // Spawna o Chefao
}

void Game::criarCaminho()
{
    for(size_t i = 0, n = pontosCaminhoChefao.size() - 1; i < n; i++){          // For loop para percorrer todos os pontos definidos como o caminho do Chefao
        QLineF line(pontosCaminhoChefao[i], pontosCaminhoChefao[i+1]);          // Cria uma linha entre cada um dos pontos
        QLineF line2(pontosCaminhoChefao2[i], pontosCaminhoChefao2[i+1]);

        QGraphicsLineItem *lineItem = new QGraphicsLineItem(line);              // Linha do Caminho dos inimigos
        QGraphicsLineItem *lineItem2 = new QGraphicsLineItem(line2);

        QPen pen;

        // Caminhos
        pen.setWidth(100);                                              // Largura
        pen.setColor(QColor(175, 238, 238));                            // Cor - 'https://www.w3.org/TR/SVG11/types.html#ColorKeywords'
        lineItem->setPen(pen);
        lineItem2->setPen(pen);
        scene->addItem(lineItem);                                       // Adiciona na cena
        scene->addItem(lineItem2);
    }

    for(size_t i = 0, n = pontosCaminho.size() - 1; i < n; i++){        // For loop para percorrer todos os pontos definidos como o caminho dos inimigos
        QLineF line(pontosCaminho[i], pontosCaminho[i+1]);              // Cria uma linha entre cada um dos pontos
        QLineF line2(pontosCaminho2[i], pontosCaminho2[i+1]);

        QGraphicsLineItem *lineItem = new QGraphicsLineItem(line);              // Linha do Caminho dos inimigos
        QGraphicsLineItem *lineItem2 = new QGraphicsLineItem(line2);

        QPen pen;

        // Caminhos
        pen.setWidth(45);                                               // Largura
        pen.setColor(QColor(222, 184, 135));                            // Cor
        lineItem->setPen(pen);
        lineItem2->setPen(pen);
        scene->addItem(lineItem);                                       // Adiciona na cena
        scene->addItem(lineItem2);
    }

    for(size_t i = 0, n = containerCompra.size() - 1; i < n; i++){          // For loop para percorrer todos os pontos definidos como o container de compra
        QLineF lineCompra(containerCompra[i], containerCompra[i+1]);            // Cria uma linha entre cada um dos pontos

        QGraphicsLineItem *lineItem3 = new QGraphicsLineItem(lineCompra);       // Linha do container de compra

        QPen pen;

        // Compra
        pen.setWidth(125);                                              // Largura
        pen.setColor(QColor(240, 255, 255));                            // Cor
        lineItem3->setPen(pen);
        scene->addItem(lineItem3);                                      // Adiciona na cena
    }
}


void Game::spawnInimigo()
{
    Inimigo *inimigo = new Inimigo(pontosCaminho);          // Cria o Inimigo
    inimigo->setPos(pontosCaminho[0]);                      // Define a sua posicao de inicio
    scene->addItem(inimigo);                                // Adiciona na cena
    inimigosSpawnados += 1;                                 // Incrementa o numero spawnado

    if(inimigosSpawnados >= maxInimigo){                // Se houverem mais inimigos do que o maximo estipulado,
        fase++;
        spawnTimer->disconnect();                       // Disconecta e para a funcao de loopar o spawn de inimigos
        emit acabouFaseSignal();
    }
}

void Game::spawnChefao()
{
    Chefao *chefao = new Chefao(pontosCaminhoChefao);      // Cria o Chefao
    chefao->setPos(pontosCaminhoChefao[0]);                // Define a sua posicao de inicio
    scene->addItem(chefao);                                // Adiciona na cena
    inimigosSpawnados = 1;                                 // Incrementa o numero spawnado

    if(inimigosSpawnados >= maxInimigo){                   // Se houverem mais inimigos do que o maximo estipulado,
        fase++;
        emit acabouFaseSignal();
    }
}

void Game::carregaSave(){
    std::fstream f((QCoreApplication::applicationDirPath() + "/save.dat").toStdString(), std::fstream::in);     // Abre o arquivo de save criado

    if(f.is_open()){                                                // Se ele abrir,
        int vidaSave, scoreSave, dinheiroSave, faseSave;                // Salva as informacoes contidas nele
        int qtdTorreSave;
        int xSave, ySave, tipoSave;
        Torre* torreSave;

        f >> vidaSave;
        f >> scoreSave;
        f >> dinheiroSave;
        f >> faseSave;
        f >> qtdTorreSave;

        vida->setVida(vidaSave);                                        // Seta esses dados lidos no jogo
        score->setScore(scoreSave);
        dinheiro->setDinheiro(dinheiroSave);
        fase = faseSave;

        vida->setPlainText(QString("Vida: ") + QString::number(vidaSave));              // Edita tambem os textos exibidos
        score->setPlainText(QString("Score: ") + QString::number(scoreSave));
        dinheiro->setPlainText(QString("Dinheiro: ") + QString::number(dinheiroSave));


        for(size_t i = 0, n = qtdTorreSave; i < n; i++){                // Percorre o numero de torres salvas, identificando suas coordenadas e tipo
            f >> xSave;
            f >> ySave;
            f >> tipoSave;

            QPoint pt(xSave, ySave);

            if(tipoSave == 0){ torreSave = new AzulTorre(); }           // Cria a respectiva torre
            else if(tipoSave == 1){ torreSave = new CianoTorre(); }
            else if(tipoSave == 2){ torreSave = new AmareloTorre(); }
            else if(tipoSave == 3){ torreSave = new LaranjaTorre(); }

            scene->addItem(torreSave);                                  // Adiciona na cena
            torreSave->setPos(pt);                                      // Nas coordenadas salvas
        }
        f.close();                                              // Fecha o arquivo quando terminar a leitura
    }
}

void Game::controleFase()
{
    if(vida->getVida() > 0){                        // Se ainda o player ter vida
        if(fase == 1) { criarInimigo(10); }             // Para cada fase, spawna uma quantidade especifica de inimigos
        else if(fase == 2) { criarInimigo(15); }
        else if(fase == 3) { criarInimigo(20); }
        else if(fase == 4) { criarInimigo(30); }
        else if(fase == 5) { criarInimigo(35); }
        else if(fase == 6) { criarChefao(); }           // Spawn do Chefao
        else return;
    }
}

