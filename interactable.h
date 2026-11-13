#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include "player.h"
#include "raylib.h"
#include <stdbool.h>

typedef struct  
{
    Rectangle rect;
    Rectangle *block;
}Button;

typedef struct  
{
    Rectangle rect;
    float velY;
    bool isGround;
}Caixa;

void empurrarCaixa(Player *dog, Caixa *caixa);
void CaixaUpdate(Caixa *c, float dt);

void ButtonUpdate(Button *button, Player *player, float dt);
void ButtonDraw(Button *button, Color cor);

#endif
