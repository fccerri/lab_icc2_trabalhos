#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pilha_encadeada.h"

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