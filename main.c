#include "raylib.h"
#include "player.h"
#include "interactable.h"
#include "mapa.h"

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

    Caixa caixa = {{64,0, 64,64}};

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if (IsKeyPressed(KEY_SPACE)) {
            dog.isActive = !dog.isActive;
            cat.isActive = !cat.isActive;
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
        DrawRectangleRec(caixa.rect, RED);
        
        EndDrawing();

    }

    CloseWindow();
    return 0;
}