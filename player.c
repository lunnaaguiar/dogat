#include "player.h"

#define GRAVITY   600.0f // gravidade

void PlayerInit(Player *p, const char *spritePath, Vector2 start, float moveSpeed, float jumpForce, bool active) 
//adicionar aqui as variaveis para os personagem(ex: jumpforce, speed, etc)
// lembrar de mudar no player.h também

{
    p->sprite = LoadTexture(spritePath); // coloca o sprite do personagem
    p->pos = start; // onde ele spawna
    p->size = (Vector2){ 2.5f * p->sprite.width, 2.5f * p->sprite.height}; // tamanho do personagem
    p->speed = moveSpeed;
    p->jumpForce = jumpForce;
    p->velY = 0.0f; // controla a velocidade do personagem no eixo Y
    p->isGround = false;
    p->isActive = active; // alterna entre os personagens
    p->isLeft = false; // controla a direção do personagem
}

void PlayerUpdate(Player *p, float dt, float groundY)
{   
    // movimentacao do personagem
    if(p->isActive){
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
            p->pos.x += p->speed * dt;
            p->isLeft = false;
        }
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            p->pos.x -= p->speed * dt;
            p->isLeft = true;
        }

        if((IsKeyPressed(KEY_UP) || IsKeyDown(KEY_W)) && p->isGround) {
            p->velY = -p->jumpForce;
            p->isGround = false;
        }
    }

    //gravidade
    p->velY += GRAVITY * dt;
    p->pos.y += p->velY * dt;

    //verifica se o personagem esta no chao
    if (p->pos.y + (p->size.y / 2.0f) >= groundY) {
        p->pos.y = groundY - (p->size.y / 2.0f);
        p->velY = 0;
        p->isGround = true;
    }
}

void PlayerDraw(const Player *p)
{
    Rectangle dest = { p->pos.x, p->pos.y, p->size.x, p->size.y}; //Define o tamanho na tela

    Vector2 origin = { dest.width / 2, dest.height / 2}; // define o meio do sprite como ponto de origem / pivot -> Muito útil é bom lembrar disso

    Rectangle corte; // o sprite em um spritesheet

    if (p->isLeft) {
        corte = (Rectangle){ 0, 0, -p->sprite.width, p->sprite.height }; // negativa / esquerda
    } else {
        corte = (Rectangle){ 0, 0, p->sprite.width, p->sprite.height }; // postiva / direita
    }

    //Desenha o sprite na tela
    DrawTexturePro(p->sprite, corte, dest, origin, 0.0f, WHITE);
}