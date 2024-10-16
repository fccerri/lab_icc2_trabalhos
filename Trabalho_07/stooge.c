#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <string.h>

double endTime(clock_t start){
    clock_t finish = clock();
    return ((double)(finish - start))/CLOCKS_PER_SEC;
}

/*
Correspondência:
    - Valores: 4 = '0' / 5 = '1' / 6 = '2' / 7 = '3' / Q = '4' 
               J = '5' / K = '6' / A = '7' / 2 = '8' / 3 = '9'
    - Naipe: ♦ = '0' / ♠ = '1' / ♥ = '2' / ♣ = '3'

Vetor de strings: (matriz)
    - string[0] = naipe (baralho[i][0])
    - string[1 -> tam] = valor  (baralho[i][1 -> tam])

Exemplo:
 - entrada: ♦ 5K7 = string[] = {'0','1','8','3'}
*/ 

char **input(int n, int tam);  //funções utilizadas nas duas implementações
char converte_valor(char valor);
char converte_naipe(char naipe[5]);
char **aloca_matriz(int l, int c);
void libera_matriz(char ***matriz, int l);
void printa_baralho(char **baralho, int n, int tam);

void stooge_sort(char **baralho, int inicio, int fim);
void swap(char **a, char **b); //Funções utilizadas para o Stooge Sort

int main () {
    int n, tam; scanf("%d%d", &n, &tam); //n = qtd de cartas, tam = n° de dígitos do valor
    char **baralho = input(n, tam); //recebe entrada

    double tempo; clock_t start = clock();
    stooge_sort(baralho, 0, n-1);
    tempo = endTime(start);

    printa_baralho(baralho, n, tam);
    printf("exec time: %lf", tempo);
    libera_matriz(&baralho,n); //libera memória

    return 0;
}

char **input(int n, int tam) {
    char **baralho = aloca_matriz(n, tam +2); // +2 para o naipe e o '\0'

    char aux1; char aux2[5];
    for (int i = 0; i<n; i++) { //percorre todos as cartas
        scanf(" %s", aux2);
        baralho[i][0] = converte_naipe(aux2); //insere naipe na forma '0'/'1'/'2'/'3' no id 0

        for(int j = 1 ; j <= tam; j++) { //percorre todos os digitos de cada valor
            scanf(" %c", &aux1);
            baralho[i][j] = converte_valor(aux1); //recebe valores da forma '0'/'1'/'2'/'3'/'4'/'5'/'6'/'7'/'8'/'9'
        }                                               // no id j (entre 1 e tam)
                                                     
        baralho[i][tam+1] = '\0'; //fim da string
    }

    return baralho;
}

void printa_baralho(char **baralho, int n, int tam){
    char valores[] = "4567QJKA23"; //matriz de correspondencia
    // wchar_t naipes[] = L"♦♠♥♣";

    for (int i = 0; i<n; i++) {
        int naipe_id = (baralho[i][0] - '0') ; //id do naipe no switch case

        switch (naipe_id) { //printa naipe 
            case(0): printf("♦ "); break;
            case(1): printf("♠ "); break;
            case(2): printf("♥ "); break;
            case(3): printf("♣ "); break;        
        }        
        // wprintf(L"%lc ", naipes[naipe_id]); //printa naipe

        for (int j = 1; j<= tam; j++) { //percorre todos os digitos do valor de cada carta
            int valor_id = baralho[i][j] - '0'; //id do valor no vetor de correspondencia

            printf("%c", valores[valor_id]); //printa o digito j do valor da carta i
            
        }
        printf(";");
    }
    printf("\n");
}

char **aloca_matriz(int l, int c) { //arrumar
    char **matriz = malloc(sizeof(char*)*l); //aloca as cartas

    for (int i = 0; i<l; i++) { //aloca strings que representam o naipe e valor de cada carta
        matriz[i] = malloc(sizeof(char)*c);
    }
    
    return matriz;
}

void libera_matriz(char ***matriz, int l) { 
    if (*matriz == NULL) return;

    for (int i = 0; i<l; i++) {
        free((*matriz)[i]);
        (*matriz)[i] = NULL;
    }
    
    free(*matriz);
    *matriz = NULL;
}

char converte_naipe(char naipe[5]) { //transforma naipes na forma '0'/'1'/'2'/'3'
    
    if (strcmp("♦", naipe) == 0) return '0';
    else if (strcmp("♠", naipe) == 0) return '1';
    else if (strcmp("♥", naipe) == 0) return '2';
    else return '3';
}

char converte_valor(char valor) { /*transforma digito do valor na forma 
                                    '0'/'1'/'2'/'3'/'4'/'5'/'6'/'7'/'8/'9'*/
    switch (valor) {
        case ('Q'): return '4'; 
        case ('J'): return '5';
        case ('K'): return '6';
        case ('A'): return '7';
        case ('2'): return '8';
        case ('3'): return '9';
        default: return valor - 4; //caso seja: 4/5/6/7 = '0'/'1/'2'/'3'
    }
}


void stooge_sort(char **baralho, int inicio, int fim) { //ordena o baralho in place

    if (strcmp(baralho[inicio], baralho[fim]) > 0) //compara primeiro e ultimo elemento
        swap(&baralho[inicio], &baralho[fim]); //faz a troca caso necessario
    
    if (inicio + 1 >= fim) return; //caso base

    int tam = fim - inicio +1; //+1 garante que o arredondamento de 1/3 seja para cima
    int novo_fim = fim - tam/3, novo_inicio = inicio + tam/3;

    stooge_sort(baralho, inicio,novo_fim); // primeiros 2/3
    stooge_sort(baralho, novo_inicio, fim); // ultimos 2/3
    stooge_sort(baralho, inicio, novo_fim); //p rimeiros 2/3 
}

void swap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}


