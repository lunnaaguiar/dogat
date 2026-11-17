#ifndef TEMPO_H
#define TEMPO_H

typedef struct
{
    float min;
    float sec;
    float ms;
} Time;

void SalvarTempo(Time *time);
void AtualizarTempo(Time *time, float dt);
void TimeDraw(const Time *time);

#endif