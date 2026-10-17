#include "player.h"

#define GRAVITY   600.0f // gravidade
#define GROUND_Y  1000.0f // chao

void PlayerInit(Player *p, const char *spritePath, Vector2 start, bool active)
{
    p->sprite = LoadTexture(spritePath); // coloca o sprite do personagem
    p->pos = start; // onde ele spawna
    p->size = (Vector2){ p->sprite.width, p->sprite.height}; // tamanho do personagem
    p->speed = 220.0f;
    p->jumpForce = 500.0f;
    p->velY = 0.0f; // controla a velocidade do personagem no eixo Y
    p->isGround = false;
    p->isActive = active; // alterna entre os personagens
}

void PlayerUpdate(Player *p, float dt)
{   
    // movimentacao do personagem
    if(p->isActive){
        if (IsKeyDown(KEY_RIGHT)) p->pos.x += p->speed * dt;
        if (IsKeyDown(KEY_LEFT)) p->pos.x -= p->speed * dt;

        if(IsKeyPressed(KEY_UP) && p->isGround) {
            p->velY = -p->jumpForce;
            p->isGround = false;
        }
    }

    //gravidade
    p->velY += GRAVITY * dt;
    p->pos.y += p->velY * dt;

    //verifica se o personagem esta no chao
    if (p->pos.y + p->size.y >= GROUND_Y) {
        p->pos.y = GROUND_Y - p->size.y;
        p->velY = 0;
        p->isGround = true;
    }
}

void PlayerDraw(const Player *p)
{
    DrawTextureV(p->sprite, p->pos, WHITE);
}