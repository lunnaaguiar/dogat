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
    ATTRACT_MODE, PLAYING, VICTORY //, PAUSE, MENU
}Estado;

typedef struct{
    Player dog;
    Player cat;

    Rectangle block1;
    Rectangle block2;
    Rectangle dogBlock;
    Rectangle catBlock;
    Caixa caixa;
    Button dogButton;
    Button catButton;

    Rectangle dogRect;
    Rectangle catRect;

    // mapa e fase
    int currentMap;
    bool finishedGame;
    bool canGoNext;
    bool levelComplete;
    bool catInPuddle;
    Texture2D fundos[5];
    Texture2D ceu;
    
    Score score;

    float tempo;
}Jogo;

typedef struct {
    int direcao;
    float tempo;
}Mov;


typedef struct{
    Player dog;
    Player cat;
    Mov movDog;
    Mov movCat;
}Attract;

// 0 - ATTRACT MODE
void AttractModeUpdate(Attract *attract, float dt);
void AttractModeDraw(const Attract *attract);

// 1 - PLAYING
void PlayingUpdate(Jogo *jogo, float dt);
void PlayingDraw(Jogo *jogo); // const para não alterar
// 2 - VICTORY
void JogoReiniciar(Jogo *jogo);   // volta do início
bool VictoryUpdate(void);         // true quando clicar em jogar novamente
void VictoryDraw(const Jogo *jogo);


#endif
