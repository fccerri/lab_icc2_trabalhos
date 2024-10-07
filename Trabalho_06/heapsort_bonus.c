#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct prato_ {
    int prioridade, preparo;
    char nome[51];
    struct prato_ *esq, *dir;
} prato ;
    
void heapSort(prato *cardapio, int tam);

void buildHeap(prato *cardapio, int tam);

void heapify(prato *atual);

void buildTree(prato *cardapio, int tam);

int compare(prato a, prato b); //retorna 1 se a > b
                               //retorna 0 se a < b

                               
void swap(prato *pai, prato *filho);

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

void heapify(prato *atual) {
    prato *maior = atual;
    int trocas = 0;

    if (atual->esq != NULL && compare(*(atual->esq), *atual)) { //acha maior filho
        maior = atual->esq;
        trocas++;
    }   
    if (atual->dir != NULL && compare(*(atual->dir), *maior) ) {
        maior = atual->dir;
        trocas++;
    } 
    if (trocas == 0) return; //caso o pai seja maior que os filhos
    
    swap(maior, atual); //troca o pai com o maior filho
    heapify(maior); //chama o arranjo para o filho que estava desordenado

}

void buildHeap(prato *cardapio, int tam) {
    for (int i = ((tam)/2 - 1) ; i>=0; i--) { //rearrajo a partir do primeiro que nao e folha
        heapify(&cardapio[i]); 
    }
}

void heapSort(prato *cardapio, int tam) {
    buildTree(cardapio, tam);
    buildHeap(cardapio, tam);
    
    for (int i = tam - 1; i > 0; i--) {
        // for (int i =0; i<tam; i++) {
            // printf("%d ", cardapio[i].prioridade);
        // }
        // printf("\n");
        // swap(&cardapio[0], &cardapio[i]); //maior vai para o final do array
        // for (int i =0; i<tam; i++) {
            // printf("%d ", cardapio[i].prioridade);
        // }
        // printf(" apos troca\n");

        //isola o maior elemento da arvore
        if (i%2) { //filho é da forma 2k + 1 (impar), portanto é o filho da esquerda
            cardapio[(i-1)/2].esq = NULL;
            // printf("filho da esq de %d\n", i/2);
        }
        else{
            cardapio[(i-1)/2].dir = NULL;
            // printf("filho da dir de %d\n", i/2);
        }

        cardapio[i].dir = NULL;
        cardapio[i].esq = NULL;

        



        // for (int i =0; i<tam/2; i++) {
            // printf("%d: ", i);
            // if (cardapio[i].esq == NULL) printf("filho esq: NULL\n");
            // else printf("Filho esq: %d\n", cardapio[i].esq->prioridade);
            // if (cardapio[i].dir == NULL) printf("    filho dir: NULL\n");
            // else printf("    Filho dir: %d\n", cardapio[i].dir->prioridade);
 
        // }

        heapify(&cardapio[0]);//estabelece max heap com raiz em idx 0
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

void buildTree(prato *cardapio, int tam) {
    int esq, dir;
    for (int i =0; i<(tam/2); i++) { //constroi a arvore
        esq = 2*i +1;
        dir = 2*i +2;

        if (esq < tam)
            cardapio[i].esq = &cardapio[esq];
        if (dir < tam)
            cardapio[i].dir = &cardapio[dir];
    }

    for (int i = (tam/2); i<tam; i++) { //folhas apontam para nulo 
        cardapio[i].esq = NULL;
        cardapio[i].dir = NULL;
    }
}

void swap(prato *pai, prato *filho) { //o problema nao ta no swap, ambas as logicas funcionam       
    // int temp = pai->preparo;
    // pai->preparo = filho->preparo;
    // filho->preparo = temp;

    // temp = pai->prioridade;
    // pai->prioridade = filho->prioridade;
    // filho->prioridade = temp;

    // char tempString[51];
    // strcpy(tempString, pai->nome);
    // strcpy(pai->nome, filho->nome);
    // strcpy(filho->nome, tempString);


    prato temp = *pai; //troca do pai com o filho
    *pai = *filho;
    *filho = temp;

    prato *filho_esq = pai->esq, //troca dos filhos
          *filho_dir = pai->dir;

    pai->esq = filho->esq;
    pai->dir = filho->dir;

    filho->esq = filho_esq;
    filho->dir = filho_dir;
}