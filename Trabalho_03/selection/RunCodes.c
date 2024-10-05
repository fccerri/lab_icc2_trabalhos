#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ERRO -1

typedef struct pair_ {
    char nome[51];
    int nota;
}pair;

typedef struct pilha_ PILHA;
PILHA* pilha_criar(int tam);
void pilha_apagar(PILHA** pilha);
bool pilha_vazia(PILHA* pilha);
bool pilha_cheia(PILHA* pilha);
int pilha_tamanho(PILHA* pilha);
pair pilha_topo(PILHA* pilha);
bool pilha_empilhar(PILHA* pilha, pair dado);
pair pilha_desempilhar(PILHA* pilha);
void pilha_print(PILHA* p);

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

#define MAX 121

int main () {
    int n; scanf("%d", &n);
    pair *elenco = malloc(n*sizeof(pair));
    PILHA *pilha = pilha_criar(n); 

    for (int i = 0; i<n; i++) { //recebe e guarda os valores
        scanf(" %s%d", elenco[i].nome, &(elenco[i].nota));
    }

    pair min = {"\0", MAX};
    int posicao;
    for (int j =0; j<n; j++) {
        for (int i =0; i<n; i++) {
            if (min.nota > elenco[i].nota) { //encontra a menor nota
                min = elenco[i];
                posicao = i;
            }
            else if (min.nota == elenco[i].nota && strcmp(min.nome, elenco[i].nome) < 0) { //desempate caso notas iguais
                min = elenco[i];
                posicao = i;
            }
        }

        elenco[posicao].nota = MAX+posicao+1; //"remove" menor nota do vetor evitando notas iguais nos subsequentes minimos
        pilha_empilhar(pilha, min);
        
        strcpy(min.nome, "\0");
        min.nota = MAX;
    }

    pilha_print(pilha);
    pilha_apagar(&pilha);    
    return 0;
}