#include "estados.h"
#include <stdio.h>

// #include "player.h"
// #include "interactable.h"

// 0 - ATTRACT MODE

void AttractModeUpdate(Attract *attract, float dt){
    /* - - - - - - gato - - - - - - */
    /* - - - - - - - - - - - - - - - */
    attract->movCat.tempo -= dt;
    
    // se o tempo restante do gato acabar:
    if(attract->movCat.tempo <= 0){
        attract->movCat.direcao = GetRandomValue(-1, 1); // -1 = esquerda | 1 = direita | 0 = como está
        attract->movCat.tempo = GetRandomValue(1,2);
        
        // pulo aleatório
        int pula = GetRandomValue(0,1); // sim ou não :O
        if(pula == 1 && attract->cat.isGround == true){

            attract->cat.jumpForce = GetRandomValue(400, 600);
            attract->cat.velY = -attract->cat.jumpForce;
            attract->cat.isGround = false;
            // som do pulo
            PlaySound(attract->cat.som.pulo);
        }
    } 

    // gravidade e pulo
    attract->cat.velY += GRAVITY * dt;
    attract->cat.pos.y += attract->cat.velY * dt;


    // troca a direção após sorteio
    if(attract->movCat.direcao == -1) attract->cat.isLeft = true;
    else if(attract->movCat.direcao == 1) attract->cat.isLeft = false;  

    if ((attract->cat.pos.y + attract->cat.size.y/2) >= 576) {
        attract->cat.pos.y = 576 - attract->cat.size.y/2;
        attract->cat.velY = 0;
        attract->cat.isGround = true;
    }

    if(attract->cat.pos.x <= 0) attract->movCat.direcao = 1;
    else if(attract->cat.pos.x >= 1280) attract->movCat.direcao = -1;

    attract->cat.pos.x += attract->movCat.direcao * attract->cat.speed * dt; // anda

    // animação
    attract->cat.isMoving = (attract->movDog.direcao != 0);

    if (attract->cat.isMoving){
        attract->cat.frameTimer += dt;
        if (attract->cat.frameTimer >= attract->cat.frameDuration){
            attract->cat.frameTimer = 0.0f;
            attract->cat.frameAtual = (attract->cat.frameAtual + 1) % attract->cat.totalFrames;
        }
    } else {
        attract->cat.frameAtual = 0;
        attract->cat.frameTimer = 0.0f;
    }
    /* - - - - - - - - - - - - - - - */


    /* - - - - - - cachorro - - - - - - */
    /* - - - - - - - - - - - - - - - */
    attract->movDog.tempo -= dt;
    
    // se o tempo restante do cachorro acabar:
    if(attract->movDog.tempo <= 0){
        attract->movDog.direcao = GetRandomValue(-1, 1); // -1 = esquerda | 1 = direita | 0 = como está
        attract->movDog.tempo = GetRandomValue(1,2);
        
        // pulo aleatório
        int pula = GetRandomValue(0,1); // sim ou não :O
        if(pula == 1 && attract->dog.isGround == true){

            attract->dog.jumpForce = GetRandomValue(400, 600);
            attract->dog.velY = -attract->dog.jumpForce;
            attract->dog.isGround = false;
            // som do pulo
            PlaySound(attract->dog.som.pulo);
        }
    } 

    // gravidade e pulo
    attract->dog.velY += GRAVITY * dt;
    attract->dog.pos.y += attract->dog.velY * dt;


    // troca a direção após sorteio
    if(attract->movDog.direcao == -1) attract->dog.isLeft = true;
    else if(attract->movDog.direcao == 1) attract->dog.isLeft = false;  

    if ((attract->dog.pos.y + attract->dog.size.y/2) >= 576) {
        attract->dog.pos.y = 576 - attract->dog.size.y/2;
        attract->dog.velY = 0;
        attract->dog.isGround = true;
    }

    if(attract->dog.pos.x <= 0) attract->movDog.direcao = 1;
    else if(attract->dog.pos.x >= 1280) attract->movDog.direcao = -1;

    attract->dog.pos.x += attract->movDog.direcao * attract->dog.speed * dt; // anda

    // animação
    attract->dog.isMoving = (attract->movDog.direcao != 0);

    if (attract->dog.isMoving){
        attract->dog.frameTimer += dt;
        if (attract->dog.frameTimer >= attract->dog.frameDuration){
            attract->dog.frameTimer = 0.0f;
            attract->dog.frameAtual = (attract->dog.frameAtual + 1) % attract->dog.totalFrames;
        }
    } else {
        attract->dog.frameAtual = 0;
        attract->dog.frameTimer = 0.0f;
    }
    /* - - - - - - - - - - - - - - - */

}

