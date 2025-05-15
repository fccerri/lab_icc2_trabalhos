#include <stdio.h>

typedef struct no_ {
    char nome[20];
    struct no_ *destino;
    int id;
} NO;