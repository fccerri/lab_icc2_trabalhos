#ifndef NOMES_H
#define NOMES_H

#define TAMANHO_NOME 15
#define QUANTIDADE_NOMES 1000000

typedef char Nome[TAMANHO_NOME];

typedef struct {
    Nome primeiroNome;
    Nome nomeDoMeio;
    Nome sobrenome;
} NomeCompleto;

int lerNomes(char *nomeArquivo, Nome nomes[], int max_nomes);

char* obterNomeAleatorio(Nome nomes[], int quantidadeNomes);

void gerarNomesCompletos(NomeCompleto nomesCompletos[], 
    Nome nomes[], Nome sobrenomes[], int quantidade);

void salvarNomesEmArquivo(NomeCompleto nomesCompletos[], int quantidade);

#endif