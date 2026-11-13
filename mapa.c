#include "mapa.h"
#include "raylib.h"
#include "string.h"

#include "mapas/mapa1.h"
#include "mapas/mapa2.h"

// MAPA DE TESTE 
int mapa[MAP_H][MAP_W];

MapaConfig configMapa;

MapExits exits;

int MapaCount(void) {
    return 2;
}

bool MapaLoad(int index) {

    switch (index) {

        case 0:
            memcpy(mapa, MAPA1, sizeof(mapa));

            configMapa = (MapaConfig){
                .dogSpawn = {100, 100},
                .catSpawn = {200, 100},

                .catBlock = {700, 400, 80, 200},
                .dogBlock = {1050, 400, 80, 200},

                .catButton = {300, 450, 60, 20},
                .dogButton = {900, 450, 60, 20},

                .box = {64, 0, 64, 64}
            };

            exits.catExit = (Rectangle){1100, 500, 64, 64};
            exits.dogExit = (Rectangle){1100, 400, 64, 64};
            break;

        case 1:
            memcpy(mapa, MAPA2, sizeof(mapa));

            configMapa = (MapaConfig){
                .dogSpawn = {100, 100},
                .catSpawn = {200, 100},

                .catBlock = {700, 400, 80, 200},
                .dogBlock = {1050, 400, 80, 200},

                .catButton = {300, 450, 60, 20},
                .dogButton = {900, 450, 60, 20},

                .box = {64, 0, 64, 64}
            };

            exits.catExit = (Rectangle){1000, 300, 64, 64};
            exits.dogExit = (Rectangle){1100, 300, 64, 64};
            break;

        default:
            return false;
    }

    return true;
}

void DrawMapa(void){

    for(int i=0; i<MAP_H; i++){
        for(int j=0; j<MAP_W; j++){
            if (mapa[i][j] == 1){
                DrawRectangle(j*TILE_SIZE, i*TILE_SIZE, TILE_SIZE, TILE_SIZE, WHITE);
            }
        }
    }
}

void DrawSaidas(void) {
    DrawRectangleRec(exits.catExit, PURPLE);
    DrawRectangleRec(exits.dogExit, BLUE);
}

bool MapaCompleto(Rectangle catRect, Rectangle dogRect) {
    bool catReached = CheckCollisionRecs(catRect, exits.catExit);
    bool dogReached = CheckCollisionRecs(dogRect, exits.dogExit);

    return catReached && dogReached;
}