#include "mapa.h"
#include "raylib.h"
#include "string.h"

#include "mapas/mapa1.h"
#include "mapas/mapa2.h"
#include "mapas/mapa3.h"
#include "mapas/mapa4.h"
#include "mapas/mapa5.h"

// MAPA DE TESTE 
int mapa[MAP_H][MAP_W];

MapaConfig configMapa;

MapExits exits;

int MapaCount(void) {
    return 4;
}

bool MapaLoad(int index) {

    switch (index) {

        case 0:
            memcpy(mapa, MAPA1, sizeof(mapa));

            configMapa = (MapaConfig){
                .dogSpawn = {100, 400},
                .catSpawn = {200, 400},

                .box = {250, 400, 100, 100},
            };

            configMapa.catBlock.y = configMapa.catBlockIniPos;
            configMapa.dogBlock.y = configMapa.dogBlockIniPos;

            exits.catExit = (Rectangle){1200, 350, 64, 64};
            exits.dogExit = (Rectangle){1100, 350, 64, 64};
            break;

        case 1:
            memcpy(mapa, MAPA2, sizeof(mapa));

            configMapa = (MapaConfig){
                .dogSpawn = {100, 400},
                .catSpawn = {200, 400},

                .waterPuddle = {380, 600, 500, 10}
            };

            exits.catExit = (Rectangle){1000, 545, 64, 64};
            exits.dogExit = (Rectangle){1100, 545, 64, 64};
            break;

        case 2:
            memcpy(mapa, MAPA3, sizeof(mapa));

            configMapa = (MapaConfig){
                .dogSpawn = {100, 400},
                .catSpawn = {200, 400},

                .catBlockIniPos = 480,
                .catBlockDestinyPos = 610,
                .dogBlockIniPos = 255,
                .dogBlockDestinyPos = 55,

                .catBlock = {585, 480, 80, 200}, //(x, y, width, height)
                .dogBlock = {585, 255, 80, 200},

                .catButton = {300, 590, 60, 20},
                .dogButton = {900, 590, 60, 20},
            };

            exits.catExit = (Rectangle){1000, 545, 64, 64};
            exits.dogExit = (Rectangle){1100, 545, 64, 64};
            break;

        case 3:
            memcpy(mapa, MAPA4, sizeof(mapa));

            configMapa = (MapaConfig){
                .dogSpawn = {100, 100},
                .catSpawn = {200, 100},

                .box = {250, 400, 100, 100},

                .waterPuddle = {630, 406, 450, 10},
            };

            exits.catExit = (Rectangle){1200, 348, 64, 64};
            exits.dogExit = (Rectangle){1100, 348, 64, 64};
            break;

        case 4:
            memcpy(mapa, MAPA5, sizeof(mapa));

            configMapa = (MapaConfig){
                .dogSpawn = {100, 590},
                .catSpawn = {100, 550},

                .box = {700, 590, 100, 100},

                .waterPuddle = {475, 600, 300, 10},
                
                .catBlockIniPos = 480,
                .catBlockDestinyPos = 610,
                .dogBlockIniPos = 270,
                .dogBlockDestinyPos = 55,

                .catBlock = {259, 480, 60, 150}, //(x, y, width, height)
                .dogBlock = {259, 270, 60, 150},

                .catButton = {180, 590, 60, 20},
                .dogButton = {350, 590, 60, 20},
            };

            exits.catExit = (Rectangle){1200, 348, 64, 64};
            exits.dogExit = (Rectangle){1100, 348, 64, 64};
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