#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "operacoes.h"


// double stop_timer(clock_t start_time){
//     clock_t end_time = clock();
//     return ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
// }
int main() {
    // clock_t time;
    // double tempo;

    char *result;
    char *str1 = malloc(10000 * sizeof(char));
    char* str2 = malloc(10000 * sizeof(char));

    scanf(" %s", str1);
    scanf(" %s", str2);

    // time = clock();

    result = karatsuba(str1, str2);    

    printf("%s\n", result);

    // tempo = stop_timer(time);
    // printf("Resultado Karatsuba: %s, Tempo de Execução: %lf\n", result, tempo);
    // time = clock();
    // free(result);
    // result = multiplicacao(str1, str2);
    // tempo = stop_timer(time);
    // printf("Resultado Convencional: %s, Tempo de Execução: %lf\n", result, tempo);

    // Libera a memória alocada
    free(str1);
    free(str2);
    free(result);

    return 0;
}
