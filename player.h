#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <stdbool.h>

typedef struct {
    Vector2 pos;
    Vector2 size;
    float speed;
    float jumpForce;
    float velY; // controla a velocidade do personagem no eixo Y
    bool isGround;
    bool isActive; // alterna entre os personagens
    bool isLeft; // controla a direção do personagem
    
    Vector2 hitboxOffset;   // distancia do centro para a borda da hitbox   
    Rectangle hitbox;       // delimita hitbox 
    Vector2 posAntes;       // salvar a posição antes da atualização
    bool emCimaDog;         // avisa que o gatinho está em cima  
    bool emCimaCaixa;
    bool facesLeft;   // true se o desenho original olha pra esquerda

    Texture2D sprite; // coloca o sprite do personagem

    // animação
    int totalFrames; // quantos frames tem no spritesheet
    int frameAtual; // frame atual
    float frameTimer; // acumulando o tempo
    float frameDuration; // segundos por frame
    int frameWidth; // largura de um frame
    int frameHeight; // altura de um frame
    bool isMoving; // só é animado se estiver andando

} Player;


// personagem, onde ele spawna, tamanho do sprite e se ele começa ativo ou não
void PlayerInit(Player *p, const char *spritePath, Vector2 start, bool active, float escala, Vector2 hitboxTam);
//Declaração das funções para usar no player.c
void PlayerUpdate(Player *p, float dt, Rectangle parede);
void PlayerDraw(const Player *p);
void carregarPlayerMulti(Player * dog, Player * cat);

#endif