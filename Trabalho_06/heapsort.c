#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct prato_ {
    int prioridade, preparo;
    char nome[51];
} prato ;
    
void heapSort(prato *cardapio, int tam);

void buildHeap(prato *cardapio, int tam);

void heapify(prato *cardapio, int id, int tam);

int compare(prato a, prato b); //retorna 1 se a > b
                               //retorna 0 se a < b

                               
void swap(prato *a, prato *b) {
    prato temp = *a;
    *a = *b;
    *b = temp;
}

double endTime(clock_t start){
    clock_t finish = clock();
    return ((double)(finish - start))/CLOCKS_PER_SEC;
}

int main () {
    int n; scanf("%d", &n);
    prato *cardapio = malloc(sizeof(prato)*n);
    for (int i =0; i<n; i++) {
        scanf("%d%d %s", &(cardapio[i]).prioridade, &(cardapio[i]).preparo, cardapio[i].nome);
    }

    double tempo; clock_t start = clock();
    heapSort(cardapio, n);
    tempo = endTime(start);

    for (int i = 0; i<n; i++) printf("%s\n", cardapio[i].nome);
    // printf("\ntempo de execução: %lf", tempo);

    free(cardapio);
    return 0;
}

void heapify(prato *cardapio, int id, int tam) {
    int esq = 2 * id + 1, //filho da esquerda
    dir = 2 * id + 2,  //fihlo da direita
    maior = id; 

    if (esq < tam && compare(cardapio[esq], cardapio[id])) { //acha maior filho
        maior = esq;
    }   
    if (dir < tam && compare(cardapio[dir], cardapio[maior]) ) {
        maior = dir;
    } 
    if (maior == id) return; //caso o pai seja maior que os filhos
    
    swap(&cardapio[maior], &cardapio[id]); //troca o pai com o maior filho
    heapify(cardapio,maior, tam); //chama o arranjo para o filho que estava desordenado

}

void buildHeap(prato *cardapio, int tam) {
    for (int i = ((tam)/2 - 1) ; i>=0; i--) { //rearrajo a partir do primeiro que nao e folha
        heapify(cardapio, i, tam); 
    }
}

void heapSort(prato *cardapio, int tam) {
    buildHeap(cardapio, tam);
    
    for (int i = tam - 1; i > 0; i--) {
        swap(&cardapio[0], &cardapio[i]); //maior vai para o final do array
        heapify(cardapio, 0, i);//estabelece max heap com raiz em idx 0
    }
}

int compare(prato a, prato b) {        //1 se a > b
    if (a.prioridade == b.prioridade) {//0 se a < b
        if (a.preparo < b.preparo)
            return 1;
        else 
            return 0;
    }

    if (a.prioridade > b.prioridade)
        return 1;
    else
        return 0;
}