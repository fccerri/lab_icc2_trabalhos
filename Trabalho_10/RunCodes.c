#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define LOADFACTOR 0.75

//tabela hash  utilizada: estática aberta com lista encadeada

//estrutura de no utilizada para lista encadeada
typedef struct no_ {
    struct no *proximo;
    int valor;
} NO;

//estrutura de hash que contem a tabela e o modulo utilizado
typedef struct tabelahash_ {
    NO *tabela;
    int modulo;
} estruturaHash;


//funcoes da resolucao por hash
void insere_hashing(int valor, estruturaHash tabelaHash);
int busca_hashing(int valor, estruturaHash tabelaHash); //retorna o valor caso exista
int subsequencia_crescente(estruturaHash tabelaHash, int *vet, int n);
void libera_hashing(estruturaHash tabelaHash);
int proximo_primo(int n);

//funcoes da resolucao por ordenacao
void swap (int *a, int *b);
int achar_pivo(int *vector, int ini, int fim);
void quick_sort(int *v, int ini, int fim); 
int msc_ordenacao(int *v, int tam_vetor);


int main () { 
    int n; scanf("%d", &n); //numero de nomes
    //estabelece B como o proximo primo maior que n/LOADFACTOR para evitar colisoes
    int B = proximo_primo(n/LOADFACTOR); //qtd de itens no vetor de hashing (modulo)

    estruturaHash tabelaHash; 
    tabelaHash.modulo = B;
    tabelaHash.tabela = calloc(B, sizeof(NO)); 
    int *vet = malloc(sizeof(int)*n);

    int valor; 
    for (int i =0; i<n; i++) {
        scanf("%d", &valor); //recebe valores no vetor
        insere_hashing(valor, tabelaHash); //insere valores na tabela hash
        vet[i] = valor;
    }

    int maxSub = subsequencia_crescente(tabelaHash, vet, n);
    printf("%d\n", maxSub);

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

    //percorre a lista encadeada pra achar o valor caso a lista tenha mais de um elemento
    while (aux->proximo != NULL && aux->valor != valor) { 
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


void swap (int *a, int *b){
    int aux = (*a);
    (*a) =(*b);
    (*b) = aux;
}

int achar_pivo(int *vector, int ini, int fim) {
    int meio = ini + (fim - ini) / 2;

    int a = vector[ini];
    int b = vector[meio];
    int c = vector[fim];

    // Verifica a mediana entre *a, *b e *c
    if ((a > b) != (a > c))
        return a;
    else if ((b > a) != (b > c))
        return b;
    else
        return c;
}
/// COLOCAR PIVÔ COMO MEDIANA DE 3
void quick_sort(int *v, int ini, int fim){
    // Define-se pivo como elemento do meio, i como primeiro elemento e j como último elemento
    int i =ini, j = fim;
    int pivo = achar_pivo(v, ini, fim);
    //int pivo = v[(ini+fim)/2];
   // Primeira etapa, percorre enquanto i<j
    do{
        // percorre i e j até que um elemento da esquerda pertença à direita
        while(v[i]<pivo) i++;
        while(v[j]>pivo) j--;
        // Não é estavel (realiza troca de elementos iguais)
        if(i<=j){
            swap(&v[i], &v[j]);
            i++;
            j--;
        }
    } while(i<j);
    // Continua iterações
    if(j>ini){
        quick_sort(v, ini, j);
    }
    if(i<fim){
        quick_sort(v, i, fim);
    }
}

int msc_ordenacao(int *v, int tam_vetor){
    // Se o tamanho do vetor é 1, a msc é 1
    if(tam_vetor == 1){
        return 1;
    }
    int msc = 1;
    int seq_atual = 1;
    for(int i = 1; i<tam_vetor; i++){
        if(v[i] == v[i-1]+1){
            seq_atual++;
        }
        else{
            if(seq_atual>msc){
                msc = seq_atual;
            }
            seq_atual = 1;
        }
    }
    if(seq_atual>msc){
            msc = seq_atual;
    }

    return msc;

}

//main da resolucao por ordenacao
// int main(){
//     int repeticao;
//     scanf("%d", &repeticao);
//     int * sequencia = (int *) malloc (repeticao * sizeof(int));
//     for(int i = 0; i<repeticao; i++){
//         scanf(" %d", &sequencia[i]);
//     }
//     quick_sort(sequencia, 0, repeticao-1);
//     printf("%d", msc_ordenacao(sequencia, repeticao));
//     free(sequencia);
//     return 0;
// }