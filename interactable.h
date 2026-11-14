#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include "player.h"
#include "raylib.h"
#include <stdbool.h>

typedef struct{
    Rectangle rect;
    Rectangle *block;
    float iniPos;
    float destiny;
}Button;

typedef struct  
{
    Rectangle rect;
    float velY;
    bool isGround;
    Texture2D sprite;
}Caixa;

void EmpurrarCaixa(Player *dog, Caixa *caixa, bool forca, Player *gato);
void CaixaUpdate(Caixa *c, float dt);
void CaixaInit(Caixa *c, char *spritePath, float size, Vector2 pos);
void CaixaDraw(const Caixa *c);

void ButtonUpdate(Button *button, Player *player, float dt, float iniPos, float destiny);
void ButtonDraw(Button *button, Color cor);

#endif
