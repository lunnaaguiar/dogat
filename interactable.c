#include "interactable.h"
#include "mapa.h"

float MoveTowards(float current, float destiny, float speed)
{
    if (current < destiny)
    {
        current += speed;
        if (current > destiny) current = destiny;
    }
    else if (current > destiny)
    {
        current -= speed;
        if (current < destiny) current = destiny;
    }

    return current;
}

void ButtonUpdate(Button *button, Player *player, float dt){

    float speed = 150;

    if(CheckCollisionRecs(button->rect, player->hitbox)){
        button->block->y = MoveTowards(button->block->y, 200, speed * dt);
    }else{ 
        button->block->y = MoveTowards(button->block->y, 400, speed * dt);
    }
}

void ButtonDraw(Button *button, Color cor){
    DrawRectangleRec(button->rect, cor);
}

static void ResolverColisaoCaixaY(Caixa *c, Rectangle tile){
    if(!CheckCollisionRecs(c->rect, tile)) return;

    if(c->velY > 0){    // caindo
        c->rect.y = tile.y - c->rect.height;
        c->isGround = true;
        c->velY = 0;
    }
}

static void ResolverColisaoCaixaX(Caixa *c, float dx, Rectangle tile){
    if(!CheckCollisionRecs(c->rect, tile)) return;

    if(dx > 0){
        // [caixa][tile]
        // c->rect.x + c->rect.width = tile.x
        // c->rect.x = tile.x - c->rect.width 
        c->rect.x = tile.x - c->rect.width;
    }else if(dx < 0){
        // [tile][caixa]
        // c->rect.x = tile.x + tile.width
        c->rect.x = tile.x + tile.width;
    }
}

void CaixaUpdate(Caixa *c, float dt){
    c->isGround = false;
    c->velY += GRAVITY * dt;    // 1) gravidade muda a velocidade
    c->rect.y += c->velY * dt;   // 2) velocidade muda a posição

    // colisão
    // colisão com os tiles do mapa x
    for(int i=0; i<MAP_H; i++){
        for(int j=0; j<MAP_W; j++){
            if (mapa[i][j] == 1){
                Rectangle tile = {j*TILE_SIZE, i*TILE_SIZE, TILE_SIZE, TILE_SIZE};
                ResolverColisaoCaixaY(c, tile);
            }
        }
    }

}


void empurrarCaixa(Player *dog, Caixa *caixa){ // usar hitbox do cachorro para empurrar e subir na caixa

    if (!CheckCollisionRecs(dog->hitbox, caixa->rect)) return; // se não colidiu, retorna

    
    float peAgora  = dog->hitbox.y + dog->hitbox.height;    // posição da base (pé) do cachorro  
    float desceu   = dog->pos.y - dog->posAntes.y;          // quanto o cachorro desceu (Y)
    float peAntes  = peAgora - desceu;                      // guarda a posição: onde o pé tava antes 

    if(dog->velY > 0 && peAntes <= caixa->rect.y + 1.0f){   // se o cachorro estaava caindo E pés estavam em cima da caixa + margem de segurança
        float correcao = caixa->rect.y - peAgora;   //  calcula quanto o pé do cachorro passou da caixa 
        dog->pos.y += correcao;       
        dog->hitbox.y += correcao;
        dog->velY = 0;
        dog->isGround = true;     
        return;
    }

    float dx = dog->pos.x - dog->posAntes.x;

    if (dx > 0) caixa->rect.x = dog->hitbox.x + dog->hitbox.width;          // andando pra direita    
    else if (dx < 0) caixa->rect.x = dog->hitbox.x - caixa->rect.width;     // andando pra esquerda
    else return;                                                            // parado

    // onde a caixa iria se atravessasse as paredes
    float posHipotetica = caixa->rect.x;

    for(int i=0; i<MAP_H; i++){
        for(int j=0; j<MAP_W; j++){
            if (mapa[i][j] == 1){
                Rectangle tile = {j*TILE_SIZE, i*TILE_SIZE, TILE_SIZE, TILE_SIZE};
                ResolverColisaoCaixaX(caixa, dx, tile);;
            }
        }
    }

    // aplicar a correção de posicionamento no cachorro | o que foi "empurrado", volta
    float correcao = caixa->rect.x - posHipotetica;   // onde ficou − onde ia
    dog->pos.x    += correcao;
    dog->hitbox.x += correcao;
}