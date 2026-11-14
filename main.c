#include "raylib.h"
#include "player.h"
#include "interactable.h"
#include "stdio.h"
#include "mapa.h"

static void SalvarTempo(float min, float sec, float ms) {
    FILE *arq = fopen("Score.txt", "a");
    if (arq == NULL) {
        return;
    }
    fprintf(arq, "%02d:%02d:%02d\n", (int)min, (int)sec, (int)ms);
    fclose(arq);
}

int main(void) {
    InitWindow(TILE_SIZE*MAP_W, TILE_SIZE*MAP_H, "Dogat"); // 1280x800 (40x25 tiles)
    SetWindowPosition(100, 100);
    SetTargetFPS(60);
    int currentMap = 0;
    bool finishedGame = false;
    bool canGoNext = true;

    MapaLoad(currentMap);

    Player dog, cat;
    // cachorro
    PlayerInit(&dog, "assets/cachorrinho2-Sheet.png",
        configMapa.dogSpawn, true,  4.0f, (Vector2){0.8f, 0.6f});
    dog.facesLeft = false;
    dog.jumpForce = 400.0f;
    // dog.size = (Vector2){ 4.0f * dog.frameWidth, 4.0f * dog.frameHeight }; // substitui pelo parametro 'escala' 
    // gato
    PlayerInit(&cat, "assets/gatinho2-Sheet.png",     
        configMapa.catSpawn, false, 2.5f, (Vector2){0.7f, 0.9f});
    cat.jumpForce = 600.0f; // altura que o gato pula
    cat.facesLeft = true; // pq desenhei do lado contrário

    // elementos interativos
    Caixa caixa;
    CaixaInit(&caixa, "assets/caixa-Sheet.png", 64, (Vector2){10,0});
    caixa.rect = configMapa.box;

    float min = 0.0f, sec = 0.0f, ms = 0.0f;


    Rectangle catBlock = configMapa.catBlock;
    Rectangle dogBlock = configMapa.dogBlock;

    Button catButton = {
        configMapa.catButton, &catBlock
    };

    Button dogButton = {
        configMapa.dogButton, &dogBlock
    };

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        //Timer
        ms += dt * 1000.0f;
        
        if(ms >= 1000.0f) {
            ms = 0.0f;
            sec += 1.0f;
        }
        if(sec >= 60.0f) {
            sec = 0.0f;
            min += 1.0f;
        }

        if (IsKeyPressed(KEY_SPACE)) {
            dog.isActive = !dog.isActive;
            cat.isActive = !cat.isActive;
        }

        if (IsKeyPressed(KEY_M)){
            SalvarTempo(min, sec, ms);
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
        carregarPlayerMulti(&dog, &cat); // colisão pro gato subir no cachorro

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

        if (levelComplete && canGoNext) {
            currentMap++;

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
        DrawText(TextFormat("x: %d  y: %d", GetMouseX(), GetMouseY()), 10, 70, 20, YELLOW);
        ClearBackground(BLACK);
        DrawMapa(); // repetição que desenha cada tile
        DrawSaidas();
        ButtonDraw(&catButton, PURPLE);
        ButtonDraw(&dogButton, BLUE);

        DrawRectangleRec(catBlock, GRAY);
        DrawRectangleRec(dogBlock, GRAY);
        DrawLine(0, 600, 1280, 600, WHITE);
        PlayerDraw(&cat);
        PlayerDraw(&dog);
        
        DrawRectangleRec(parede, WHITE);
        // DrawRectangleRec(caixa.rect, RED);
        CaixaDraw(&caixa);
        DrawText(TextFormat("Time: %02d:%02d:%02d", (int)min, (int)sec, (int)ms), 10, 40, 20, WHITE);
        
        EndDrawing();

    }

    CloseWindow();
    return 0;
}