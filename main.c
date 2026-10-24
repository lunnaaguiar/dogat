#include "raylib.h"
#include "player.h"

int main(void) {
    InitWindow(1280, 720, "Dogat");
    SetWindowPosition(100, 100);
    SetTargetFPS(60);

    Player dog, cat;
    PlayerInit(&dog, "assets/metagross.png", (Vector2){ 100, 100 }, true);
    dog.facesLeft = false;
    dog.jumpForce = 400.0f;
    PlayerInit(&cat, "assets/gatinho2-Sheet.png", (Vector2){ 200, 100 }, false);
    cat.jumpForce = 600.0f; // altura que o gato pula
    cat.facesLeft = true; // pq desenhei do lado contrário

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if (IsKeyPressed(KEY_SPACE)) {
            dog.isActive = !dog.isActive;
            cat.isActive = !cat.isActive;
        }

        PlayerUpdate(&dog, dt);
        PlayerUpdate(&cat, dt);

        BeginDrawing();
        ClearBackground(BLACK);
        DrawLine(0, 600, 1280, 600, WHITE);
        PlayerDraw(&dog);
        PlayerDraw(&cat);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}