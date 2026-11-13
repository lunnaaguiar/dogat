#include "raylib.h"
#include "player.h"
#include "interactable.h"
#include "stdio.h"
#include "mapa.h"
#include "score.h"

/*
static void SalvarTempo(float min, float sec, float ms) {
    FILE *arq = fopen("Score.txt", "a");
    if (arq == NULL) {
        return;
    }
    fprintf(arq, "%02d:%02d:%02d\n", (int)min, (int)sec, (int)ms);
    fclose(arq);
}
*/

int main(void) {
    InitWindow(TILE_SIZE*MAP_W, TILE_SIZE*MAP_H, "Dogat"); // 1280x800 (40x25 tiles)
    SetWindowPosition(100, 100);
    SetTargetFPS(60);

    Player dog, cat;
    // cachorro
    PlayerInit(&dog, "assets/cachorrinho2-Sheet.png",
        (Vector2){100, 100}, true,  4.0f, (Vector2){0.8f, 0.6f});
    dog.facesLeft = false;
    dog.jumpForce = 400.0f;
    // dog.size = (Vector2){ 4.0f * dog.frameWidth, 4.0f * dog.frameHeight }; // substitui pelo parametro 'escala' 
    // gato
    PlayerInit(&cat, "assets/gatinho2-Sheet.png",     
        (Vector2){200, 100}, false, 2.5f, (Vector2){0.7f, 0.9f});
    cat.jumpForce = 600.0f; // altura que o gato pula
    cat.facesLeft = true; // pq desenhei do lado contrário

    // float min = 0.0f, sec = 0.0f, ms = 0.0f;
    float tempo = 0.0f;
    
    Score score;
    ScoreInit(&score);                      // deixa a lista vazia
    ScoreCarregar(&score, "Score.txt");   // lê os tempos salvos

    Caixa caixa = {{64,0, 64,64}};
    Texture2D texCaixa = LoadTexture("assets/caixa-Sheet.png");
    SetTextureFilter(texCaixa, TEXTURE_FILTER_POINT);   // pixel art

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        /*Timer
        ms += dt * 1000.0f;
        
        if(ms >= 1000.0f) {
            ms = 0.0f;
            sec += 1.0f;
        }
        if(sec >= 60.0f) {
            sec = 0.0f;
            min += 1.0f;
        }
        */

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

        PlayerUpdate(&dog, dt, parede); 
        PlayerUpdate(&cat, dt, parede);
        CaixaUpdate(&caixa, dt);
        empurrarCaixa(&dog, &caixa);

        // regras do multiplayer (vem depois do playerUpdate)
        carregarPlayerMulti(&dog, &cat); // colisão pro gato subir no cachorro
        
        BeginDrawing();
        DrawMapa(); // repetição que desenha cada tile
        ClearBackground(BLACK);
        DrawLine(0, 600, 1280, 600, WHITE);
        PlayerDraw(&cat);
        PlayerDraw(&dog);
        
        DrawRectangleRec(parede, WHITE);
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