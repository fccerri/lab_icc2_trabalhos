#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

// Soma de dois números representados por strings
char* add(char* str1, char* str2) {
    int tam = max(strlen(str1), strlen(str2));
    int carry = 0;
    int sum = 0;

    char* res = calloc(tam + 2, sizeof(char));

    // Adiciona zeros à esquerda para igualar o tamanho das strings
    char* tmp1 = calloc(tam + 1, sizeof(char));
    char* tmp2 = calloc(tam + 1, sizeof(char));
    memset(tmp1, '0', tam);
    memset(tmp2, '0', tam);
    strcpy(tmp1 + (tam - strlen(str1)), str1);
    strcpy(tmp2 + (tam - strlen(str2)), str2);

    for (int i = tam - 1; i >= 0; i--) {
        sum = carry + (tmp1[i] - '0') + (tmp2[i] - '0');
        res[i + 1] = (sum % 10) + '0';
        carry = sum / 10;
    }

    free(tmp1);
    free(tmp2);

    if (carry) {
        res[0] = carry + '0';
        return res;
    } else {
        char* res_shifted = strdup(res + 1);
        free(res);
        return res_shifted;
    }
}
char* sub(char* str1, char* str2) {
    int tam1 = strlen(str1);
    int tam2 = strlen(str2);
    int tam = max(tam1, tam2); 

    char* res = calloc((tam + 2), sizeof(char));
    memset(res, '0', tam + 1);

    int empresta = 0, i = tam1 - 1, j = tam2 - 1, k = tam;

    while (i >= 0 || j >= 0 || empresta) {
        int digito1 = (i >= 0) ? str1[i--] - '0' : 0;
        int digito2 = (j >= 0) ? str2[j--] - '0' : 0;
        digito2 += empresta;

        if (digito1 < digito2) {
            digito1 += 10;
            empresta = 1;
        } else {
            empresta = 0;
        }

        res[k--] = (digito1 - digito2) + '0';
    }

    while (*res == '0' && *(res + 1)) res++;

    return res;
}

// Multiplica um número, representado por uma string, por uma potência de 10
char* potencia_de_10(const char* str, int potencia) {
    int tam = strlen(str);
    char* res = calloc(tam + potencia + 1, sizeof(char));

    strcpy(res, str);
    for (int i = 0; i < potencia; i++) {
        res[tam + i] = '0';
    }
    res[tam + potencia] = '\0';

    return res;
}


char* karatsuba(char* str1, char* str2){
    int m = max(strlen(str1), strlen(str2));
    int meio = m/2;
    // Nesses dois IFs, se alguma string for maior que a outra, o algoritmo as iguala com zeros à esquerda
    // Exemplo: "1" e "02", ficaria "01" e "02"
    if(strlen(str1)>strlen(str2)){
     for (int i = strlen(str2); i >= 0; i--) {
        str2[i + 1] = str2[i];
        }
        str2[0] = '0';
    }
    if(strlen(str2)>strlen(str1)){
     for (int i = strlen(str1); i >= 0; i--) {
        str1[i + 1] = str1[i];
        }
        str1[0] = '0';
    }
    // Se ambos os tamanhos das strings forem 1, será feita a multiplicação entre elas
    if(strlen(str1) == 1 && strlen(str2) == 1){
        int result = (str1[0] - '0') * (str2[0] - '0');
        char * result_char;
        if(result>=10){
            result_char = malloc(3 * sizeof(char));
            result_char[0] = (result/10+'0');
            result_char[1] = ((result - ((result/10)*10))+'0');
            result_char[2] = '\0';

        }
        else{
            result_char = malloc(2 * sizeof(char));
            result_char[0] = (result +'0');
            result_char[1] = '\0';
        }
        return result_char;
    }
    
    // Separação das metades inferiores e superiores
    char* metade_superior1 = strndup(str1, meio);
    char* metade_inferior1 = strndup(str1 + meio, strlen(str1)- meio);
    char* metade_superior2 = strndup(str2, meio);
    char* metade_inferior2 = strndup(str2 + meio, strlen(str2) - meio); 
 
    char* z0 = karatsuba(metade_inferior1, metade_inferior2);
    char* soma1 = add(metade_inferior1, metade_superior1);
    char* soma2 = add(metade_inferior2, metade_superior2);
    char* z1 = karatsuba(soma1, soma2);
    char* z2 = karatsuba(metade_superior1, metade_superior2);

    // Cálculo do resultado final
    char* z1_menos_z0_z2 = sub(z1, add(z0, z2));
    char* potencia10_z2 = potencia_de_10(z2, 2 * (m - meio));
    char* potencia10_z1_menos_z0_z2 = potencia_de_10(z1_menos_z0_z2, m - meio);
    char* resultado = add(add(potencia10_z2, potencia10_z1_menos_z0_z2), z0);
    //Liberando espaços de memória
    free(metade_inferior1);
    metade_inferior1 = NULL;
    free(metade_inferior2);
    metade_inferior2 = NULL;
    free(metade_superior2);
    metade_superior2 = NULL;
    free(metade_superior1);
    metade_superior1 = NULL;


    // Essa parte é apenas uma adequação para umas saídas que sairam "0000", mas era pra ser 0, ou "0123", era pra ser "123"
    int i = 0;
    while (resultado[i] == '0' && resultado[i + 1] != '\0') i++;
    char *resposta = malloc(sizeof(char)*(strlen(resultado)-i+1));
    strcpy(resposta, resultado+i);
    free(resultado);
    return resposta;   
}

char* multiplicacao(const char* str1, const char* str2) {
    int tam1 = strlen(str1), tam2 = strlen(str2), mul;
    char *result = malloc(sizeof(char)*(3));
    char aux[3];

    memset (result, '0', 2 );
    result[2] = '\0';

    for (int i = tam1 - 1 ; i >= 0; i--) {
        for (int j = tam2 - 1; j >= 0; j--) {

            mul = (str1[i] - '0')*(str2[j] - '0'); 
            aux[0] = (mul/10) + '0';
            aux[1] = (mul%10) + '0';
            aux[2] = '\0';

            char* temp = add(result, potencia_de_10(aux, tam1 + tam2 - i - j - 2));
            free(result); 
            result = temp;
        }
           
    }
    int i = 0;
    while (result[i] == '0' && result[i + 1] != '\0') i++;
    char *resposta = malloc(sizeof(char)*(strlen(result)-i+1));
    strcpy(resposta, result+i);
    free(result);

    return resposta;
}
// Função para multiplicar dois números grandes representados por strings
