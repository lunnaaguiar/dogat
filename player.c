#include "player.h"

#define GRAVITY   600.0f // gravidade
#define GROUND_Y  600.0f // chao

// fazer a hitbox andar junto com o personagem

static void AtualizarHitbox(Player *p){ // multiplicadores

    p->hitbox.x = p->pos.x + p->hitboxOffset.x * p->hitboxPos.x;
    p->hitbox.y = p->pos.y + p->hitboxOffset.y * p->hitboxPos.y; 
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

void carregarPlayerMulti(Player * dog, Player * cat){ // forte, fraco
    // dog = forte
    // cat = fraco

    Vector2 difDog;
    difDog.x = dog->pos.x - dog->posAntes.x;
    difDog.y = dog->pos.y - dog->posAntes.y;
    
    float topoForte = dog->hitbox.y; // cabeça do cachorro
    float pezinhoCatAntes = cat->posAntes.y + cat->hitboxOffset.y + cat->hitbox.height;

    // acabou de cair no dog
    bool pousou = CheckCollisionRecs(cat->hitbox, dog->hitbox)
               && cat->velY > 0
               && pezinhoCatAntes <= topoForte - difDog.y + 1.0f;

    // se ainda estão juntos considerando a largura
    bool sobreDog = cat->hitbox.x < dog->hitbox.x + dog->hitbox.width
                 && cat->hitbox.x + cat->hitbox.width > dog->hitbox.x;

    // salva o estado que impede o gato de cair do cachorro quando atualiza os frames                 
    cat->emCimaDog = pousou || (cat->emCimaDog && cat->velY > 0 && sobreDog);

    if (!cat->emCimaDog) return;

    // posicionamento do gato
    cat->pos.y = topoForte - cat->hitbox.height - cat->hitboxOffset.y;
    cat->pos.x += difDog.x;
    cat->velY = 0;
    cat->isGround = true;

    AtualizarHitbox(cat);

} 

void PlayerInit(Player *p, const char *spritePath, Vector2 start, bool active, Vector2 hitboxPos) //adicionar aqui as variaveis para os personagem(ex: jumpforce, speed, etc)
{
    p->sprite = LoadTexture(spritePath); // coloca o sprite do personagem
    SetTextureFilter(p->sprite, TEXTURE_FILTER_POINT); // pixel art nítida

    // animação
    p->totalFrames = 2; // pois tem 2 frames no spritesheet
    p->frameAtual = 0; // primeiro frame
    p->frameTimer = 0.0f; // contagem do tempo do frame
    p->frameDuration = 0.3f; // duração de cada frame
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
    
    // tamanho da hitbox
    p->hitbox.width = p->size.x * 0.7f;
    p->hitbox.height = p->size.y * 0.9f; // deixar positivo
    p->emCimaDog = false;
    //
    p->hitboxOffset.x = -p->hitbox.width / 2.0f;
    p->hitboxOffset.y = -p->hitbox.height / 2.0f;
    //
    p->hitboxPos.x = hitboxPos.x;
    p->hitboxPos.y = hitboxPos.y;


    // atualizar hitbox
    AtualizarHitbox(p);
    p->facesLeft = false;   // padrão: sprite olha pra direita
}

void PlayerUpdate(Player *p, float dt, Rectangle parede)
{   
    float dx = 0;
    p->isMoving = false;

    // movimentacao do personagem
    if(p->isActive){
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
            dx += p->speed * dt;
            p->isLeft = false;
            p->isMoving = true;
        }
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            dx -= p->speed * dt;
            p->isLeft = true;
            p->isMoving = true;
        }

        if((IsKeyPressed(KEY_UP) || IsKeyDown(KEY_W)) && p->isGround) {
            p->velY = -p->jumpForce;
            p->isGround = false;
        }
    }

    p->posAntes.x = p->pos.x; // salva a posição x antes de atualizar
    p->pos.x += dx;
    
    // atualizar hitbox x
    AtualizarHitbox(p); 
    ResolverColisaoX(p, dx, parede);

    
    // também salva a posição y anterior
    p->posAntes.y = p->pos.y;
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

    // hitbox
    // DrawRectangleLinesEx(p->hitbox, 2, RED); // só p visualizar
}