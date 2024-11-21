#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define LOADFACTOR 0.75

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
int proximo_primo(int n);

double endTime(clock_t start){
    clock_t finish = clock();
    return ((double)(finish - start))/CLOCKS_PER_SEC;
}

int main () { 
    int n; scanf("%d", &n); //numero de nomes
    //estabelece B como o proximo primo maior que n/LOADFACTOR para evitar colisoes
    int B = proximo_primo(n/LOADFACTOR); //qtd de itens no vetor de hashing (modulo)

    estruturaHash tabelaHash; 
    tabelaHash.modulo = B;
    tabelaHash.tabela = calloc(B, sizeof(NO)); 
    int *vet = malloc(sizeof(int)*n);

    double tempo; clock_t start = clock();
    int valor; 
    for (int i =0; i<n; i++) {
        scanf("%d", &valor); //recebe valores no vetor
        insere_hashing(valor, tabelaHash); //insere valores na tabela hash
        vet[i] = valor;
    }

    int maxSub = subsequencia_crescente(tabelaHash, vet, n);
    printf("%d\n", maxSub);
    tempo = endTime(start); 
    printf("Tempo de execução: %lf\n", tempo);


    //libera memoria
    libera_hashing(tabelaHash);
    free(vet);
    vet = NULL;
    return 0;
}

int subsequencia_crescente(estruturaHash tabelaHash, int *vet, int n){
    int aux, maxSub = 0, tempMaxSub = 1;
    for (int i = 0; i<n; i++) {
        aux = vet[i];
        if (busca_hashing(aux-1, tabelaHash) == 0) { //se for o primeiro elemento da subsequencia
        while (busca_hashing(++aux, tabelaHash) != 0) { //caso ache um elemento subsequente
            tempMaxSub++; //a sequencia atual é incrementada
        }
        maxSub = max(maxSub, tempMaxSub); //determina se a sequencia atual é a melhor global 
        tempMaxSub = 1;
        }
    }

    return  maxSub;
}

void insere_hashing(int valor, estruturaHash tabelaHash) {
    int B = tabelaHash.modulo;
    int indice = valor % B; //funcao hash

    NO *aux = &(tabelaHash.tabela[indice]); int count = 0;

    if (aux->valor != 0) //verifica se ja existe um valor no nó
        count++; 
    while (aux->proximo != NULL) { //percorre a lista encadeada caso exista colisao
        aux = (NO*)aux->proximo;
        count++;
    }

    if (count != 0) { //declara um no para o proximo elemento caso tenha colisao
        aux->proximo = malloc(sizeof(NO));
        aux = (NO*)aux->proximo;
    }

    aux->valor = valor;
    aux->proximo = NULL;
}

int busca_hashing(int valor, estruturaHash tabelaHash) {
    int indice = valor % tabelaHash.modulo; //funcao de hashing
    NO *aux = &(tabelaHash.tabela[indice]); 

    while (aux->proximo != NULL && aux->valor != valor) { //percorre a lista encadeada pra achar o valor caso exista
        aux = (NO*)aux->proximo;
    }

    if (aux->valor == valor)
        return valor;
    else
        return 0; //caso o valor nao tenha sido encontrado

}


void libera_hashing(estruturaHash tabelaHash) {
    for (int i = 0; i<tabelaHash.modulo; i++) { //percorre a tabela hash
            NO *aux = (NO*)tabelaHash.tabela[i].proximo; 
        while (aux != NULL) { 
            //libera a lista encadeda com exceção do primeiro elemento
            NO *next = (NO*)aux->proximo;
            free(aux);
            aux->proximo = NULL;
            aux = next;
        }
    }
    free(tabelaHash.tabela); //libera o restante da tabela hash
    tabelaHash.tabela = NULL;
}

//a funcao usa do fato que todo primo e da forma 6k +- 1
int proximo_primo(int n) {
    int eh_primo = 0;
    n -= (n % 6); //numero sera da forma 6k 
    n += 5; //numero sera da forma 6k - 1

    while (!eh_primo){
        eh_primo = 1; 

        if ( n > 2 && (n%2 == 0) ) //verifica divisibilidade por 2
            eh_primo = 0;

        for (int i = 3; i*i <= n && eh_primo == 1; i+= 2) { //verifica divisibilidade por impares
            if ((n % i) == 0) 
                eh_primo = 0;
        }

        if (!eh_primo) //se nao for primo
            n += (n % 6 == 1) ? 4 : 2; //alterna o numero entre 6k + 1 e 6k -1

    }
    return n;
}
