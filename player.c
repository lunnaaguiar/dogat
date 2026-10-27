#include "player.h"

#define GRAVITY   600.0f // gravidade
#define GROUND_Y  1000.0f // chao

// fazer a hitbox andar junto com o personagem
static void AtualizarHitbox(Player *p){

    p->hitbox.x = p->pos.x + p->hitboxOffset.x;
    p->hitbox.y = p->pos.y + p->hitboxOffset.y;
}

static void ResolverColisaoX(Player *p, float dx, Rectangle obstaculo)
{
    // n faz nd
    if (!CheckCollisionRecs(p->hitbox, obstaculo)) return;

    float xCorreto;

    if (dx > 0) {
        xCorreto = obstaculo.x - p->hitbox.width;   // pela esquerda
    } else if (dx < 0) {
        xCorreto = obstaculo.x + obstaculo.width;   // pela direita
    } else {
        return; // n foi x
    }

    float correcao = xCorreto - p->hitbox.x; // dif
    p->pos.x += correcao;                    // mexeu em pos
    AtualizarHitbox(p);                      // atualiza hitbox
}

static void ResolverColisaoY(Player *p, Rectangle bloco){

    if (!CheckCollisionRecs(p->hitbox, bloco)) return;

    float yCorreto;

    if ( p->velY > 0 ) { //caindo
        // caindo: pousou em cima do bloco
        yCorreto = bloco.y - p->hitbox.height; // negativo sobe

        p->velY = 0;// zera a velocidade vertical
        p-> isGround = true;// marca que está no chão

    } else if ( p->velY < 0 ) { // subindo
        // subindo: bateu a cabeça embaixo do bloco
        yCorreto = bloco.y + bloco.height;     // positivo desce
        
        p->velY = 0;// zera a velocidade vertical

    } else {
        return;
    }

    float correcao = yCorreto - p->hitbox.y;
    p->pos.y += correcao;
    AtualizarHitbox(p);
}

void PlayerInit(Player *p, const char *spritePath, Vector2 start, bool active) //adicionar aqui as variaveis para os personagem(ex: jumpforce, speed, etc)
{
    p->sprite = LoadTexture(spritePath); // coloca o sprite do personagem
    p->pos = start; // onde ele spawna
    p->size = (Vector2){ 2.5f * p->sprite.width, 2.5f * p->sprite.height}; // tamanho do personagem
    p->speed = 220.0f;
    p->jumpForce = 500.0f;
    p->velY = 0.0f; // controla a velocidade do personagem no eixo Y
    p->isGround = false;
    p->isActive = active; // alterna entre os personagens
    p->isLeft = false; // controla a direção do personagem
    
    // tamanho da hitbox
    p->hitbox.width = p->size.x * 0.7f;
    p->hitbox.height = p->size.y * 0.9f; // deixar positivo
    
    //
    p->hitboxOffset.x = -p->hitbox.width / 2.0f;
    p->hitboxOffset.y = -p->hitbox.height / 2.0f;

    // atualizar hitbox
    AtualizarHitbox(p);
}

void PlayerUpdate(Player *p, float dt, Rectangle parede)
{   
    float dx = 0;

    // movimentacao do personagem
    if(p->isActive){
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
            dx += p->speed * dt;
            p->isLeft = false;
        }
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            dx -= p->speed * dt;
            p->isLeft = true;
        }

        if((IsKeyPressed(KEY_UP) || IsKeyDown(KEY_W)) && p->isGround) {
            p->velY = -p->jumpForce;
            p->isGround = false;
        }
    }

    p->pos.x += dx;

    // atualizar hitbox x
    AtualizarHitbox(p); 
    ResolverColisaoX(p, dx, parede);

    // parte do x ^^^^^

    // parte do y
    //  |
    //  V
    p->isGround = false;

    //gravidade
    p->velY += GRAVITY * dt;
    p->pos.y += p->velY * dt; // move

    //verifica se o personagem esta no chao
    if (p->pos.y + (p->size.y / 2.0f) >= GROUND_Y) {
        p->pos.y = GROUND_Y - (p->size.y/ 2.0f);
        p->velY = 0;
        p->isGround = true;
    }
    
    // atualizar hitbox y
    AtualizarHitbox(p); 
    ResolverColisaoY(p, parede);
    
    

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

    // hitbox
    DrawRectangleLinesEx(p->hitbox, 2, RED); // só p visualizar
}