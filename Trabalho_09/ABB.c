#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double endTime(clock_t start){
    clock_t finish = clock();
    return ((double)(finish - start))/CLOCKS_PER_SEC;
}

typedef struct no_ {
    struct no_ *filho_esq; //ponteiro para o filho esquerdo
    struct no_ *filho_dir; ////ponteiro para o filho direito
    int dado; //dado contido no nó
} NO;

NO *constroiABB(int n);
NO *insereNo(int valor, NO *raiz);
void BuscaCaminho(NO *raiz, int valor);
int dfs(NO *raiz, int valor);
void liberaArvore(NO **raiz);

int main () { 
    int n, aux; scanf("%d", &n);

    NO *raiz = constroiABB(n);

    // double tempo; clock_t start = clock();
    scanf("%d", &aux);
    BuscaCaminho(raiz, aux);
    // tempo = endTime(start);
    // printf("\ntempo da busca binaria: %lf\n", tempo);

    // start = clock(); 
    // dfs(raiz, aux); //busca linear para comparacao
    // tempo = endTime(start);
    // printf("tempo da dfs: %lf\n", tempo);

    liberaArvore(&raiz);
    return 0;
}

NO *constroiABB(int n) {
    int temp; NO *raiz; //ponteiro para a raiz da arvore

    scanf("%d", &temp);
    raiz = insereNo(temp, raiz); //estabelece  e aloca a raiz da arvore

    for (int i = 0; i<n -1 ; i++) { //constroi a arvore 
        scanf("%d", &temp);
        insereNo(temp, raiz); //insere o nó com o valor "temp"
    }

    return raiz;
}

NO *insereNo(int valor, NO *raiz){
    if (raiz == NULL) { //caso base, insere o novo nó
        NO *aux = calloc(1, sizeof(NO)); //aloca o novo nó
        aux->dado = valor; //guarda o seu valor
        return aux;
    }
        
    if (valor >= raiz->dado) { //caso valor seja MAIOR que a raiz (insercao no lado DIREITO)
        raiz->filho_dir =  insereNo(valor, raiz->filho_dir); //faz chamada recursiva para o filho direito
    }
    else { //caso valor seja MENOR que a raiz (insercao no lado ESQUERDO)
            raiz->filho_esq = insereNo(valor, raiz->filho_esq); //faz chamada recursiva para o filho esquerdo
    }
        
    return raiz;
}

void BuscaCaminho(NO *raiz, int valor) {
    if (raiz == NULL) { //caso o valor não esteja contido na arvore
        printf("-1");
        return;
    }

    printf("%d ", raiz->dado); //printa o nó atual

    if (raiz->dado > valor) { //continua busca na arvore da esquerda
        BuscaCaminho(raiz->filho_esq, valor);
    }
    else if (raiz->dado < valor) { //continua busca na arvore da direita
        BuscaCaminho(raiz->filho_dir, valor);
    }   
}

int dfs(NO *raiz, int valor) {
    if (raiz == NULL) return -1; //caso não encontre
    printf("%d ", raiz->dado); //printa o caminho 
    if (raiz->dado == valor) return valor; //caso o valor tenha sido encontrado

    if (dfs(raiz->filho_esq, valor) == valor) return valor; //caso o valor ja tenha sido encontrado

    dfs(raiz->filho_dir, valor);
}

void liberaArvore(NO **raiz) {
    if (*raiz != NULL) {
        liberaArvore(&(*raiz)->filho_dir); //chamada recursiva para arvore da direita
        liberaArvore(&(*raiz)->filho_esq); //chamada recursiva para arvore da esquerda
        (*raiz)->filho_esq = NULL;
        (*raiz)->filho_dir = NULL;

        free(*raiz); //libera a memoria
        *raiz = NULL;
    }
}