void AttractModeDraw(const Attract *attract){
    ClearBackground(BLACK);

    // desenhar os bichinhos
    PlayerDraw(&attract->dog);
    PlayerDraw(&attract->cat);

    int titulo = (1280 - MeasureText("DOGAT", 50)) /2;
    int texto = (1280 - MeasureText("- Aperte ENTER para iniciar -", 22)) /2;
    DrawText("DOGAT", titulo, 680, 50, WHITE);
    if ( (int) GetTime() %2 == 0) DrawText("- Aperte ENTER para iniciar -", texto, 736, 22, WHITE);
}

// 1 - PLAYING
void PlayingUpdate(Jogo *jogo, float dt)
{
    jogo->tempo += dt;
    // obs: inserir função de salvar tempo depois

    // alternar entre personagens
    if (IsKeyPressed(KEY_SPACE))
    {
        jogo->dog.isActive = !jogo->dog.isActive;
        jogo->cat.isActive = !jogo->cat.isActive;
    }

    // player update
    PlayerUpdate(&jogo->dog, dt, jogo->catBlock, jogo->dogBlock);
    PlayerUpdate(&jogo->cat, dt, jogo->catBlock, jogo->dogBlock);

    // colisão e interação com objetos
    CaixaUpdate(&jogo->caixa, dt);
    EmpurrarCaixa(&jogo->dog, &jogo->caixa, true, &jogo->cat);
    EmpurrarCaixa(&jogo->cat, &jogo->caixa, false, NULL);
    ButtonUpdate(&jogo->catButton, &jogo->cat, dt, configMapa.catBlockIniPos, configMapa.catBlockDestinyPos);
    ButtonUpdate(&jogo->dogButton, &jogo->dog, dt, configMapa.dogBlockIniPos, configMapa.dogBlockDestinyPos);

    // regras do multijogador
    CarregarGato(&jogo->dog, &jogo->cat); // colisão pro gato subir no cachorro

    jogo->dogRect = (Rectangle){
        jogo->dog.pos.x - jogo->dog.size.x / 2,
        jogo->dog.pos.y - jogo->dog.size.y / 2,
        jogo->dog.size.x,
        jogo->dog.size.y
    };

    jogo->catRect = (Rectangle){
        jogo->cat.pos.x - jogo->cat.size.x / 2,
        jogo->cat.pos.y - jogo->cat.size.y / 2,
        jogo->cat.size.x,
        jogo->cat.size.y
    };

    // parte sem função ainda:
    jogo->levelComplete = MapaCompleto(jogo->catRect, jogo->dogRect);
    jogo->catInPuddle = CatTouchedPuddle(configMapa.waterPuddle, &jogo->cat) || IsKeyPressed(KEY_R);

    if (jogo->levelComplete && jogo->canGoNext || jogo->catInPuddle) {
        if(!jogo->catInPuddle) jogo->currentMap++;
        if (MapaLoad(jogo->currentMap)) {
            jogo->dog.pos = configMapa.dogSpawn;
            jogo->cat.pos = configMapa.catSpawn;
            jogo->catBlock = configMapa.catBlock;
            jogo->dogBlock = configMapa.dogBlock;
            jogo->catButton.rect = configMapa.catButton;
            jogo->catButton.block = &jogo->catBlock;
            jogo->dogButton.rect = configMapa.dogButton;
            jogo->dogButton.block = &jogo->dogBlock;
            jogo->caixa.rect = configMapa.box;
        } else {
            jogo->finishedGame = true;
            ScoreInserir(&jogo->score, jogo->tempo);
            ScoreSalvar(&jogo->score, "Score.txt");
            //jogo->tempo = 0.0f;
        }    
        jogo->canGoNext = false;
    }

    if (!jogo->levelComplete) {
        jogo->canGoNext = true;
    }

}

