#include "raylib.h"
#include "player.h"
#include "interactable.h"
#include "stdio.h"
#include "mapa.h"
#include "score.h"
#include "estados.h"



int main(void) {
    InitWindow(TILE_SIZE*MAP_W, TILE_SIZE*MAP_H, "Dogat"); // 1280x800 (40x25 tiles)
    InitAudioDevice(); // preparar pra os sons
    SetWindowPosition(100, 100);
    SetTargetFPS(60);
    int currentMap = 2;
    bool finishedGame = false;
    bool canGoNext = true;
    
    // - - - - - - - -
    // música principal
    Music music = LoadMusicStream("assets/sons/time_for_adventure.mp3");
    PlayMusicStream(music);
    
    // struct sons
    Sons efeitosSonorosGato = {
        LoadSound("assets/sons/larchrow-8bit-arcade-sfx_jump_07.wav")
    };
    Sons efeitosSonorosCachorro = {
        LoadSound("assets/sons/larchrow-8bit-arcade-sfx_jump_07.wav")
    };
    // - - - - - - - -

    MapaLoad(currentMap);
    
    Estado estadoAtual = ATTRACT_MODE;
    /* - - - - - - - - - - - - - - - - - - - - -*/
    Jogo jogo = {0};

    jogo.currentMap = currentMap;
    jogo.finishedGame = finishedGame;
    jogo.canGoNext = canGoNext;

    Player dog, cat;
    // cachorro
    PlayerInit(&jogo.dog, "assets/sprites/cachorrinho2-Sheet.png",
        configMapa.dogSpawn, true,  4.0f, (Vector2){0.8f, 0.6f}, efeitosSonorosCachorro);
        jogo.dog.facesLeft = false;
        jogo.dog.jumpForce = 400.0f;

    // gato
    PlayerInit(&jogo.cat, "assets/sprites/gatinho2-Sheet.png",     
        configMapa.catSpawn, false, 2.5f, (Vector2){0.7f, 0.9f}, efeitosSonorosGato);
        jogo.cat.jumpForce = 600.0f; // altura que o gato pula
        jogo.cat.facesLeft = true; // pq desenhei do lado contrário

    // elementos interativos
    CaixaInit(&jogo.caixa, "assets/sprites/caixa-Sheet.png", 64, (Vector2){10,0});    
    jogo.caixa.rect = configMapa.box;

    // TEMPO
    jogo.tempo = 0.0f;
        
    // bloco
    jogo.catBlock = configMapa.catBlock;
    jogo.dogBlock = configMapa.dogBlock;
    // botão
    jogo.catButton = (Button){configMapa.catButton, &jogo.catBlock, 0, 0, LoadTexture("assets/sprites/botao-Sheet.png")};
    jogo.dogButton = (Button){configMapa.dogButton, &jogo.dogBlock, 0, 0, LoadTexture("assets/sprites/botao-Sheet.png")};
    /* - - - - - - - - - - - - - - - - - - - - -*/
    
    /* - - - - - - - - - - - - - - - - - - - - -*/
    Attract attract = {0};
    attract.cat = jogo.cat;
    attract.dog = jogo.dog;

    // cachorro
    PlayerInit(&attract.dog, "assets/sprites/cachorrinho2-Sheet.png",
        configMapa.dogSpawn, true,  6.0f, (Vector2){0.8f, 0.6f}, efeitosSonorosCachorro);
        attract.dog.facesLeft = false;
        attract.dog.jumpForce = 400.0f;
        attract.dog.speed = 400.0f;
        
    // gato
    PlayerInit(&attract.cat, "assets/sprites/gatinho2-Sheet.png",     
        configMapa.catSpawn, false, 3.5f, (Vector2){0.7f, 0.9f}, efeitosSonorosGato);
        attract.cat.jumpForce = 600.0f; // altura que o gato pula
        attract.cat.facesLeft = true; // pq desenhei do lado contrário
        attract.cat.speed = 450.0f;
    /* - - - - - - - - - - - - - - - - - - - - -*/


    ScoreInit(&jogo.score);                      // deixa a lista vazia
    ScoreCarregar(&jogo.score, "Score.txt");     // lê os tempos salvos

    while (!WindowShouldClose()) {
        UpdateMusicStream(music);
        float dt = GetFrameTime();
        if(dt > 0.06) dt = 0.06;
        BeginDrawing();
        switch (estadoAtual)
        {
        case ATTRACT_MODE:
            /* code */
            DrawText("Teste ATTRACT MODE", 10,10, 12, WHITE);
            if (IsKeyPressed(KEY_ENTER)) estadoAtual = PLAYING;
            AttractModeUpdate(&attract, dt);
            AttractModeDraw(&attract);
            break;
            

        case PLAYING:
            PlayingUpdate(&jogo, dt);
            PlayingDraw(&jogo);
            if(jogo.finishedGame) estadoAtual = VICTORY;
            break;

        case VICTORY:
            ClearBackground(BLACK);
            DrawText("VOCÊ GANHOUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", 10,10, 12, WHITE);
            break;

        default:
            break;
        }

        // DrawText(TextFormat("x: %d  y: %d", GetMouseX(), GetMouseY()), 200, 70, 20, YELLOW);

        EndDrawing();
    }
    // UnloadTexture(texCaixa);
    ScoreLiberar(&jogo.score);
    UnloadMusicStream(music);   
    CloseAudioDevice();
    CloseWindow();
    return 0;
}