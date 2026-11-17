#include "score.h"
#include <stdio.h>
#include <stdlib.h>

void ScoreInit(Score *recorde)
{
    recorde->inicio = NULL;
    recorde->total = 0;
}

int ScoreInserir(Score *recorde, float tempo)
{
    NoScore *novo = (NoScore *)malloc(sizeof(NoScore));
    if (novo == NULL) return 0;          // sem memória
    novo->tempo = tempo;

    int posicao = 1;

    if (recorde->inicio == NULL || tempo < recorde->inicio->tempo) {
        // lista vazia ou o novo é melhor
        novo->prox = recorde->inicio;
        recorde->inicio = novo;
    } else {
        // anda até o último que ainda é menor ou igual ao novo
        NoScore *atual = recorde->inicio;
        posicao++;
        while (atual->prox != NULL && atual->prox->tempo <= tempo) {
            atual = atual->prox;
            posicao++;
        }
        novo->prox = atual->prox;        // liga o novo no resto da lista
        atual->prox = novo;              // liga o anterior no novo
    }

    recorde->total++;
    return posicao;
}

void ScoreCarregar(Score *recorde, const char *arquivo)
{
    FILE *f = fopen(arquivo, "r");
    if (f == NULL) return;

    float t;
    while (fscanf(f, "%f", &t) == 1) {
        ScoreInserir(recorde, t);
    }
    fclose(f);
}

void ScoreSalvar(const Score *recorde, const char *arquivo)
{
    FILE *f = fopen(arquivo, "w");       //  reescreve o arquivo inteiro
    if (f == NULL) return;

    for (NoScore *n = recorde->inicio; n != NULL; n = n->prox) {
        fprintf(f, "%.3f\n", n->tempo);
    }
    fclose(f);
}

void ScoreFormatar(float tempo, char *buf, int tamanho)
{
    int totalMs = (int)(tempo * 1000.0f);
    int min = totalMs / 60000;
    int sec = (totalMs / 1000) % 60;
    int ms  = totalMs % 1000;
    snprintf(buf, tamanho, "%02d:%02d:%03d", min, sec, ms);
}

void ScoreLiberar(Score *recorde)
{
    NoScore *n = recorde->inicio;
    while (n != NULL) {
        NoScore *prox = n->prox;         // guarda o próximo
        free(n);
        n = prox;
    }
    recorde->inicio = NULL;
    recorde->total = 0;
}