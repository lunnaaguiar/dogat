#include "raylib.h"
#include "player.h"
// #include "mapa.c"

int main(void) {
    InitWindow(1000, 1000, "Dogat");
    SetTargetFPS(60);

    Player dog, cat;
    PlayerInit(&dog, "assets/metagross.png", (Vector2){ 100, 100 }, true);
    PlayerInit(&cat, "assets/absol.png", (Vector2){ 200, 100 }, false);

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
        carregarPlayerMulti(&dog, &cat);
        
        BeginDrawing();
        
        ClearBackground(BLACK);

        PlayerDraw(&dog);
        PlayerDraw(&cat);
        
        DrawRectangleRec(parede, WHITE);
        
        EndDrawing();

    }

    CloseWindow();
    return 0;
}