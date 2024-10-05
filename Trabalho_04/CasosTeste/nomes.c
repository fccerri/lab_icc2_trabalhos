#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nomes.h"

int lerNomes(char *nomeArquivo, Nome nomes[], int max_nomes){
    FILE *arquivo = fopen(nomeArquivo, "r");
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo %s\n", nomeArquivo);
        return 0;
    }

    int i = 0;
    while (fgets(nomes[i], TAMANHO_NOME, arquivo) != NULL && i < max_nomes) {
        nomes[i][strcspn(nomes[i], "\n")] = '\0'; // Remove o '\n'
        i++;
    }

    fclose(arquivo);
    return i;
}

char* obterNomeAleatorio(Nome nomes[], int quantidadeNomes){
    return nomes[rand() % quantidadeNomes];
}

void gerarNomesCompletos(NomeCompleto nomesCompletos[], 
    Nome nomes[], Nome sobrenomes[], int quantidade){
    
    for(int i = 0; i < quantidade; i++){
        strcpy(nomesCompletos[i].primeiroNome, obterNomeAleatorio(nomes, quantidade));
        strcpy(nomesCompletos[i].nomeDoMeio, obterNomeAleatorio(sobrenomes, quantidade));
        strcpy(nomesCompletos[i].sobrenome, obterNomeAleatorio(sobrenomes, quantidade));
    }

}

void gerarNomeArquivo(char *nomeArquivo, int quantidade){
    sprintf(nomeArquivo, "nomes_completos_%d.txt", quantidade);
}

void salvarNomesEmArquivo(NomeCompleto nomesCompletos[], int quantidade){
    char nomeArquivoSaida[30];
    gerarNomeArquivo(nomeArquivoSaida, quantidade);

    FILE* file = fopen(nomeArquivoSaida, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        fprintf(file, "%s %s %s\n", 
            nomesCompletos[i].primeiroNome, 
            nomesCompletos[i].nomeDoMeio, 
            nomesCompletos[i].sobrenome);
    }

    fclose(file);
}