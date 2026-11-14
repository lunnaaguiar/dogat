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

void ButtonUpdate(Button *button, Player *player, float dt, float iniPos, float destiny){

    float speed = 100;

    if(CheckCollisionRecs(button->rect, player->hitbox)){
        button->block->y = MoveTowards(button->block->y, destiny, speed * dt);
    }else{ 
        button->block->y = MoveTowards(button->block->y, iniPos, speed * dt);
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

void CaixaInit(Caixa *c, char *spritePath, float size, Vector2 pos){

    c->sprite = LoadTexture(spritePath); // coloca o sprite do personagem
    SetTextureFilter(c->sprite, TEXTURE_FILTER_POINT); // pixel art nítida

    // tamanho
    c->rect.width = size;
    c->rect.height = size;
    
    // posição no spawn
    c->rect.x = pos.x;
    c->rect.y = pos.y;

    // padrões
    c->velY = 0;
    c->isGround = false;

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

void EmpurrarCaixa(Player *p, Caixa *caixa, bool forca, Player *gato){ // usar hitbox do cachorro para empurrar e subir na caixa
                                                        // o cachorro precisa conhecer o gato
                                                        // para o gato -> recebe NULL
    p->emCimaCaixa = false;   // atualiza

    if (!CheckCollisionRecs(p->hitbox, caixa->rect)) return; // se não colidiu, retorna

    float peAgora  = p->hitbox.y + p->hitbox.height;        // posição da base (pé) do bichinho  
    float desceu   = p->pos.y - p->posAntes.y;              // quanto o bichinho desceu (Y)
    float peAntes  = peAgora - desceu;                      // guarda a posição: onde o pé tava antes 

    if(p->velY > 0 && peAntes <= caixa->rect.y + 1.0f){     // se o bichinho estava caindo E pés estavam em cima da caixa + margem de segurança
        float correcao = caixa->rect.y - peAgora;           //  calcula quanto o pé do bichinho passou da caixa 
        p->pos.y += correcao;       
        p->hitbox.y += correcao;
        p->velY = 0;
        p->isGround = true;
        
        p->emCimaCaixa = true;
        return;
    }

    float dx = p->pos.x - p->posAntes.x;
    if(dx==0) return;                                                           // parado (não faz nada)
    
    // se forte (cachorro)
    if(forca){
        float caixaAntes = caixa->rect.x;
        if (dx > 0) caixa->rect.x = p->hitbox.x + p->hitbox.width;              // andando pra direita    
        else caixa->rect.x = p->hitbox.x - caixa->rect.width;                   // andando pra esquerda                      
        
        // onde a caixa iria se atravessasse as paredes
        float posHipotetica = caixa->rect.x;

        // caixa empurra gato
        if(gato && CheckCollisionRecs(gato->hitbox, caixa->rect) && !gato->emCimaCaixa){
            float xCorreto;
            if (dx > 0) xCorreto = caixa->rect.x + caixa->rect.width;       // direita -- gato na frente da caixa
            else        xCorreto = caixa->rect.x - gato->hitbox.width;      // esquerda - gato atrás da caixa

            float correcao = xCorreto - gato->hitbox.x;
            gato->pos.x    += correcao;
            gato->hitbox.x += correcao;
        }

        // colisão com mapa
        for(int i=0; i<MAP_H; i++){
            for(int j=0; j<MAP_W; j++){
                if (mapa[i][j] == 1){
                    Rectangle tile = {j*TILE_SIZE, i*TILE_SIZE, TILE_SIZE, TILE_SIZE};
                    ResolverColisaoCaixaX(caixa, dx, tile);;
                }
            }
        }

        float correcao = caixa->rect.x - posHipotetica;             // correção do cachorro tem posHipotetica, porque ele "atravessa caixa"
        p->pos.x    += correcao;
        p->hitbox.x += correcao;

        if(gato && gato->emCimaCaixa){
            float andou = caixa->rect.x - caixaAntes;   // diferença com base na caixa
            gato->pos.x += andou;                       // o gato precisa andar também quando o cachorro empurra a caixa
            gato->hitbox.x += andou;                    // atualizar hitbox do gato
        }             

    }else{ 
        // gato não empurra caixa
        float xCorreto;
        if (dx > 0) xCorreto = caixa->rect.x - p->hitbox.width;     // bateu pela esquerda
        else        xCorreto = caixa->rect.x + caixa->rect.width;   // bateu pela direita

        float correcao = xCorreto - p->hitbox.x;
        p->pos.x    += correcao;
        p->hitbox.x += correcao;
    }
}

void CaixaDraw(const Caixa *c)
{
    //Desenha o sprite na tela
    DrawTexturePro(c->sprite, (Rectangle){0,0,c->sprite.width,c->sprite.height}, c->rect, (Vector2){0,0}, 0, WHITE);
    
    // hitbox
    // DrawRectangleLinesEx(c->rect, 2, RED); // só p visualizar
}