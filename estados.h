#ifndef ESTADOS_H
#define ESTADOS_H

#include "raylib.h"
#include "player.h"
#include "interactable.h"
// #include <stdbool.h>    

typedef enum estados { 
    ATTRACT_MODE, PLAYING //, PAUSE, MENU
}Estado;

typedef struct {
    float ms;
    float sec;
    float min;
}Time;

typedef struct{
    Player dog;
    Player cat;

    Rectangle parede;
    Caixa caixa;

    Time tempo;
}Jogo;

// 0 - ATTRACT MODE
void AttractModeUpdate();
void AttractModeDraw();

// 1 - PLAYING
void PlayingUpdate(Jogo *jogo);
void PlayingDraw(Jogo *jogo);

#endif
