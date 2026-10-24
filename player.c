#include "player.h"

#define GRAVITY   600.0f // gravidade
#define GROUND_Y  600.0f // chao

void PlayerInit(Player *p, const char *spritePath, Vector2 start, bool active) //adicionar aqui as variaveis para os personagem(ex: jumpforce, speed, etc)
{
    p->sprite = LoadTexture(spritePath); // coloca o sprite do personagem
    SetTextureFilter(p->sprite, TEXTURE_FILTER_POINT); // pixel art nítida

    // animação
    p->totalFrames = 2; // pois tem 2 frames no spritesheet
    p->frameAtual = 0; // primeiro frame
    p->frameTimer = 0.0f; // contagem do tempo do frame
    p->frameDuration = 0.5f; // duração de cada frame
    p->frameWidth = p->sprite.width / p->totalFrames; // divide a imagem inteira pelo total de frames (2)
    p->frameHeight = p->sprite.height; // a altura 32x
    p->isMoving = false;

    // personagem
    p->pos = start; // onde ele spawna
    p->size = (Vector2){ 2.5f * p->frameWidth, 2.5f * p->frameHeight }; // tamanho do personagem
    p->speed = 220.0f;
    p->jumpForce = 500.0f;
    p->velY = 0.0f; // controla a velocidade do personagem no eixo Y
    p->isGround = false;
    p->isActive = active; // alterna entre os personagens
    p->isLeft = false; // controla a direção do personagem
    p->facesLeft = false;   // padrão: sprite olha pra direita
}

void PlayerUpdate(Player *p, float dt)
{   
    p->isMoving = false;

    // movimentacao do personagem
    if(p->isActive){
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
            p->pos.x += p->speed * dt;
            p->isLeft = false;
            p->isMoving = true;
        }
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            p->pos.x -= p->speed * dt;
            p->isLeft = true;
            p->isMoving = true;
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
    if (p->pos.y + (p->size.y / 2.0f) >= GROUND_Y) {
        p->pos.y = GROUND_Y - (p->size.y/ 2.0f);
        p->velY = 0;
        p->isGround = true;
    }

    // animação
    if (p->isMoving){
        p->frameTimer += dt; // calcula o tempo em segundos desde o último frame
        if (p->frameTimer >= p->frameDuration){
            p->frameTimer = 0.0f;
            p->frameAtual = (p->frameAtual + 1) % p->totalFrames;
        }
    } else {
            p->frameAtual = 0; // se estiver parado, volta pro frame inicial
            p->frameTimer = 0.0f; 
        }

}

void PlayerDraw(const Player *p)
{
    Rectangle dest = { p->pos.x, p->pos.y, p->size.x, p->size.y}; //Define o tamanho na tela

    Vector2 origin = { dest.width / 2, dest.height / 2}; // define o meio do sprite como ponto de origem / pivot -> Muito útil é bom lembrar disso

    Rectangle corte = { // o sprite em um spritesheet
        // { x, y, largura, altura }
        (float)(p->frameAtual * p->frameWidth), // x
        0, // y
        (float)((p->isLeft != p->facesLeft) ? -p->frameWidth : p->frameWidth), // largura
        (float)p->frameHeight // altura
    }; 

    //if (p->isLeft) {
    //    corte = (Rectangle){ 0, 0, -p->sprite.width, p->sprite.height }; // negativa / esquerda
    //} else {
    //    corte = (Rectangle){ 0, 0, p->sprite.width, p->sprite.height }; // postiva / direita
    //}

    //Desenha o sprite na tela
    DrawTexturePro(p->sprite, corte, dest, origin, 0.0f, WHITE);
}