#ifndef ESTADOS_H
#define ESTADOS_H

#include "raylib.h"
#include "player.h"
#include "interactable.h"
#include "mapa.h"
// #include "tempo.h"
#include "score.h"

// #include <stdbool.h>    

typedef enum { 
    ATTRACT_MODE, PLAYING //, PAUSE, MENU
}Estado;

typedef struct{
    Player dog;
    Player cat;

    Rectangle block1;
    Rectangle block2;
    Rectangle catBlock;
    Rectangle dogBlock;
    Caixa caixa;

    // mapa e fase
    int currentMap;
    bool finishedGame;
    bool canGoNext;

    Score score;
}Jogo;

typedef struct{
    Player dog;
    Player cat;
}Attract;

// 0 - ATTRACT MODE
void AttractModeUpdate(Attract *attract, float dt);
void AttractModeDraw(const Attract *attract);

// 1 - PLAYING
void PlayingUpdate(Jogo *jogo, float dt);
void PlayingDraw(const Jogo *jogo); // const para não alterar

#endif
