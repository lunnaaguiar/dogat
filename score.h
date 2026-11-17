#ifndef SCORE_H
#define SCORE_H

// cada nó da lista guarda o tempo de uma partida em seg
typedef struct NoScore {
    float tempo;
    struct NoScore *prox;   // aponta pro próximo nó (ou NULL)
} NoScore;

typedef struct {
    NoScore *inicio;   // melhor tempo
    int total;         // quantos tempos tem na lista
} Score;

void ScoreInit(Score *recorde);

// insere o tempo na posição certa (menor primeiro).
int  ScoreInserir(Score *recorde, float tempo);

// lê/grava um tempo por linha no arquivo
void ScoreCarregar(Score *recorde, const char *arquivo);
void ScoreSalvar(const Score *recorde, const char *arquivo);

// escreve o tempo no formato MM:SS:mmm
void ScoreFormatar(float tempo, char *buf, int tamanho);


void ScoreLiberar(Score *recorde);

#endif