#include "pilha_encadeada.h"
#include <stdio.h>
#include <stdlib.h>

struct pilha_ {
    int tam, topo;
    pair *dados;
};

PILHA* pilha_criar(int tam) {
    PILHA *p = malloc(sizeof(PILHA));
    if (p == NULL) exit(ERRO);
    p->dados = malloc(tam*sizeof(pair));
    if (p->dados == NULL) exit(ERRO);

    p->tam = tam;
    p->topo = 0;
    return p;
}

void pilha_apagar(PILHA** pilha) {
    if (pilha == NULL || *pilha == NULL) exit(ERRO);
    free((*pilha)->dados);
    (*pilha)->dados = NULL;
    free(*pilha);
    *pilha = NULL; 
}

bool pilha_vazia(PILHA* pilha) {
    if (pilha != NULL && pilha->topo == 0) return true;
    return false;
}

bool pilha_cheia(PILHA* pilha) {
    if (pilha != NULL && pilha->topo == pilha->tam) return true;
    return false;
}

int pilha_tamanho(PILHA* pilha) {
    if (pilha != NULL) return pilha->topo;
    exit(ERRO);
}

pair pilha_topo(PILHA* pilha) {
    if (pilha != NULL && !pilha_vazia(pilha)) 
        return pilha->dados[(pilha->topo)-1];
    exit(ERRO);
}

bool pilha_empilhar(PILHA* pilha, pair dado) {
    if (pilha == NULL || pilha_cheia(pilha)) return false;
    pilha->dados[pilha->topo] = dado;
    pilha->topo++;
    return true;
}
pair pilha_desempilhar(PILHA* pilha) {
    if (pilha == NULL || pilha_vazia(pilha)) exit(ERRO);
    pilha->topo--;
    return pilha->dados[(pilha->topo)];
}
void pilha_print(PILHA* pilha) {
    for (int i = pilha_tamanho(pilha)-1; i>=0; i--) {
        printf("%s %d\n", pilha->dados[i].nome, pilha->dados[i].nota);
    }
}