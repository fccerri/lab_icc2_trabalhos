#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>
#include<time.h>

/// Estrutura prato
typedef struct {
    int prioridade; //decrescente
    int tempo;         //crescente
    char nome[50];
}prato;

// Função que realiza a troca de dois elementos
void swap(prato *a, prato *b){
    prato aux;
    aux = (*a);
    (*a) = (*b);
    (*b) = aux;
}


void bubble_sort_aprimorado(prato *vetor, int tamanho_vetor){
    int i, j;
    bool troca = true;
    // Se não for feita nenhuma troca, retorna
    for(i = 0; i<tamanho_vetor && troca; i++){
        troca = false;
        // Para em tamanho_vetor -i - 1. O -i refere-se aos elementos já ordenados
        for(j = 0; j<tamanho_vetor-i-1; j++){
            // realiza a troca conforme as especificações do projeto
            if(vetor[j].prioridade>vetor[j+1].prioridade || (vetor[j].prioridade==vetor[j+1].prioridade && vetor[j].tempo< vetor[j+1].tempo)){
                //a função "swap" troca os dois elementos
                swap(&vetor[j], &vetor[j+1]);
                troca  = true;
            }
        }
    }
}

void quick_sort(prato *vector, int ini, int fim){
    // Define-se pivo como elemento aleatório (abordagem que dificulta cair no pior caso do Quick Sort)
    int i =ini, j = fim;
    srand(time(NULL));
    int index_pivo = ini +rand()%(fim-ini+1);
    //armazena-se a prioridade e o tempo do pivô
    int pivo_prioridade = vector[index_pivo].prioridade;
    int pivo_tempo = vector[index_pivo].tempo;
   // Primeira etapa, percorre enquanto i<j
    do{
        // percorre i e j até que um elemento da esquerda pertença à direita
        while(vector[i].prioridade<pivo_prioridade || (vector[i].prioridade == pivo_prioridade && vector[i].tempo> pivo_tempo)) i++;
        while(vector[j].prioridade>pivo_prioridade || (vector[j].prioridade == pivo_prioridade && vector[j].tempo< pivo_tempo)) j--;
        // Não é estavel (realiza troca de elementos iguais)
        if(i<=j){
            swap(&vector[i], &vector[j]);
            i++;
            j--;
        }
    } while(i<j);
    // Continua iterações
    if(j>ini){
        quick_sort(vector, ini, j);
    }
    if(i<fim){
        quick_sort(vector, i, fim);
    }
}
double stop_timer(clock_t start_time){
    clock_t end_time = clock();
    return ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
}

int main(void){
    clock_t time, time2;
    double tempo;
    int num_pratos;
    scanf("%d", &num_pratos);
    prato * pratos = (prato *) malloc(num_pratos * sizeof(prato));
    for(int i = 0; i<num_pratos; i++){
        scanf(" %d %d", &(pratos[i].prioridade), &(pratos[i].tempo));
        getchar();
        // Lê a string (nome do prato)
        fgets(pratos[i].nome, sizeof(pratos[i].nome), stdin);
    }

    time = clock();
    quick_sort(pratos, 0, num_pratos-1);
    tempo = stop_timer(time);
    printf("\n Tempo de Execução Quick Sort: %lf", tempo); 

   /*  time = clock();
    bubble_sort_aprimorado(pratos, num_pratos);
    tempo = stop_timer(time);
    printf("\n Tempo de Execução Bubble Sort: %lf", tempo); */

    
    /*for(int i = 0; i<num_pratos; i++){
        printf("%s", pratos[i].nome);
    } */

    free(pratos);
    pratos = NULL;
}