#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define BASE 1000
#define NAME_TAM 52
#define AUX_TAM 70
/*entrada: <nome do arquivo> <k> <R/D> <B/M/Q>
R: Utiliza quick select  - D: Apenas ordena o vetor
B: Bubble - M: Merge(gpt) - Q: Quick 
*/


double stop_timer(clock_t start_time){
    clock_t end_time = clock();
    return ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
}

typedef struct aluno_ {
    int aumento;
    char nome[NAME_TAM];
} ALUNO;

ALUNO tratamento_de_dados(char aux[AUX_TAM]);

void quick_sort(ALUNO *alunos, int inicio, int fim); //-> acho q nesse caso a ordenacao sera proxima do pior caso 

void bubble(ALUNO *alunos, int inicio, int fim); //so pra teste

int quick_select(ALUNO *alunos, int k, int inicio, int fim);

int particao(ALUNO *alunos, int inicio, int fim);

int adiciona_empates(ALUNO *alunos, int id, int fim, int menor);

void gerencia_memoria(ALUNO **alunos, int *tam, int *alocado);

int mediana(int a, int b, int c);

void choose(ALUNO *alunos, int inicio, int fim, char sort);

void swap(ALUNO *a, ALUNO *b);

void mergeSort(ALUNO arr[], int left, int right);

void merge(ALUNO arr[], int left, int mid, int right);

int main (void) {
    
    FILE *fp; int k, tam_vet, alocado, id; char arquivo[50], aux[AUX_TAM]; //declaracao
    scanf(" %s%d", arquivo, &k); 
    clock_t time;
    double tempo;

    fp = fopen(arquivo, "r");

    
    ALUNO *alunos = malloc(sizeof(ALUNO)*BASE); //alocacao
    tam_vet = 0; alocado = BASE;
    
    int count = 0; //qtd de alunos
    fscanf(fp, "%*[^\n]"); //ignora primeira linha 
    fgetc(fp); 

    time = clock();    

    while (fscanf(fp, "%69[^\n]", aux) == 1) { //recebe os dados
        fgetc(fp); 
        gerencia_memoria(&alunos, &tam_vet, &alocado); //verifica se tem espaço da realloc se nescessario
        alunos[count] = tratamento_de_dados(aux); //organiza os dados da maneira certa
        count ++;
    }
    count--; //ajusta para o index do ultimo aluno 
    fclose(fp);

    char method, sort; 
    scanf(" %c %c", &method, &sort);
    // method = 'D'; sort = 'Q';
    
    if (method == 'R') {

        id = quick_select(alunos, k, 0, count); //oganiza o vetor e acha o menor aumento contido em k 
        
        id =  adiciona_empates(alunos,  id, count, alunos[id].aumento); //adiciona empates que excedam k 

        choose(alunos, 0, id, sort);

    }
    else if (method == 'D'){
        choose(alunos, 0, count, sort); 
        
        id = k-1;   
        while(id < count && alunos[id+1].aumento == alunos[k-1].aumento) id++;
        
    }
    else {
        printf("R ou D para o algoritimo\n");
        exit(-1);
    }

    tempo = stop_timer(time);

    for (int i = 0; i<=id; i++){ //printa a resposta
        printf("%s\n", alunos[i].nome);
    }

    printf("Tempo de Execução: %lf\n", tempo);   

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
    

    for (int j = inicio; j<fim; j++) { //organiza os elementos e estabelece o local certo para o pivot
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

ALUNO tratamento_de_dados(char aux[AUX_TAM]) {
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

int mediana(int a, int b, int c) {
    if ((a > b) ^ (a > c)) 
        return a;
    else if ((b < a) ^ (b < c)) 
        return b;
    else
        return c;
}

void swap(ALUNO *a, ALUNO *b) {
    ALUNO temp = *a;
    *a = *b;
    *b = temp;
}   

void bubble(ALUNO *alunos, int inicio, int fim) {
    int trocas = 1;

    while (trocas!=0) {
        trocas = 0;
        for (int i = 0; i<=fim-1; i++) {
            if (alunos[i].aumento < alunos[i+1].aumento) {
                swap(&alunos[i], &alunos[i+1]);
                trocas++;
            } 
            else if (alunos[i].aumento == alunos[i+1].aumento && 
                    strcmp(alunos[i].nome, alunos[i+1].nome) > 0 ) {
                        swap(&alunos[i], &alunos[i+1]);
                        trocas++;
                    }
        }
    }
}

void choose(ALUNO *alunos, int inicio, int fim, char sort) {

    switch (sort) {
            case 'B': {
                bubble(alunos, 0, fim);
                break;
            }
            case 'M': {
                mergeSort(alunos, 0, fim);
                break;
            }
            case 'Q': {
                quick_sort(alunos, 0, fim);
                break;
            }
            default: {
                printf("B M ou Q para o método de ordenacao\n");
                exit(-1);
            }
        }
}

void merge(ALUNO arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    ALUNO *L = (ALUNO *)malloc(n1 * sizeof(ALUNO));
    ALUNO *R = (ALUNO *)malloc(n2 * sizeof(ALUNO));

    // Copiar dados para os sub-arrays temporários
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    
    // Merge dos sub-arrays de volta no array original
    while (i < n1 && j < n2) {
        if (L[i].aumento > R[j].aumento || 
           (L[i].aumento == R[j].aumento && strcmp(L[i].nome, R[j].nome) > 0)) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar o restante de L[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar o restante de R[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}


void mergeSort(ALUNO arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

