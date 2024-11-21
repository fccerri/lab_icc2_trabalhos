#include<stdio.h>
#include<stdlib.h>
#include<time.h>

double endTime(clock_t start){
    clock_t finish = clock();
    return ((double)(finish - start))/CLOCKS_PER_SEC;
}

void swap (int *a, int *b){
    int aux = (*a);
    (*a) =(*b);
    (*b) = aux;
}

int achar_pivo(int *vector, int ini, int fim) {
    int meio = ini + (fim - ini) / 2;

    int a = vector[ini];
    int b = vector[meio];
    int c = vector[fim];

    // Verifica a mediana entre *a, *b e *c
    if ((a > b) != (a > c))
        return a;
    else if ((b > a) != (b > c))
        return b;
    else
        return c;
}
/// COLOCAR PIVÔ COMO MEDIANA DE 3
void quick_sort(int *v, int ini, int fim){
    // Define-se pivo como elemento do meio, i como primeiro elemento e j como último elemento
    int i =ini, j = fim;
    int pivo = achar_pivo(v, ini, fim);
    //int pivo = v[(ini+fim)/2];
   // Primeira etapa, percorre enquanto i<j
    do{
        // percorre i e j até que um elemento da esquerda pertença à direita
        while(v[i]<pivo) i++;
        while(v[j]>pivo) j--;
        // Não é estavel (realiza troca de elementos iguais)
        if(i<=j){
            swap(&v[i], &v[j]);
            i++;
            j--;
        }
    } while(i<j);
    // Continua iterações
    if(j>ini){
        quick_sort(v, ini, j);
    }
    if(i<fim){
        quick_sort(v, i, fim);
    }
}
int msc_ordenacao(int *v, int tam_vetor){
    // Se o tamanho do vetor é 1, a msc é 1
    if(tam_vetor == 1){
        return 1;
    }
    int msc = 1;
    int seq_atual = 1;
    for(int i = 1; i<tam_vetor; i++){
        if(v[i] == v[i-1]+1){
            seq_atual++;
        }
        else{
            if(seq_atual>msc){
                msc = seq_atual;
            }
            seq_atual = 1;
        }
    }
    if(seq_atual>msc){
            msc = seq_atual;
    }

    return msc;

}
int main(){
    int repeticao;
    scanf("%d", &repeticao);
    int * sequencia = (int *) malloc (repeticao * sizeof(int));

    double tempo; clock_t start = clock();
    for(int i = 0; i<repeticao; i++){
        scanf(" %d", &sequencia[i]);
    }
    quick_sort(sequencia, 0, repeticao-1);
    printf("%d", msc_ordenacao(sequencia, repeticao));
    tempo = endTime(start); 
    printf("Tempo de execução: %lf\n", tempo);

    free(sequencia);
    return 0;
}