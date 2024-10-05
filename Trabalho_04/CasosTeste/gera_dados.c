#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO_NOME 15

// Função para gerar um nome aleatório
void gerarNomeAleatorio(char* nome) {
    int tamanho = rand() % 5 + 5; // Nome com 5 a 10 caracteres
    for (int i = 0; i < tamanho; i++) {
        nome[i] = 'A' + rand() % 26; // Letras maiúsculas aleatórias
    }
    nome[tamanho] = '\0';
}

// Função para verificar se o nome já existe
// int nomeExiste(char** lista, int tamanho, char* nome) {
//     for (int i = 0; i < tamanho; i++) {
//         if (strcmp(lista[i], nome) == 0) {
//             return 1;
//         }
//     }
//     return 0;
// }

// Função para gerar uma lista de nomes únicos
void gerarListaNomes(char** lista, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        gerarNomeAleatorio(lista[i]);
        // do {
        //     gerarNomeAleatorio(lista[i]);
        // } while (nomeExiste(lista, i, lista[i]));
    }
}

// Função para salvar a lista de nomes em um arquivo
void salvarNomesEmArquivo(char** lista, int quantidade, const char* nomeArquivo) {
    FILE* file = fopen(nomeArquivo, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }
    for (int i = 0; i < quantidade; i++) {
        fprintf(file, "%s\n", lista[i]);
    }
    fclose(file);
}

int main() {
    srand(time(NULL));
    int quantidade;
    printf("Digite a quantidade de nomes e sobrenomes a serem gerados: ");
    scanf("%d", &quantidade);

    // Aloca memória para a lista de nomes e sobrenomes
    char** nomes = malloc(quantidade * sizeof(char*));
    char** sobrenomes = malloc(quantidade * sizeof(char*));
    for (int i = 0; i < quantidade; i++) {
        nomes[i] = malloc(TAMANHO_NOME * sizeof(char));
        sobrenomes[i] = malloc(TAMANHO_NOME * sizeof(char));
    }

    // Gera listas de nomes e sobrenomes únicos
    gerarListaNomes(nomes, quantidade);
    gerarListaNomes(sobrenomes, quantidade);

    // Salva as listas em arquivos separados
    salvarNomesEmArquivo(nomes, quantidade, "nomes.txt");
    salvarNomesEmArquivo(sobrenomes, quantidade, "sobrenomes.txt");

    // Libera a memória alocada
    for (int i = 0; i < quantidade; i++) {
        free(nomes[i]);
        free(sobrenomes[i]);
    }
    free(nomes);
    free(sobrenomes);

    printf("Arquivos de nomes e sobrenomes gerados com sucesso!\n");
    return 0;
}
