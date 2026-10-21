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

    Texture2D sprite; // coloca o sprite do personagem
} Player;

// personagem, onde ele spawna, tamanho do sprite e se ele começa ativo ou não
//adicionar aqui as variaveis para os personagem(ex: jumpforce, speed, etc)
void PlayerInit(Player *p, const char *spritePath, Vector2 start, float moveSpeed, float jumpForce, bool active);

//Declaração das funções para usar no player.c
void PlayerUpdate(Player *p, float dt);
void PlayerDraw(const Player *p);