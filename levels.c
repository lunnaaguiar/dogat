#include "levels.h"

static const Level LEVELS[] = {
    { // Fase 1
        .groundY = 1000,
        .dogExit  = {1600, 900, 120, 100},
        .catExit  = {1750, 900, 120, 100},
    },
    { // Fase 2
        .groundY = 1000,
        .dogExit  = {1600, 900, 120, 100},
        .catExit  = {1750, 900, 120, 100},
    },
};

int LevelCount(void) { return sizeof(LEVELS) / sizeof(LEVELS[0]); }

void LevelLoad(Level *lv, int index) { *lv = LEVELS[index]; }

void LevelDraw(const Level *lv) {
    DrawLine(0, lv->groundY, GetScreenWidth(), lv->groundY, WHITE);
    DrawRectangleLinesEx(lv->dogExit, 3, GREEN);
    DrawRectangleLinesEx(lv->catExit, 3, YELLOW);
}

static Rectangle PlayerRect(const Player *p) {
    return (Rectangle){ p->pos.x - p->size.x/2, p->pos.y - p->size.y/2, p->size.x, p->size.y };
}

bool LevelComplete(const Level *lv, const Player *a, const Player *b) {
    return CheckCollisionRecs(PlayerRect(a), lv->dogExit) &&
           CheckCollisionRecs(PlayerRect(b), lv->catExit);
}