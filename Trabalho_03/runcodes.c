#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

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

//#define MAX 121

// Serve para ter uma noção do porquê do shell_sort funcionar daquela forma
/*void insertion_sort(pair *elenco, int tamanho_elenco){
    //No insertion sort, o primeiro elemento considera-se ordenado
    // os próximos elementos são inseridos no array de acordo com a posição dele: menor ou menor que ele
    pair elemento_aux;
    int indice_maior = 0, j, i;
    for(i = 1; i<tamanho_elenco; i++){
        elemento_aux = elenco[i]; //guarda elemento atual
        j  = i-1; // define j como a posição IMEDIATAMENTE atrás de i
        // move os elementos pra direita
        while( j>=0 && ((elemento_aux.nota<elenco[j].nota) || ((elemento_aux.nota == elenco[j].nota) && (strcmp(elemento_aux.nome, elenco[i].nome)>0)))){
            elenco[j+1] = elenco[j]; //move o elmento pra direita
            j--;
        }
        // Insere o elemento na posição certa        
        elenco[j+1] = elemento_aux;
        }
}*/ 

void shell_sort(pair *elenco, int tamanho_elenco){
    // No sheel sort, o algoritmo divide em sublistas(gaps) e aplica o insertion sort, até que o gap seja 1 e aplique-se o insertion sort no vetor inteiro
    int gap = tamanho_elenco / 2; 
    int j;
    pair elemento_aux;
    while(gap>0){
        // começa o loop a partir do gap e vai até o final do array
        for(int i = gap; i <tamanho_elenco; i++){
            elemento_aux = elenco[i]; // variável auxiliar para pegar o elemento atual
            j = i;
            // faz a verificação se o elemento_aux é maior que o elemento comparado pelo gap. Se for maior, atribui ao elemento j o elemento da distância de gap.
            while((j>=gap) && ((elemento_aux.nota > elenco[j-gap].nota) || ((elemento_aux.nota == elenco[j-gap].nota) && (strcmp(elemento_aux.nome, elenco[j-gap].nome)<0)))){
                elenco[j] = elenco[j-gap];
                j -= gap;
              }
            //Atribui-se o elemento original a sua posição correta (para que ele não seja perdido)
        elenco[j]= elemento_aux;
    }
    //repete-se esse processo
    gap /= 2;
    }
} 

void selection_sort(pair *elenco, int n){
    PILHA *pilha = pilha_criar(n); 
    pair min = {"\0", INT_MAX};
    int posicao , i, j;
    for (j =0; j<n; j++) {
        for (i =0; i<n; i++) {
            if ((min.nota > elenco[i].nota) || (min.nota == elenco[i].nota && strcmp(min.nome, elenco[i].nome) < 0)) { //encontra a menor nota
                min = elenco[i];
                posicao = i;
            }
        }
        elenco[posicao].nota = INT_MAX; //"remove" menor nota do vetor evitando notas iguais nos subsequentes minimos
        pilha_empilhar(pilha, min);
        
        strcpy(min.nome, "\0");
        min.nota = INT_MAX;
    }
    i = 0;
    while(!pilha_vazia(pilha)){
        elenco[i] = pilha_desempilhar(pilha);
        //printf("\n%s %d", elenco[i].nome, elenco[i].nota);
        //pilha_print(pilha);
        i++;
    }
    pilha_print(pilha);
    pilha_apagar(&pilha);  
}


int main() {
    int n; scanf("%d", &n);
    pair *elenco = malloc(n*sizeof(pair));
    //PILHA *pilha = pilha_criar(n); 

    for (int i = 0; i<n; i++) { //recebe e guarda os valores
        scanf(" %s%d", elenco[i].nome, &(elenco[i].nota));
    }
    //selection sort(elenco, n);
    shell_sort(elenco, n);
    for(int i = 0; i<n; i++){
        printf("%s %d\n", elenco[i].nome, elenco[i].nota);
    }
    free(elenco);
    return 0;
}