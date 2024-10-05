#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "nomes.h"

int main(int argc, char *argv[]){
    srand(time(NULL));

    Nome *nomes = malloc(sizeof(Nome)*QUANTIDADE_NOMES);
    Nome *sobrenomes = malloc(sizeof(Nome)*QUANTIDADE_NOMES);

    lerNomes("nomes.txt", nomes, QUANTIDADE_NOMES);
    printf("Nomes lidos corretamente\n");
    lerNomes("sobrenomes.txt", sobrenomes, QUANTIDADE_NOMES);
    printf("Sobrenomes lidos corretamente\n");

    if(argc != 2){
        printf("Uso: %s <quantidade_de_nomes>\n", argv[0]);
        return 1;
    }

    int quantidadeNomesCompletos = atoi(argv[1]);

    NomeCompleto *nomesCompletos = malloc(sizeof(NomeCompleto)*quantidadeNomesCompletos);

    gerarNomesCompletos(nomesCompletos, nomes, sobrenomes, quantidadeNomesCompletos);
    printf("Nomes completos gerados\n");

    salvarNomesEmArquivo(nomesCompletos, quantidadeNomesCompletos);
    printf("Nomes completos salvos\n");

    free(nomes);
    free(sobrenomes);
    free(nomesCompletos);
}