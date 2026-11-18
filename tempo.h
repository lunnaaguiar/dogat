#ifndef TEMPO_H
#define TEMPO_H

typedef struct
{
    float min;
    float sec;
    float ms;
}Tempo;

void SalvarTempo(Tempo *tempo);
void AtualizarTempo(Tempo *tempo, float dt);
void TimeDraw(const Tempo *tempo);

#endif