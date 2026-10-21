#include "raylib.h"
#include "player.h"

int main(void) {
    InitWindow(1920, 1080, "Dogat");
    SetTargetFPS(60);

    Player dog, cat;
    PlayerInit(&dog, "assets/metagross.png", (Vector2){ 100, 100 }, 120.0f, 300.0f, true);
    PlayerInit(&cat, "assets/absol.png", (Vector2){ 200, 100 }, 220.0f, 500.0f, false);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if (IsKeyPressed(KEY_SPACE)) {
            dog.isActive = !dog.isActive;
            cat.isActive = !cat.isActive;
        }

        PlayerUpdate(&dog, dt);
        PlayerUpdate(&cat, dt);

        BeginDrawing();
        DrawLine(0, 1000, 1920, 1000, WHITE);
        ClearBackground(BLACK);
        PlayerDraw(&dog);
        PlayerDraw(&cat);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}