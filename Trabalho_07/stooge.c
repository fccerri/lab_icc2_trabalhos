#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <string.h>

/*
Correspondência:
    - valores: 4 = 0 / 5 = 1 / 6 = 2 / 7 = 3 / Q = 4 / J = 5 /K = 6 / A = 7 / 2 = 8 / 3 = 9
    - naipe: ouro = 0 / espada = 1 / copas = 2 / zap = 3
Vetor de strings: 
    - string[0] = naipe
    - string[1 -> tam] = valor  } ex: entrada: ♦ 5K7 = string['0','1','8','3']
*/ 

char **input(int n, int tam); 
char converte_valor(char valor);
char converte_naipe(char naipe[5]);
void stooge_sort(char **baralho, int inicio, int fim);
char **aloca_matriz(int l, int c);
void libera_matriz(char ***matriz, int l);
void printa_baralho(char **baralho, int n, int tam);
void swap(char **a, char **b);

int main () {
    int n, tam; scanf("%d%d", &n, &tam); //n = qtd de cartas, tam = n° de dígitos do valor
    char **baralho = input(n, tam); //recebe entrada

    stooge_sort(baralho, 0, n-1); //ordena e printa ordenacao
    printa_baralho(baralho, n, tam);

    libera_matriz(&baralho,n); //libera memória

    return 0;
}

void stooge_sort(char **baralho, int inicio, int fim) {
    if (inicio == fim) return;
    if (strcmp(baralho[inicio], baralho[fim]) > 0) {
        swap(&baralho[inicio],& baralho[fim]);
    }

    int tam = fim - inicio + 1; //+1 garante o arredontamento para cima 
    int novo_inicio = inicio + tam/3, novo_fim =  fim - tam/3;


    if (fim - inicio + 1 > 2) {
        stooge_sort(baralho, inicio, novo_fim); 
        stooge_sort(baralho, novo_inicio, fim);
        stooge_sort(baralho, inicio, novo_fim);
    }
}


char **input(int n, int tam) {
    char **baralho = aloca_matriz(n, tam +2); // +2 para o naipe e o '\0'

    char aux1; char aux2[5];
    for (int i = 0; i<n; i++) {
        scanf(" %s", aux2);
        baralho[i][0] = converte_naipe(aux2); //recebe naipe na forma 0/1/2/3 no id 0

        for(int j = 1 ; j <= tam; j++) {
            scanf(" %c", &aux1);
            baralho[i][j] = converte_valor(aux1); //recebe valor da forma 0/1/2/3/4/5/6/7/8/9 
        }                                               // no id j (entre 1 e tam)
                                                     
        baralho[i][tam+1] = '\0'; 
    }

    return baralho;
}

void printa_baralho(char **baralho, int n, int tam){
    char valores[] = "4567QJKA23"; 
    wchar_t naipes[] = L"♦♠♥♣";

    for (int i = 0; i<n; i++) {
        int naipe_id = (baralho[i][0] - '0') ; //id do naipe no vetor de correspondencia

        switch (naipe_id) {
            case(0): printf("♦ "); break;
            case(1): printf("♠ "); break;
            case(2): printf("♥ "); break;
            case(3): printf("♣ "); break;        
        }        
        //  wprintf(L"%lc ", naipes[naipe_id]); //printa naipe

        for (int j = 1; j<= tam; j++) {
            int valor_id = baralho[i][j] - '0'; //id do valor no vetor de correspondencia

            printf("%c", valores[valor_id]); //printa valor
            
        }
        printf(";");
    }
    printf("\n");
}

char **aloca_matriz(int l, int c) { //arrumar
    char **matriz = malloc(sizeof(char*)*l);

    for (int i = 0; i<l; i++) {
        matriz[i] = malloc(sizeof(char)*c);
    }
    
    return matriz;
}

void libera_matriz(char ***matriz, int l) {
    for (int i = 0; i<l; i++) {
        free((*matriz)[i]);
        (*matriz)[i] = NULL;
    }
    
    free(*matriz);
    *matriz = NULL;
}

char converte_naipe(char naipe[5]) {
    
    if (strcmp("♦", naipe) == 0) return '0';
    else if (strcmp("♠", naipe) == 0) return '1';
    else if (strcmp("♥", naipe) == 0) return '2';
    else return '3';
}

char converte_valor(char valor) {

    switch (valor) {
        case ('Q'): return '4'; 
        case ('J'): return '5';
        case ('K'): return '6';
        case ('A'): return '7';
        case ('2'): return '8';
        case ('3'): return '9';
        default: return valor - 4; //caso seja:4/5/6/7
    }
}

void swap(char **a, char **b) { 
    char *temp = *a; // Troca as referências das strings
    *a = *b;
    *b = temp;
}