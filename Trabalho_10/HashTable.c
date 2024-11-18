#include <stdio.h>
#include <stdlib.h>
#define max(a, b) ((a) > (b) ? (a) : (b))

//tabela hash aberta com lista encadeada
typedef struct no_ {
    struct no *proximo;
    int valor;
} NO;

typedef struct tabelahash_ {
    NO *tabela;
    int modulo;
} estruturaHash;

void insere_hashing(int valor, estruturaHash tabelaHash);
int busca_hashing(int valor, estruturaHash tabelaHash); //retorna o valor caso exista
int subsequencia_crescente(estruturaHash tabelaHash, int *vet, int n);
void libera_hashing(estruturaHash tabelaHash);

int main () { 
    int n; scanf("%d", &n); //numero de nomes
    int B = n/0.75; //qtd de itens no vetor de hashing (modulo)

    estruturaHash tabelaHash; 
    tabelaHash.modulo = B;
    tabelaHash.tabela = calloc(B, sizeof(NO)); 
    int *vet = malloc(sizeof(int)*n);

    int valor; 
    for (int i =0; i<n; i++) {
        scanf("%d", &valor);
        insere_hashing(valor, tabelaHash);
        vet[i] = valor;
    }

    int maxSub = subsequencia_crescente(tabelaHash, vet, n);
    printf("%d\n", maxSub);

    libera_hashing(tabelaHash);
    return 0;
}

int subsequencia_crescente(estruturaHash tabelaHash, int *vet, int n){
    int aux, maxSub = 0, tempMaxSub = 1;
    for (int i = 0; i<n; i++) {
        aux = vet[i];
        if (busca_hashing(aux-1, tabelaHash) == 0) { //se for o primeiro elemento da subsequencia
        while (busca_hashing(++aux, tabelaHash) != 0) {
            tempMaxSub++;
        }
        maxSub = max(maxSub, tempMaxSub);
        tempMaxSub = 1;
        }
    }

    return  maxSub;
}

void insere_hashing(int valor, estruturaHash tabelaHash) {
    int indice = (9*valor + 29) % tabelaHash.modulo; //funcao de hashing
    NO *aux = &(tabelaHash.tabela[indice]); int count = 0;

    if (aux->valor == 0) //verifica se ja existe um valor no nó
        count++; 
    while (aux->proximo != NULL) { //percorre a lista encadeada caso exista colisao
        aux = aux->proximo;
        count++;
    }

    if (count != 0) {
        aux->proximo = malloc(sizeof(NO));
        aux = aux->proximo;
    }

    aux->valor = valor;
}

int busca_hashing(int valor, estruturaHash tabelaHash) {
    int indice = (9*valor + 29) % tabelaHash.modulo; //funcao de hashing
    NO *aux = &(tabelaHash.tabela[indice]); 

    while (aux->proximo != NULL && aux->valor != valor) { //percorre a lista encadeada pra achar o valor caso exista
        aux = aux->proximo;
    }

    if (aux->valor == valor)
        return valor;
    else
        return 0;

}

void libera_hashing(estruturaHash tabelaHash) {
    //tem q percorre td, mo preguica
}