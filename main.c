#include "raylib.h"
#include "player.h"
#include "levels.h"

static void StartLevel(Level *lv, int idx, Player *dog, Player *cat) {
    LevelLoad(lv, idx);
    dog->pos = lv->dogSpawn;  dog->velY = 0;
    cat->pos = lv->catSpawn;  cat->velY = 0;
}

int main(void) {
    InitWindow(1920, 1080, "Dogat");
    SetTargetFPS(60);

    Player dog, cat;
    PlayerInit(&dog, "assets/metagross.png", (Vector2){ 100, 100 }, 200.0f, 500.0f, true);
    PlayerInit(&cat, "assets/absol.png", (Vector2){ 200, 100 }, 300.0f, 650.0f, false);

    Level level;
    int currentLevel = 0;
    bool gameWon = false;
    StartLevel(&level, currentLevel, &dog, &cat);

    float min = 0.0f, sec = 0.0f, ms = 0.0f;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
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

        PlayerUpdate(&dog, dt, level.groundY);
        PlayerUpdate(&cat, dt, level.groundY);

        if (LevelComplete(&level, &dog, &cat)) {
                currentLevel++;
                if (currentLevel >= LevelCount()) gameWon = true;
                else StartLevel(&level, currentLevel, &dog, &cat);
            }
        
        if (IsKeyPressed(KEY_R)) StartLevel(&level, currentLevel, &dog, &cat); // reiniciar fase

        BeginDrawing();
        ClearBackground(BLACK);
        LevelDraw(&level);
        PlayerDraw(&dog);
        PlayerDraw(&cat);
        DrawText(TextFormat("Time: %02d:%02d:%02d", (int)min, (int)sec, (int)ms), 10, 40, 20, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}