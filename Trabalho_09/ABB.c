#include <stdio.h>
#include <stdlib.h>

typedef struct no_ {
    struct no_ *filho_esq, *filho_dir;
    int dado;
} NO;

NO *constroiABB(int n);

void insereNo(int valor, NO *raiz);

void BuscaCaminho(NO *raiz, int valor);

void liberaArvore(NO *raiz);

int main () {
    int n, aux; scanf("%d", &n);

    NO *raiz = constroiABB(n);

    scanf("%d", &aux);
    BuscaCaminho(raiz, aux);

    //liberaArvore(raiz);
    return 0;
}

NO *constroiABB(int n) {
    int temp; NO *raiz;
    raiz = calloc(1, sizeof(NO));

    for (int i = 0; i<n; i++) {
        scanf("%d", &temp);
        insereNo(temp, raiz);
    }

    return raiz;
}

void insereNo(int valor, NO *raiz){
    
    if (valor >= raiz->dado) { //caso valor seja MAIOR que a raiz (insercao no lado DIREITO)

        if (raiz->filho_dir != NULL) { //caso o filho direito da raiz já exista
            insereNo(valor, raiz->filho_dir); //faz chamada recursiva para o filho direito
        }
        else { //caso o filho direito não exista
            raiz->filho_dir = calloc(1, sizeof(NO)); //aloca espaço para o nó folha
            raiz->filho_dir->dado = valor; //insere valor 
        }
    }

    else if (valor < raiz->dado) { //caso valor seja MENOR que a raiz (insercao no lado ESQUERDO)

        if (raiz->filho_esq != NULL) { //caso o filho esquerdo da raiz já exista
            insereNo(valor, raiz->filho_esq); //faz chamada recursiva para o filho esquerdo
        }
        else { //caso o filho esquerdo não exista
            raiz->filho_esq = calloc(1, sizeof(NO)); //aloca espaço para o nó folha
            raiz->filho_esq->dado = valor; //insere valor 
        }
    }
}

void BuscaCaminho(NO *raiz, int valor) {
    if (raiz == NULL) { //caso o valor não esteja contido na arvore
        printf("-1\n");
        return;
    }

    printf("%d ", raiz->dado); //printa no atual

    if (raiz->dado > valor) {
        BuscaCaminho(raiz->filho_esq, valor);
    }
    else if (raiz->dado < valor) {
        BuscaCaminho(raiz->filho_dir, valor);
    }

    if (raiz->dado  == valor) return;
    
}
