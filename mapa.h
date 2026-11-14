#ifndef MAPA_H
#define MAPA_H

#include "raylib.h"
#include "stdbool.h"

#define TILE_SIZE 32 // 32X32

#define MAP_W 40    // 40*32 = 1280
#define MAP_H 25    // 25*32 = 800

#define GRAVITY   600.0f // gravidade
#define GROUND_Y  600.0f // chao


extern int mapa[MAP_H][MAP_W];

typedef struct {
    Rectangle catExit;
    Rectangle dogExit;
} MapExits;

typedef struct {
    Vector2 dogSpawn;
    Vector2 catSpawn;

    Rectangle catBlock;
    float catBlockIniPos;
    float catBlockDestinyPos;

    Rectangle dogBlock;
    float dogBlockIniPos;
    float dogBlockDestinyPos;

    Rectangle catButton;
    Rectangle dogButton;

    Rectangle box;
} MapaConfig;

extern MapaConfig configMapa;

int MapaCount(void);
bool MapaLoad(int index);

void DrawMapa(void);
void DrawSaidas(void);
bool MapaCompleto(Rectangle catRect, Rectangle dogRect);

#endif