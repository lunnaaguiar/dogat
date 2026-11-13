#include "score.h"
#include <stdio.h>
#include <stdlib.h>

void ScoreInit(Score *s)
{
    s->inicio = NULL;
    s->total = 0;
}

int ScoreInserir(Score *s, float tempo)
{
    NoScore *novo = (NoScore *)malloc(sizeof(NoScore));
    if (novo == NULL) return 0;          // sem memória
    novo->tempo = tempo;

    int posicao = 1;

    if (s->inicio == NULL || tempo < s->inicio->tempo) {
        // lista vazia ou o novo é melhor (vira o primeiro)
        novo->prox = s->inicio;
        s->inicio = novo;
    } else {
        // anda até o último nó que ainda é menor ou igual ao novo
        NoScore *atual = s->inicio;
        posicao++;
        while (atual->prox != NULL && atual->prox->tempo <= tempo) {
            atual = atual->prox;
            posicao++;
        }
        novo->prox = atual->prox;        // 1° liga o novo no resto da lista
        atual->prox = novo;              // 2° liga o anterior no novo
    }

    s->total++;
    return posicao;
}

void ScoreCarregar(Score *s, const char *arquivo)
{
    FILE *f = fopen(arquivo, "r");
    if (f == NULL) return;               // ainda não existe

    float t;
    while (fscanf(f, "%f", &t) == 1) {
        ScoreInserir(s, t);
    }
    fclose(f);
}

void ScoreSalvar(const Score *s, const char *arquivo)
{
    FILE *f = fopen(arquivo, "w");       //  reescreve o arquivo inteiro
    if (f == NULL) return;

    for (NoScore *n = s->inicio; n != NULL; n = n->prox) {
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

void ScoreLiberar(Score *s)
{
    NoScore *n = s->inicio;
    while (n != NULL) {
        NoScore *prox = n->prox;         // guarda o próximo antes do free
        free(n);
        n = prox;
    }
    s->inicio = NULL;
    s->total = 0;
}