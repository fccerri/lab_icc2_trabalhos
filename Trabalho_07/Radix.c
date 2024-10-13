#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <string.h>

/*
Correspondência:
    - valores: 4 = 0 / 5 = 1 / 6 = 2 / 7 = 3 / Q = 4 / J = 5 /K = 6 / A = 7 / 2 = 8 / 3 = 9
    - naipe? ouro = 0 / espada = 2 / copas = 4 / zap = 6
Vetor de strings: 
    - string[0] = naipe
    - string[1 -> tam] = valor  } ex: entrada: ♦ 5K7 = string['0','1','8','3']
*/ 

char **input(int n, int tam); 

char converte_valor(char valor);

char converte_naipe(wchar_t naipe);

void counting_sort(char **baralho, char **ordenado, int n, int digito);

char **radix_sort(char **baralho, int n ,int tam);

char **aloca_matriz(int l, int c);

void libera_matriz(char ***matriz, int l);

void printa_baralho(char **baralho, int n, int tam);

int main () {
    int n, tam; scanf("%d%d", &n, &tam); //n = qtd de cartas, tam = n° de dígitos do valor
    char **baralho = input(n, tam); //recebe entrada

    char **ordenado = radix_sort(baralho, n, tam); //ordena e printa ordenacao

    libera_matriz(&baralho,n); //libera memória
    libera_matriz(&ordenado,n);

    return 0;
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

    for (int i =0; i<n; i++) {
        valor = baralho[i][digito] - '0'; //pega id do valor no prefix

        insercao = prefix[valor]; //determina onde o valor será inserido
        prefix[valor]--;

        strcpy(ordenado[insercao], baralho[i]); //insere o valor no vetor ordenado
    }

}

char **radix_sort(char **baralho, int n ,int tam) {
    char **ordenado = aloca_matriz(n, tam+2);    
    printa_baralho( baralho, n, tam); //printa baralho antes da ordenacao
    return 0;
    for(int i = tam; i> 0; i--) {
        counting_sort(baralho, ordenado, n, i);//ordena valores

        printf("Após ordenar o %d° digito dos valores:", i+1);
        printa_baralho(baralho, n, tam); 
    }
    
    counting_sort(baralho, ordenado, n, 0); //ordena naipe

    printf("Após ordenar por naipe:");
    printa_baralho(baralho, n, tam);

    return ordenado;
    
}

char **input(int n, int tam) {
    char **baralho = aloca_matriz(n, tam +2);

    char aux1; wchar_t aux2;
    for (int i = 0; i<n; i++) {
        wscanf(L"%lc", &aux2);
        baralho[i][0] = converte_naipe(aux2); //recebe naipe na forma 0/2/4/6 no id 0

        for(int j = 1 ; j <= tam; j++) {
            scanf("%c", &aux1);
            baralho[i][j] = converte_valor(aux1); //recebe valor da forma 0/1/2/3/4/5/6/7/8/9 
        }                                                // no id j (entre 1 e tam)
        baralho[i][tam+1] = '\0';
    }

    return baralho;
}

void printa_baralho(char **baralho, int n, int tam){
    char correspondencia[20] = "4567QJK♦♠♥♣\0";
    printf("%s", correspondencia);

    for (int i = 0; i<n; i++) {
        int naipe = (baralho[n][0] - '0') + 10; //id do naipe no vetor de correspondencia
        printf("%lc ", correspondencia[naipe]); //printa naipe

        for (int j = 1; j<= tam; j++) {
            int valor = baralho[n][j] - '0'; //id do valor no vetor de correspondencia
            printf("%c;", correspondencia[valor]); //printa valor
        }
    }
    printf("\n");
}

char **aloca_matriz(int l, int c) { //arrumar
    char **baralho = malloc(sizeof(char*)*l);
    
    for (int i = 0; i<l; i++) {
        baralho[i] = malloc(sizeof(char)*c);
    }

    return baralho;
}

void libera_matriz(char ***matriz, int l) {
    for (int i = 0; i<l; i++) {
        free((*matriz)[i]);
        (*matriz)[i] = NULL;
    }
    
    free(*matriz);
    *matriz = NULL;
}

char converte_naipe(wchar_t naipe) {
    char retorno;
    switch (naipe) {
        case (L'♦'): {
            retorno = '0';
            break;
        }
        case (L'♠'): {
            retorno = '2';
            break;
        }
        case (L'♥'): {
            retorno = '4';
            break;
        }
        case (L'♣'): {
            retorno = '6';
            break;
        }
    }

    return retorno;
}

char converte_valor(char valor) {

    switch (valor) {
        case ('Q'): {
            valor = '4';
            break;
        }
        case ('J'): {
            valor = '5';
            break;
        }
        case ('K'): {
            valor = '6';
            break;
        }
        case ('A'): {
            valor = '7';
            break;
        }
        case ('2'): {
            valor = '8';
            break;
        }
        case ('3'): {
            valor = '9';
            break;
        }
        default : valor = valor - '4'; //caso seja:4/5/6/7
    }

    return valor;

}


