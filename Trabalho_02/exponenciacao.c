#include <stdio.h>
#include <time.h>
#define mod 10000;

// double stop_timer(clock_t start_time){
//     clock_t end_time = clock();
//     return ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
// }

long int iterativo(int n, int k) {
    long int result = 1;
    for (int i =0; i<k; i++) {
        result *= n;
        result %= mod;
    }
    return result;
}

long int divConq(int n, int k) {
    long int result = 1, temp;

    if (k == 1) { //caso base
        return n;
    }
    //faz correção caso k seja impar
    else if (k%2) {
        result *= n;
    }
    //temp evita chamar a funcao desnecessariamente
    temp = divConq(n, k/2); 
    temp *= temp%mod; 
    result *= temp;
    
    return result%mod;
}

int main () {
    // clock_t time;
    // double tempo;

    int n, k; long int result;
    scanf ("%d%d", &n, &k);

    // time = clock();
    // result = iterativo(n, k);
    // tempo = stop_timer(time);

    // printf("Resultado iterativo: %ld, Tempo de Execução: %lf\n", result, tempo);

    // time = clock();
    // result = divConq(n,k);
    // tempo = stop_timer(time);

    // printf("Resultado Divisão e Conquista: %ld, Tempo de Execução: %lf\n", result, tempo);


    printf("%ld\n", divConq(n, k));
    return 0;
}