#ifndef MAPA_H
#define MAPA_H

#define TILE_SIZE 32 // 32X32

#define MAP_W 40    // 40*32 = 1280
#define MAP_H 25    // 25*32 = 800

#define GRAVITY   600.0f // gravidade
#define GROUND_Y  600.0f // chao


extern int mapa[MAP_H][MAP_W];

void DrawMapa(void);

#endif