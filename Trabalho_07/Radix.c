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

void counting_sort(char **baralho, char **ordenado, int n, int digito); 
char **radix_sort(char **baralho, int n ,int tam); //Funções utilizadas para o Radix Sort

int main () {
    int n, tam; scanf("%d%d", &n, &tam); //n = qtd de cartas, tam = n° de dígitos do valor
    char **baralho = input(n, tam); //recebe entrada

    double tempo; clock_t start = clock();
    char **ordenado = radix_sort(baralho, n, tam); //ordena e printa ordenacao
    tempo = endTime(start);

    printf("exec time: %lf", tempo);
    libera_matriz(&baralho,n); //libera memória
    libera_matriz(&ordenado,n);

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
    
    for (int i = 0; i<n; i++) {
        int naipe_id = (baralho[i][0] - '0') ; //id do naipe no switch case

        switch (naipe_id) { //printa naipe 
            case(0): printf("♦ "); break;
            case(1): printf("♠ "); break;
            case(2): printf("♥ "); break;
            case(3): printf("♣ "); break;        
        }        

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


void counting_sort(char **baralho, char **ordenado, int n, int digito) {
    int prefix[10] = {0,0,0,0,0,0,0,0,0,0},
    valor, insercao; 

    for (int i = 0; i<n; i++) { //determina quantidade de cada valor
        valor = baralho[i][digito] - '0';
        prefix[valor]++; //insere no vetor auxiliar a quantidade de cada valor
    }

    for (int i = 1; i<=9; i++) { //seta o prefix
        prefix[i] += prefix[i-1];
    }

    for (int i = n -1; i>= 0; i--) {
        valor = baralho[i][digito] - '0'; //pega id do valor no prefix

        insercao = --prefix[valor]; /*determina onde o valor será inserido e decrementa
                                      o prefix[valor] para a proxima insercao*/

        strcpy(ordenado[insercao], baralho[i]); //insere o valor no vetor ordenado
    }

    for (int i =0; i<n; i++) { //copia a matriz ordenada par a matriz original(baralho)
        strcpy(baralho[i], ordenado[i]);
    }

}

char **radix_sort(char **baralho, int n ,int tam) {
    char **ordenado = aloca_matriz(n, tam+2); // +2 para o naipe e o '\0'
    printa_baralho( baralho, n, tam); //printa baralho antes da ordenacao

    for(int i = tam; i > 0; i--) { //ordena valores
        counting_sort(baralho, ordenado, n, i);

        printf("Após ordenar o %d° dígito dos valores:\n", i);
        printa_baralho(baralho, n, tam); 
    }

    counting_sort(baralho, ordenado, n, 0); //ordena naipe

    printf("Após ordenar por naipe:\n");
    printa_baralho(baralho, n, tam);

    return ordenado;    
}


