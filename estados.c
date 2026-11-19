#include "estados.h"
#include <stdio.h>

// #include "player.h"
// #include "interactable.h"

// 0 - ATTRACT MODE
void AttractModeUpdate(Attract *attract, float dt);

void AttractModeDraw(const Attract *attract);

// 1 - PLAYING
void PlayingUpdate(Jogo *jogo, float dt)
{
    jogo->tempo += dt;
    // obs: inserir função de salvar tempo depois

    // alternar entre personagens
    if (IsKeyPressed(KEY_SPACE))
    {
        jogo->dog.isActive = !jogo->dog.isActive;
        jogo->cat.isActive = !jogo->cat.isActive;
    }

    if (IsKeyPressed(KEY_M)){
        ScoreInserir(&jogo->score, jogo->tempo);
        ScoreSalvar(&jogo->score, "Score.txt");
        jogo->tempo = 0.0f;
    }

    // player update
    PlayerUpdate(&jogo->dog, dt, jogo->catBlock, jogo->dogBlock);
    PlayerUpdate(&jogo->cat, dt, jogo->catBlock, jogo->dogBlock);

    // colisão e interação com objetos
    CaixaUpdate(&jogo->caixa, dt);
    EmpurrarCaixa(&jogo->dog, &jogo->caixa, true, &jogo->cat);
    EmpurrarCaixa(&jogo->cat, &jogo->caixa, false, NULL);
    ButtonUpdate(&jogo->catButton, &jogo->cat, dt, configMapa.catBlockIniPos, configMapa.catBlockDestinyPos);
    ButtonUpdate(&jogo->dogButton, &jogo->dog, dt, configMapa.dogBlockIniPos, configMapa.dogBlockDestinyPos);

    // regras do multijogador
    CarregarGato(&jogo->dog, &jogo->cat); // colisão pro gato subir no cachorro

    jogo->dogRect = (Rectangle){
        jogo->dog.pos.x - jogo->dog.size.x / 2,
        jogo->dog.pos.y - jogo->dog.size.y / 2,
        jogo->dog.size.x,
        jogo->dog.size.y
    };

    jogo->catRect = (Rectangle){
        jogo->cat.pos.x - jogo->cat.size.x / 2,
        jogo->cat.pos.y - jogo->cat.size.y / 2,
        jogo->cat.size.x,
        jogo->cat.size.y
    };

    // parte sem função ainda:
    jogo->levelComplete = MapaCompleto(jogo->catRect, jogo->dogRect);
    jogo->catInPuddle = CatTouchedPuddle(configMapa.waterPuddle, &jogo->cat);

    if (jogo->levelComplete && jogo->canGoNext || jogo->catInPuddle) {
        if(!jogo->catInPuddle) jogo->currentMap++;
        if (MapaLoad(jogo->currentMap)) {
            jogo->dog.pos = configMapa.dogSpawn;
            jogo->cat.pos = configMapa.catSpawn;
            jogo->catBlock = configMapa.catBlock;
            jogo->dogBlock = configMapa.dogBlock;
            jogo->catButton = (Button){configMapa.catButton, &jogo->catBlock};
            jogo->dogButton = (Button){configMapa.dogButton, &jogo->dogBlock};
            jogo->caixa.rect = configMapa.box;
        } else {
            jogo->finishedGame = true;
        }    
        jogo->canGoNext = false;
    }

    if (!jogo->levelComplete) {
        jogo->canGoNext = true;
    }

}

void PlayingDraw(Jogo *jogo)
{
    // BeginDrawing();

    ClearBackground(BLACK);

    DrawMapa(); // repetição que desenha cada tile (puramente visual, a colisão é feita no player.c)
    DrawSaidas();
    PuddleDraw(configMapa.waterPuddle);
    
    // desenhos dos players
    PlayerDraw(&jogo->cat);
    PlayerDraw(&jogo->dog);

    // elementos de interação
    DrawRectangleRec(jogo->catBlock, PURPLE);
    DrawRectangleRec(jogo->dogBlock, BLUE);
    CaixaDraw(&jogo->caixa);
    
    // botões
    ButtonDraw(&jogo->catButton, PURPLE); 
    ButtonDraw(&jogo->dogButton, BLUE);

    // score
    TempoAtualDraw(jogo->tempo);
    ScoreRankDraw(&jogo->score);

    // EndDrawing(); // finaliza
}