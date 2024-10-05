#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BASE 1000

typedef struct aluno_ {
    int aumento;
    char nome[52];
} ALUNO;

ALUNO tratamento_de_dados(char aux[70]);

void quick_sort(ALUNO *alunos, int inicio, int fim); //-> acho q nesse caso a ordenacao sera proxima do pior caso 

int quick_select(ALUNO *alunos, int k, int inicio, int fim);

int particao(ALUNO *alunos, int inicio, int fim);

int adiciona_empates(ALUNO *alunos, int id, int fim, int menor);

void gerencia_memoria(ALUNO **alunos, int *tam, int *alocado);

int mediana(int a, int b, int c);

void swap(ALUNO *a, ALUNO *b);

int main (void) {
    
    FILE *fp; int k, tam_vet, alocado; char arquivo[20], aux[70]; //declaracao
    scanf(" %s%d", arquivo, &k); 

    fp = fopen(arquivo, "r");

    
    ALUNO *alunos = malloc(sizeof(ALUNO)*BASE); //alocacao
    tam_vet = 0; alocado = BASE;
    
    int count = 0; //qtd de alunos
    fscanf(fp, "%*[^\n]"); //ignora primeira linha 
    fgetc(fp); 

    while (fscanf(fp, "%69[^\n]", aux) == 1) { //recebe os dados
        fgetc(fp); 
        gerencia_memoria(&alunos, &tam_vet, &alocado); //verifica se tem espaço da realloc se nescessario
        alunos[count] = tratamento_de_dados(aux); //organiza os dados da maneira certa
        count ++;
    }
    count--; //ajusta para o index do ultimo aluno 
    fclose(fp);

    int id = quick_select(alunos, k, 0, count); //oganiza o vetor e acha o menor aumento contido em k 
    
    id =  adiciona_empates(alunos,  id, count, alunos[id].aumento); //adiciona empates que excedam k
    
    quick_sort(alunos, 0, id); //organiza em ordem de aumento e lexicograficamente em caso de emaptes

    for (int i = 0; i<=id; i++){ //printa a resposta
        printf("%s\n", alunos[i].nome);
    }
       
    free(alunos); //libera memoria
    alunos = NULL;
    return 0;
}

void quick_sort(ALUNO *alunos, int inicio, int fim) {
    if (inicio >= fim) //caso base
        return;

    int pivot = particao(alunos,inicio,fim); //ajusta pivot em sua posicao e organiza vetor
    quick_sort(alunos, inicio, pivot-1); //ordena esquerda
    quick_sort(alunos, pivot+1, fim);  //ordena direita

}


int quick_select(ALUNO *alunos, int k, int inicio, int fim) {
    int i = particao(alunos, inicio, fim);

    if (i == k-1) //caso base
        return i;

    if (i < k-1) 
        return quick_select(alunos, k, i+1, fim); //refaz para o lado direito(maior)

    else
        return quick_select(alunos, k, inicio, i-1);//refaz para o lado esquerdo(menor)

    

}

int particao(ALUNO *alunos, int inicio, int fim) {
    swap(&alunos[mediana(inicio, (fim+inicio)/2, fim)], &alunos[fim]); //evita o pior caso
    int i = inicio; ALUNO pivot = alunos[fim];
    

    for (int j = inicio; j<fim; j++) { //organiza os elementos (menores a esqueda, maiores a direita) e estabelece o local certo para o pivot
        if (alunos[j].aumento > pivot.aumento) {
            swap(&alunos[i], &alunos[j]);
            i++;            
        }
        else if (alunos[j].aumento == pivot.aumento) { //desempate por nome 
            if (strcmp(alunos[j].nome , pivot.nome) < 0) {
                swap(&alunos[i], &alunos[j]);
                i++;
            }
            
        }

    }
    swap(&alunos[fim], &alunos[i]); //coloca o pivot em sua posicao
    return i; //index do pivot
}


ALUNO tratamento_de_dados(char aux[70]) {
    ALUNO aluno;
    aux = strtok(aux, ","); //tokeniza a linha tranformando "," em "\n"
    strcpy(aluno.nome, aux); 

    int n[4];
    for (int i =0; i<3; i++) {
        aux = strtok(NULL, ",");
        if(aux[0] == '1' && aux[1] == '0') { //caso a nota seja 10
            n[i] = 100;
            continue;
        }
        n[i] = 10*(aux[0] - '0'); //tranforma 0A.B em AB
        n[i] += (aux[2] - '0');
    }

    aluno.aumento = (n[2] - n[0]); //calcula o aumento
    return aluno;
}

int adiciona_empates(ALUNO *alunos, int id, int fim, int menor) {
    for (int j = id+1; j<=fim; j++) { //percorre o restante do vetor adicionando empates
        if (menor == alunos[j].aumento) {
            swap(&alunos[id+1], &alunos[j]);
            id++;
        }
    }
    return id; //retorna o index ajustado do ultimo aluno incluso 
}

void gerencia_memoria(ALUNO **alunos, int *tam, int *alocado) {
    if (*tam == *alocado) {
        ALUNO *temp = realloc(*alunos, ((*alocado + 1000)*sizeof(ALUNO)));
        if (temp == NULL) exit(-1);

        *alunos = temp;
        *alocado += 1000;
    }
    (*tam)++;
}

void swap(ALUNO *a, ALUNO *b) {
    ALUNO temp = *a;
    *a = *b;
    *b = temp;
}   

int mediana(int a, int b, int c) {
    if ((a > b) ^ (a > c)) 
        return a;
    else if ((b < a) ^ (b < c)) 
        return b;
    else
        return c;
}
