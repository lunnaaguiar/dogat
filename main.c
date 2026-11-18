#include "raylib.h"
#include "player.h"
#include "interactable.h"
#include "stdio.h"
#include "mapa.h"
#include "score.h"

int main(void) {
    InitWindow(TILE_SIZE*MAP_W, TILE_SIZE*MAP_H, "Dogat"); // 1280x800 (40x25 tiles)
    SetWindowPosition(100, 100);
    SetTargetFPS(60);
    int currentMap = 4;
    bool finishedGame = false;
    bool canGoNext = true;

    MapaLoad(currentMap);

    Player dog, cat;
    // cachorro
    PlayerInit(&dog, "assets/cachorrinho2-Sheet.png",
        configMapa.dogSpawn, true,  4.0f, (Vector2){0.8f, 0.6f});
    dog.facesLeft = false;
    dog.jumpForce = 400.0f;

    // gato
    PlayerInit(&cat, "assets/gatinho2-Sheet.png",     
        configMapa.catSpawn, false, 2.5f, (Vector2){0.7f, 0.9f});
    cat.jumpForce = 600.0f; // altura que o gato pula
    cat.facesLeft = true; // pq desenhei do lado contrário

    // elementos interativos
    Caixa caixa = {{64,0, 64,64}};
    CaixaInit(&caixa, "assets/caixa-Sheet.png", 64, (Vector2){10,0});
    caixa.rect = configMapa.box;

    //Lunna
    Texture2D texCaixa = LoadTexture("assets/caixa-Sheet.png");
    SetTextureFilter(texCaixa, TEXTURE_FILTER_POINT);   // pixel art
    
    // float min = 0.0f, sec = 0.0f, ms = 0.0f;
    float tempo = 0.0f;

    Rectangle catBlock = configMapa.catBlock;
    Rectangle dogBlock = configMapa.dogBlock;

    Button catButton = {
        configMapa.catButton, &catBlock
    };

    Button dogButton = {
        configMapa.dogButton, &dogBlock
    };

    Score score;
    ScoreInit(&score);                      // deixa a lista vazia
    ScoreCarregar(&score, "Score.txt");   // lê os tempos salvos

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        tempo += dt;

        if (IsKeyPressed(KEY_SPACE)) {
            dog.isActive = !dog.isActive;
            cat.isActive = !cat.isActive;
        }

        if (IsKeyPressed(KEY_M)){
            ScoreInserir(&score, tempo);
            ScoreSalvar(&score, "Score.txt");
            tempo = 0.0f;
        }

        Rectangle parede = { 400, GetScreenHeight()-100, 100, 100 };

        PlayerUpdate(&dog, dt, catBlock, dogBlock); 
        PlayerUpdate(&cat, dt, catBlock, dogBlock);
        
        CaixaUpdate(&caixa, dt);
        EmpurrarCaixa(&dog, &caixa, true, &cat);
        EmpurrarCaixa(&cat, &caixa, false, NULL);
        ButtonUpdate(&catButton, &cat, dt, configMapa.catBlockIniPos, configMapa.catBlockDestinyPos);
        ButtonUpdate(&dogButton, &dog, dt, configMapa.dogBlockIniPos, configMapa.dogBlockDestinyPos);

        // regras do multiplayer (vem depois do playerUpdate)
        CarregarGato(&dog, &cat); // colisão pro gato subir no cachorro

        Rectangle dogRect = {
            dog.pos.x - dog.size.x / 2,
            dog.pos.y - dog.size.y / 2,
            dog.size.x,
            dog.size.y
        };

        Rectangle catRect = {
            cat.pos.x - cat.size.x / 2,
            cat.pos.y - cat.size.y / 2,
            cat.size.x,
            cat.size.y
        };

        bool levelComplete = MapaCompleto(catRect, dogRect);
        bool catInPuddle = CatTouchedPuddle(configMapa.waterPuddle, &cat);

        if (levelComplete && canGoNext || catInPuddle) {
            if(!catInPuddle) currentMap++;

            if (MapaLoad(currentMap)) {
                dog.pos = configMapa.dogSpawn;
                cat.pos = configMapa.catSpawn;

                catBlock = configMapa.catBlock;
                dogBlock = configMapa.dogBlock;

                catButton = (Button){configMapa.catButton, &catBlock};
                dogButton = (Button){configMapa.dogButton, &dogBlock};

                caixa.rect = configMapa.box;

            } else {
                finishedGame = true;
            }

            canGoNext = false;
        }

        if (!levelComplete) {
            canGoNext = true;
        }
        
        BeginDrawing();
        DrawText(TextFormat("x: %d  y: %d", GetMouseX(), GetMouseY()), 200, 70, 20, YELLOW);
        ClearBackground(BLACK);
        DrawMapa(); // repetição que desenha cada tile
        DrawSaidas();
        PuddleDraw(configMapa.waterPuddle);
        ButtonDraw(&catButton, PURPLE);
        ButtonDraw(&dogButton, BLUE);

        PlayerDraw(&cat);
        PlayerDraw(&dog);
        
        
        DrawRectangleRec(parede, WHITE);
        DrawRectangleRec(catBlock, PURPLE);
        DrawRectangleRec(dogBlock, BLUE);
        DrawTexturePro(texCaixa,
        (Rectangle){ 0, 0, texCaixa.width, texCaixa.height },  // origem: a imagem toda da caixa
        caixa.rect,                                             // destino: onde está a caixa (64x64)
        (Vector2){ 0, 0 },                                      // sem pivô
        0.0f, WHITE);

        char buf[16];
        ScoreFormatar(tempo, buf, sizeof(buf));
        DrawText(TextFormat("Time: %s", buf), 10, 40, 20, WHITE);

        // top 5 do ranking
        int y = 70, pos = 1;
        for (NoScore *n = score.inicio; n != NULL && pos <= 5; n = n->prox, pos++) {
        ScoreFormatar(n->tempo, buf, sizeof(buf));
        DrawText(TextFormat("%d. %s", pos, buf), 10, y, 20, YELLOW);
        y += 24;
        }
        
        EndDrawing();

    }
    UnloadTexture(texCaixa);
    ScoreLiberar(&score);
    CloseWindow();
    return 0;
}