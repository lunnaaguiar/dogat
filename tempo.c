#include "tempo.h"
#include "stdio.h"
#include "raylib.h"

// manipulação de arquivos: salvar tempo no Score.txt
void SalvarTempo(Time *time) {
    FILE *arq = fopen("Score.txt", "a");
    if (arq == NULL) {
        return;
    }
    fprintf(arq, "%02d:%02d:%02d\n", (int)time->min, (int)time->sec, (int)time->ms);
    fclose(arq);
}

void AtualizarTempo(Time *time, float dt){
    //Timer
    time->ms += dt * 1000.0f;
    
    if(time->ms >= 1000.0f) {
        time->ms = 0.0f;
        time->sec += 1.0f;
    }   
    if(time->sec >= 60.0f) {
        time->sec = 0.0f;
        time->min += 1.0f;
    }
}

void TimeDraw(const Time *time){
    DrawText(TextFormat("Time: %02d:%02d:%02d", (int)time->min, (int)time->sec, (int)time->ms), 10, 40, 20, WHITE);
}