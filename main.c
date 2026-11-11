#include "raylib.h"
#include "player.h"
#include "mapa.c"

int main(void) {
    InitWindow(TILE_SIZE*MAP_W, TILE_SIZE*MAP_H, "Dogat"); // 1280x800 (40x25 tiles)
    SetWindowPosition(100, 100);
    SetTargetFPS(60);

    Player dog, cat;
    // cachorro
    PlayerInit(&dog, "assets/cachorrinho2-Sheet.png", (Vector2){ 100, 100 }, true, (Vector2) {0.8,0.2});
    dog.facesLeft = false;
    dog.jumpForce = 400.0f;
    dog.size = (Vector2){ 4.0f * dog.frameWidth, 4.0f * dog.frameHeight };
    // gato
    PlayerInit(&cat, "assets/gatinho2-Sheet.png", (Vector2){ 200, 100 }, false, (Vector2) {1,1});
    cat.jumpForce = 600.0f; // altura que o gato pula
    cat.facesLeft = true; // pq desenhei do lado contrário

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if (IsKeyPressed(KEY_SPACE)) {
            dog.isActive = !dog.isActive;
            cat.isActive = !cat.isActive;
        }

        Rectangle parede = { 400, GetScreenHeight()-100, 100, 100 };

        PlayerUpdate(&dog, dt, parede); 
        PlayerUpdate(&cat, dt, parede);

        // regras do multiplayer (vem depois do playerUpdate)
        carregarPlayerMulti(&dog, &cat); // colisão pro gato subir no cachorro
        
        BeginDrawing();
        DrawMapa(); // repetição que desenha cada tile
        ClearBackground(BLACK);
        DrawLine(0, 600, 1280, 600, WHITE);
        PlayerDraw(&cat);
        PlayerDraw(&dog);
        
        DrawRectangleRec(parede, WHITE);
        
        EndDrawing();

    }

    CloseWindow();
    return 0;
}