#ifndef LEVELS_H
#define LEVELS_H

#include "raylib.h"
#include "player.h"

typedef struct Level {
    Vector2 catSpawn, dogSpawn; //Spawn points
    float groundY; //Posição do chão
    Rectangle catExit, dogExit; //Ponto de chegada dos personagens
} Level;

int  LevelCount(void);
void LevelLoad(Level *lv, int index);
void LevelDraw(const Level *lv);
bool LevelComplete(const Level *lv, const Player *a, const Player *b);

#endif