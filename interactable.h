#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include "player.h"
#include "raylib.h"
#include <stdbool.h>

typedef struct{
    Rectangle rect;
    float velY;
    bool isGround;
    Texture2D sprite;
}Caixa;

void empurrarCaixa(Player *dog, Caixa *caixa);
void CaixaUpdate(Caixa *c, float dt);
void CaixaInit(Caixa *c, char *spritePath, float size, Vector2 pos);
void CaixaDraw(const Caixa *c);

#endif
