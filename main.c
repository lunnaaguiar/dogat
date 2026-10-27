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

        PlayerUpdate(&dog, dt, parede); // adicionei +1 parametro
        PlayerUpdate(&cat, dt, parede);

        BeginDrawing();
        // DrawLine(0, 1000, 1920, 1000, WHITE); // marcar o chão 
        ClearBackground(BLACK);

        PlayerDraw(&dog);
        PlayerDraw(&cat);
        
        DrawRectangleRec(parede, WHITE);
        if (CheckCollisionRecs(dog.hitbox, parede)) {
            DrawText(TextFormat("colidiu"), 200, 80, 20, RED);
        }
        
        EndDrawing();

    }

    CloseWindow();
    return 0;
}