void PlayingDraw(Jogo *jogo)
{
    // BeginDrawing();

    ClearBackground(BLACK);
    // desenha o fundo
    if (jogo->currentMap < 2 && jogo->fundos[jogo->currentMap].id > 0) {
        DrawTexture(jogo->fundos[jogo->currentMap], 0, 0, WHITE);
    } else {
        DrawMapa(); // fase sem imagem ainda: desenha os quadrados brancos
    }
    
    // elementos de interação
    CaixaDraw(&jogo->caixa);
    DrawRectangleRec(jogo->catBlock, PURPLE);
    DrawRectangleRec(jogo->dogBlock, BLUE);

    // DrawMapa(); // repetição que desenha cada tile (puramente visual, a colisão é feita no player.c)


    DrawSaidas();
    DrawSaidas();
    PuddleDraw(configMapa.waterPuddle);
    
    // botões
    ButtonDraw(&jogo->catButton, PURPLE); 
    ButtonDraw(&jogo->dogButton, BLUE);

    // desenhos dos players
    PlayerDraw(&jogo->cat);
    PlayerDraw(&jogo->dog);

    // score
    TempoAtualDraw(jogo->tempo);
    ScoreRankDraw(&jogo->score);

    // EndDrawing(); // finaliza
}

// 2 - VICTORY
#define BTN_W 320
#define BTN_H 70

static Rectangle BotaoJogarNovamente(void)
{
    return (Rectangle){ (1280 - BTN_W) / 2.0f, 450, BTN_W, BTN_H };
}

void JogoReiniciar(Jogo *jogo)
{
    jogo->currentMap = 0;
    MapaLoad(0);

    // mesmas linhas que já existem no PlayingUpdate
    jogo->dog.pos = configMapa.dogSpawn;
    jogo->cat.pos = configMapa.catSpawn;
    jogo->catBlock = configMapa.catBlock;
    jogo->dogBlock = configMapa.dogBlock;
    jogo->catButton.rect = configMapa.catButton;
    jogo->catButton.block = &jogo->catBlock;
    jogo->dogButton.rect = configMapa.dogButton;
    jogo->dogButton.block = &jogo->dogBlock;
    jogo->caixa.rect = configMapa.box;

    jogo->dog.velY = 0;
    jogo->cat.velY = 0;
    jogo->dog.isActive = true;
    jogo->cat.isActive = false;

    jogo->tempo = 0.0f;
    jogo->finishedGame = false;
    jogo->canGoNext = false;
}

bool VictoryUpdate(void)
{
    bool sobre = CheckCollisionPointRec(GetMousePosition(), BotaoJogarNovamente());
    return (sobre && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || IsKeyPressed(KEY_ENTER);
}

void VictoryDraw(const Jogo *jogo)
{
    ClearBackground(BLACK);

    const char *titulo = "VOCÊ VENCEU!";
    DrawText(titulo, (1280 - MeasureText(titulo, 60)) / 2, 250, 60, WHITE);

    char buf[16];
    ScoreFormatar(jogo->tempo, buf, sizeof(buf));
    const char *tempo = TextFormat("Tempo: %s", buf);
    DrawText(tempo, (1280 - MeasureText(tempo, 30)) / 2, 350, 30, YELLOW);

    Rectangle botao = BotaoJogarNovamente();
    bool sobre = CheckCollisionPointRec(GetMousePosition(), botao);
    DrawRectangleRec(botao, sobre ? LIGHTGRAY : GRAY);
    DrawRectangleLinesEx(botao, 3, WHITE);

    const char *texto = "Jogar novamente";
    DrawText(texto, botao.x + (BTN_W - MeasureText(texto, 28)) / 2,
             botao.y + (BTN_H - 28) / 2, 28, BLACK);
}

