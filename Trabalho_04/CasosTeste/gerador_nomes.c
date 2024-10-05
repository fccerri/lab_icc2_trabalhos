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
    lerNomes("sobrenomes.txt", sobrenomes, QUANTIDADE_NOMES);

    if(argc != 2){
        printf("Uso: %s <quantidade_de_nomes>\n", argv[0]);
        return 1;
    }

    int quantidadeNomesCompletos = atoi(argv[1]);

    NomeCompleto *nomesCompletos = malloc(sizeof(NomeCompleto)*quantidadeNomesCompletos);

    gerarNomesCompletos(nomesCompletos, nomes, sobrenomes, quantidadeNomesCompletos);

    salvarNomesEmArquivo(nomesCompletos, quantidadeNomesCompletos);

    free(nomes);
    free(sobrenomes);
    free(nomesCompletos);
}