#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "nomes.h"


// Função para gerar notas aleatórias entre 0 e 10
float gerarNotaAleatoria() {
    return ((float)rand() / RAND_MAX) * 10;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    if (argc != 2) {
        printf("Uso: %s <quantidade_alunos>\n", argv[0]);
        return 1;
    }

    int quantidadeAlunos = atoi(argv[1]);
    
    Nome *nomes = malloc(sizeof(Nome)*QUANTIDADE_NOMES);
    Nome *sobrenomes = malloc(sizeof(Nome)*QUANTIDADE_NOMES);
    
    lerNomes("nomes.txt", nomes, QUANTIDADE_NOMES);
    lerNomes("sobrenomes.txt", sobrenomes, QUANTIDADE_NOMES);

    NomeCompleto *nomesCompletos = malloc(sizeof(NomeCompleto)*quantidadeAlunos);
    gerarNomesCompletos(nomesCompletos, nomes, sobrenomes, quantidadeAlunos);

    // Nome do arquivo de saída
    char nomeArquivo[50];
    snprintf(nomeArquivo, sizeof(nomeArquivo), "alunos_notas_%d.csv", quantidadeAlunos);

    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo para escrita");
        return 1;
    }

    // Escrevendo o cabeçalho do arquivo CSV
    fprintf(arquivo, "aluno,nota1,nota2,nota3\n");

    // Gerando os alunos e suas notas
    for (int i = 0; i < quantidadeAlunos; i++) {
        float nota1 = gerarNotaAleatoria();
        float nota2 = gerarNotaAleatoria();
        float nota3 = gerarNotaAleatoria();

        fprintf(arquivo, "%s %s %s,%.1f,%.1f,%.1f\n", 
                nomesCompletos[i].primeiroNome, 
                nomesCompletos[i].nomeDoMeio, 
                nomesCompletos[i].sobrenome, 
                nota1, nota2, nota3);
    }

    fclose(arquivo);
    printf("Arquivo %s gerado com sucesso!\n", nomeArquivo);

    free(nomes);
    free(sobrenomes);
    free(nomesCompletos);

    return 0;
}
